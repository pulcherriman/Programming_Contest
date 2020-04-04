// akemi's PrimeDaihinmin Solver (C) 2019 Fixstars Corp.
// g++ akemi.cpp -std=c++17 -o akemi -O3 -Wall -Wno-unused-but-set-variable -lgmp

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <utility>

#include <gmpxx.h>
#include "json.hpp"

constexpr const char* version  = "0.06";
constexpr const char* revision = "a";
constexpr const char* ver_date = "20191225";

static double TIME_LIMIT = 10.0;

void remove_newline(std::string& s)
{
    std::string target("\n");
    std::string::size_type pos = s.find(target);
    while (pos != std::string::npos) {
        s.replace(pos, target.size(), "");
        pos = s.find(target, pos);
    }
}

// Miller-Rabin primality test
int is_prime(const mpz_t q, int k=50)
{
    return mpz_probab_prime_p(q, k);
}

void string2digits(const std::string& s, std::vector<int>& v)
{
    for (const char c : s) {
        int n = c - '0';
        if (n < 0 || n > 9) continue;
        v.push_back(n);
    }
}

std::string make_candidate(std::vector<int> hand, int length)
{
    std::random_device seed_gen;
    std::default_random_engine engine(seed_gen());
    std::stringstream ss("");

    if (length == 1) {
        std::vector<int> h(hand);
        h.erase(std::unique(h.begin(), h.end()), h.end());
        auto p = std::remove(h.begin(),h.end(), 0);
        p = std::remove(h.begin(), p, 1);
        p = std::remove(h.begin(), p, 4);
        p = std::remove(h.begin(), p, 6);
        p = std::remove(h.begin(), p, 8);
        p = std::remove(h.begin(), p, 9);
        h.erase(p, h.end());
        if (h.empty()) {
            return "";
        } else {
            std::uniform_int_distribution<> randint(0, h.size() - 1);
            int n = h[randint(engine)];
            ss << n;
            return ss.str();
        }
    }

    std::vector<int> hh;
    std::vector<int> ht;
    std::copy_if(hand.begin(), hand.end(), std::back_inserter(hh), [](int n){ return n > 0; });
    std::copy_if(hand.begin(), hand.end(), std::back_inserter(ht), [](int n){ return (n & 1) == 1 && n != 5; });
    if (ht.empty()) return "";
    std::uniform_int_distribution<> randht(0, ht.size() - 1);
    int tail = ht[randht(engine)];
    hh.erase(std::find(hh.begin(), hh.end(), tail));
    if (hh.empty()) return "";
    std::uniform_int_distribution<> randhh(0, hh.size() - 1);
    int head = hh[randhh(engine)];
    hand.erase(std::find(hand.begin(), hand.end(), tail));
    hand.erase(std::find(hand.begin(), hand.end(), head));
    std::shuffle(hand.begin(), hand.end(), engine);
    ss << head;
    for (int i = 0; i < length - 2; i++) {
        ss << hand[i];
    }
    ss << tail;
    return ss.str();
}

std::string make_Mersenne(std::vector<int> hand, int length)
{
    std::vector<int> u;

    switch (length) {
    case 1:
        if (std::find(hand.begin(), hand.end(), 3) != hand.end()) return "3";
        if (std::find(hand.begin(), hand.end(), 7) != hand.end()) return "7";
        break;
    case 2:
        u = {1, 3};
        if (std::includes(hand.begin(), hand.end(), u.begin(), u.end())) return "31";
        break;
    case 3:
        u = {1, 2, 7};
        if (std::includes(hand.begin(), hand.end(), u.begin(), u.end())) return "127";
        break;
    case 4:
        u = {1, 8, 9};
        if (std::includes(hand.begin(), hand.end(), u.begin(), u.end())
            && std::count(hand.begin(), hand.end(), 1) >= 2) return "8191";
        break;
    case 6:
        u = {2, 4, 5, 7, 8};
        if (std::includes(hand.begin(), hand.end(), u.begin(), u.end())
            && std::count(hand.begin(), hand.end(), 2) >= 2) return "524287";
        u = {0, 1, 3, 7};
        if (std::includes(hand.begin(), hand.end(), u.begin(), u.end())
            && std::count(hand.begin(), hand.end(), 1) >= 3) return "131071";
        break;
    case 10:
        u = {1, 2, 3, 4, 6, 7, 8};
        if (std::includes(hand.begin(), hand.end(), u.begin(), u.end())
            && std::count(hand.begin(), hand.end(), 4) >= 3 
            && std::count(hand.begin(), hand.end(), 7) >= 2) return "2147483647";
        break;
    }

    return "";
}

