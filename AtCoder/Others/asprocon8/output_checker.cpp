// g++ --std=c++17 -o output_checker output_checker.cpp
#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <numeric>
#include <string>
#include <algorithm>

constexpr int output_lines_max = 1000000;
constexpr int base_score = 10000000;

class ErrorList {
    std::vector<std::string> messages;
    const size_t error_report_max = 1000;
public:
    ErrorList() {};
    ~ErrorList() {
        for (const std::string& msg : messages) {
            std::cerr << msg << '\n';
        }
        std::cerr.flush();
    }
    void add(const std::string &msg) {
        if (messages.size() < error_report_max) {
            messages.push_back(msg);
        }
    }
    bool empty() const { return messages.empty(); }
} errors;

template<typename... Args>
void record_error(const std::string &format, Args... args) {
    char buf[256];
    snprintf(buf, 256, format.c_str(), args...);
    errors.add(buf);
}

struct Item { int hanger, color; };

// input
int H, S, C, a, b;
std::vector<int> K;
std::vector<std::vector<int> > N, A, B;

void read_input(std::ifstream &in) {
    // assume that the input is valid
    in >> S >> C >> H >> a >> b;
    N.resize(S);
    for (int s = 0; s < S; s++) {
        N[s].resize(C);
        for (int c = 0; c < C; c++) in >> N[s][c];
    }
    K.resize(S);
    for (int s = 0; s < S; s++) in >> K[s];
    A.resize(S);
    for (int s = 0; s < S; s++) {
        A[s].resize(S);
        for (int t = 0; t < S; t++) in >> A[s][t];
    }
    B.resize(C);
    for (int c = 0; c < C; c++) {
        B[c].resize(C);
        for (int d = 0; d < C; d++) in >> B[c][d];
    }
}

// output
class Instruction {
    int s, c = 0;
public:
    Instruction(int s) : s(s) {
        assert(s == -1 || s == -2);
    }
    Instruction(int s, int c) : s(s), c(c) {
        assert(0 <= s);
        assert(s < S);
        assert(0 <= c);
        assert(c < C);
    }
    bool is_put() const { return s >= 0; }
    bool is_skip() const { return s == -2; }
    bool is_remove() const { return s == -1; }
    Item get_item() const { assert(is_put()); return Item{s, c}; }
};
std::vector<Instruction> output;

Instruction inst_skip() { return Instruction{-2}; }
Instruction inst_remove() { return Instruction{-1}; }
Instruction inst_put(int s, int c) { assert(s >= 0); return Instruction{s, c}; }

void read_output(std::ifstream &out) {
    int k; out >> k;
    if (out.fail()) {
        record_error("%s", "Cannot read output size");
        return;
    } else if (k <= 0 || k > output_lines_max) {
        record_error("Invalid output size: %d", k);
        k = std::min(k, output_lines_max);
    }

    for (int i = 0; i < k; i++) {
        int s; out >> s;
        if (out.fail()) {
            record_error("Cannot read instruction %d", i + 1);
            return;
        } else if (s == -2) {
            output.push_back(inst_skip());
        } else if (s == -1) {
            output.push_back(inst_remove());
        } else if (0 < s && s <= S) {
            int c; out >> c;
            if (out.fail()) {
                record_error("Cannot read color (hook %d)", i + 1);
                return;
            }
            if (0 < c && c <= C) {
                output.push_back(inst_put(s - 1, c - 1));
            } else {
                record_error("Invalid item (%d, %d) (hook %d)", s, c, i + 1);
            }
        } else {
            record_error("Invalid instruction %d (hook %d)", s, i + 1);
            std::string discard;
            getline(out, discard);
        }
    }
}

void check_item_qty() {
    std::vector qty(S, std::vector(C, 0));
    for (Instruction inst : output) {
        if (inst.is_put()) {
            const auto [s, c] = inst.get_item();
            qty[s][c]++;
        }
    }
    for (int s = 0; s < S; s++)
        for (int c = 0; c < C; c++)
            if (qty[s][c] != N[s][c]) {
                record_error("Wrong number of occurrences of item (%d, %d): "
                             "expect %d, got %d",
                             s + 1, c + 1, N[s][c], qty[s][c]);
            }
}

void check_setup() {
    int prev_s = -1, prev_c = -1, prev_idx = -1;
    for (int i = 0; i < int(output.size()); i++) {
        if (output[i].is_put()) {
            const auto [s, c] = output[i].get_item();
            if (prev_s != -1) {
                const int setup = std::max(A[prev_s][s], B[prev_c][c]);
                if (setup > i - prev_idx - 1) {
                    record_error("Too few empty hooks between instructions %d and %d",
                                 prev_idx + 1, i + 1);
                }
            }
            prev_s = s;
            prev_c = c;
            prev_idx = i;
        }
    }
}

int calc_score() {
    check_item_qty();
    check_setup();

    // simulate
    std::vector<int> t(H, -1), r = K;
    int X = 0;
    for (int i = 0; i < int(output.size()); i++) {
        const Instruction inst = output[i];
        const int h = i % H;
        if (inst.is_remove()) {
            if (t[h] == -1) {
                record_error("Instruction %d is -1, but no hanger to remove", i + 1);
            } else {
                r[t[h]]++;
                X++;
                t[h] = -1;
            }
        } else if (inst.is_put()) {
            const auto s = inst.get_item().hanger;
            if (t[h] == -1) {
                r[s]--;
                X++;
                t[h] = s;
            } else if (t[h] != s) {
                r[t[h]]++;
                r[s]--;
                X += 2;
                t[h] = s;
            }
            if (r[s] < 0) {
                record_error("Used too many hangers of type %d on instruction %d",
                             s + 1, i + 1);
                r[s] = 0;
            }
        }
    }

    int Y = output.size();
    for (const auto &Ns : N) Y -= std::accumulate(Ns.begin(), Ns.end(), 0);
    const long long penalty = (long long)a * X + (long long)b * Y;
	std::cout<<X<<","<<Y<<std::endl;
    return base_score > penalty ? base_score - penalty : 1;
}

void check_output(const char *input, const char *output) {
    if (std::ifstream in(input); in) {
        read_input(in);
    } else {
        record_error("Cannot open input file: %s", input);
    }
    if (!errors.empty()) return;

    if (std::ifstream out(output); out) {
        read_output(out);
    } else {
        record_error("Cannot open output file: %s", output);
    }
    if (!errors.empty()) return;

    const int score = calc_score();
    if (!errors.empty()) return;

    assert(score > 0);
    std::cout << "IMOJUDGE<<<" << score << ">>>" << std::endl;
}

int main(int argc, const char** argv) {
    if (argc <= 2) {
        record_error("Too few arguments.\nUsage: %s INPUT OUTPUT", argv[0]);
        return 1;
    } else {
        check_output(argv[1], argv[2]);
        return errors.empty() ? 0 : 1;
    }
}