std::vector<int> solver(std::vector<int> hand, const mpz_class& number, int length)
{
      std::random_device seed_gen;
      std::default_random_engine engine(seed_gen());
    std::vector<int> cards;
    std::vector<int> ret({});

    if (static_cast<int>(hand.size()) < length) return cards;

    // check Belphegor prime
    int cnt_0 = std::count(hand.begin(), hand.end(), 0);
    int cnt_1 = std::count(hand.begin(), hand.end(), 1);
    int cnt_6 = std::count(hand.begin(), hand.end(), 6);
    if (cnt_0 >=26 && cnt_1 >= 2 && cnt_6 >= 3) {
        ret = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
        return ret;
    }

    // check Mersenne prime
    std::string mersenne = make_Mersenne(hand, length);
    if (!mersenne.empty()) {
        mpz_class m;
        m.set_str(mersenne, 10);
        if (m > number) {
            string2digits(mersenne, ret);
            return ret;
        }
    }

    mpz_class candidate;
    for (int i = 0; i < 10000; i++) {
        std::string s = make_candidate(hand, length);
        if (!s.empty()) {
            candidate.set_str(s, 10);
            if (candidate > number && is_prime(candidate.get_mpz_t())) {
                string2digits(s, ret);
                return ret;
            }
        }
    }

    return ret;
}

int main(int argc, char* argv[])
{
    std::string s;
    const int num_first_cards = 5;
      std::random_device seed_gen;
      std::default_random_engine engine(seed_gen());

    for (;;) {
        getline(std::cin, s);
        nlohmann::json obj = nlohmann::json::parse(s);
        auto action = obj["action"];

        if (action == "play") {
            auto name(obj["name"]);
            auto hand_(obj["hand"]);
            auto numbers_(obj["numbers"]);
            auto record(obj["record"]);
            auto hands(obj["hands"]);

            std::vector<int> hand;
            for (const auto card : hand_) {
                hand.push_back(card);
            }

            std::vector<mpz_class> numbers;
            std::string number_str("");
            mpz_class n;
            for (const auto number : numbers_) {
                number_str += number;
                n.set_str(number, 10);
                numbers.push_back(n);
            }

            int length = number_str.length();
            if (length == 0) {
                if (hand.size() <= num_first_cards) {
                    length = hand.size();
                } else {
                    std::uniform_int_distribution<> dist(1, num_first_cards);
                    length = dist(engine);
                }
            }

            const mpz_class ZERO("0");
            auto cards = solver(hand, numbers.empty() ? ZERO : numbers.back(), length);

            nlohmann::json out;
            if (!cards.empty()) {
                out["action"] = "number";
                out["cards"] = cards;
            } else {
                out["action"] = "pass";
            }
            std::string json(out.dump());
            remove_newline(json);
            std::cout << json << std::endl << std::flush;

        } else if (action == "pass") {
            auto draw(obj["draw"]);
            std::cout << std::endl << std::flush;

        } else if (action == "init") {
            int uid(obj["uid"]);
            auto names(obj["names"]);
            auto name(names[uid]);
            auto hand(obj["hand"]);
            TIME_LIMIT = obj["time"];
            std::cout << std::endl << std::flush;

        } else if (action == "quit") {
            std::cout << std::endl << std::flush;
            break;
        }
    }

    return 0;
}