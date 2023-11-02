#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

// #define NDEBUG

#include <bits/stdc++.h>
// #include <atcoder/all>

using namespace std;
// using namespace atcoder;

#define ll long long int
#define ull unsigned long long int

class Xorshift {
    public:
        Xorshift(): x_(1) {}

        Xorshift(uint32_t seed): x_(seed) {
            assert(seed);
        }

        uint32_t randrange(uint32_t stop) {
            // [0, stop)
            assert(stop > 0);
            next();
            return x_ % stop;
        }

        uint32_t randrange(uint32_t start, uint32_t stop) {
            // [start, stop)
            assert(start < stop);
            next();
            return start + x_ % (stop - start);
        }

        uint32_t randint(uint32_t a, uint32_t b) {
            // [a, b]
            assert(a <= b);
            return randrange(a, b + 1);
        }

        double random() {
            // [0.0, 1.0]
            next();
            return static_cast<double>(x_) / static_cast<double>(UINT32_MAX);
        }

        double uniform(double a, double b) {
            // [a, b] or [b, a]
            return a + (b - a) * random();
        }

    private:
        void next() {
            x_ ^= x_ << 13;
            x_ ^= x_ >> 7;
            x_ ^= x_ << 17;
        }

        uint32_t x_;
};

class Timer {
    public:
        Timer() {
            begin();
            elapsed_time_ = 0.0;
        }

        void begin() {
            start_time_ = chrono::system_clock::now();
        }

        double get_time() {
            chrono::system_clock::time_point end_time = chrono::system_clock::now();
            elapsed_time_ = chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time_).count();
            elapsed_time_ *= 1e-9; // nanoseconds -> seconds
            return elapsed_time_;
        }

        double get_last_time() const {
            return elapsed_time_;
        }

        bool yet(double time_limit) {
            return get_time() < time_limit;
        }

        double progress(double time_limit) {
            return get_time() / time_limit;
        }

    private:
        chrono::system_clock::time_point start_time_;
        double elapsed_time_;
};

constexpr double time_limit = 1.95;
constexpr double lambda = 1e-5;

using ItemSet = bitset<100>;

vector<int> bitset_to_vector(const ItemSet& l) {
    ull low = (l & ItemSet(ULLONG_MAX)).to_ullong();
    ull high = (l >> 64).to_ullong();

    vector<int> ret;
    ret.reserve(l.count());

    while (low) {
        int v = countr_zero(low);
        ret.push_back(v);
        low ^= (1ull << v);
    }
    while (high) {
        int v = countr_zero(high);
        ret.push_back(v + 64);
        high ^= (1ull << v);
    }
    return ret;
}

ItemSet vector_to_bitset(const vector<int>& g) {
    ItemSet ret;
    for (int i : g) {
        ret.set(i);
    }
    return ret;
}

struct IO {
    bool online_judge;
    string filename;
    ofstream out;

    int n, d, q;
    vector<int> w;
    int turn;

    void input() {
        online_judge = true;
        cin >> n >> d >> q;
        turn = 0;
		w = vector<int>(n);
        for (int i = 0; i < n; ++i) {
            cin >> w[i];
        }
    }

    void input(const string& filename_) {
        online_judge = false;
        filename = filename_;
        out = ofstream("out/" + filename);

        ifstream in("in/" + filename);
        assert(in);

        in >> n >> d >> q;

        w = vector<int>(n);
        for (int i = 0; i < n; ++i) {
            in >> w[i];
        }
        turn = 0;
    }

    int sum(const ItemSet& l) {
        int ret = 0;
        for (int x : bitset_to_vector(l)) {
            ret += w[x];
        }
        return ret;
    }

    char query(const ItemSet& l, const ItemSet& r) {
        assert(l.any());
        assert(r.any());
        assert(!(l >> n).any());
        assert(!(r >> n).any());
        assert(!(l & r).any());

        assert(turn < q);
        ++turn;

        if (online_judge) {
            cout << l.count() << " " << r.count();
            for (int x : bitset_to_vector(l)) {
                cout << " " << x;
            }
            for (int x : bitset_to_vector(r)) {
                cout << " " << x;
            }
            cout << endl;

            int ls = sum(l);
            int rs = sum(r);
            if (ls < rs) {
                return '<';
            } else if (ls > rs) {
                return '>';
            } else {
                return '=';
            }
        } else {
            out << l.count() << " " << r.count();
            for (int x : bitset_to_vector(l)) {
                out << " " << x;
            }
            for (int x : bitset_to_vector(r)) {
                out << " " << x;
            }
            out << "\n";

            int ls = sum(l);
            int rs = sum(r);
            if (ls < rs) {
                return '<';
            } else if (ls > rs) {
                return '>';
            } else {
                return '=';
            }
        }
    }

    void print(const vector<int>& answer, bool debug) {
        assert(answer.size() == static_cast<size_t>(n));
        if (debug) {
            if (!online_judge) {
                out << "#c ";
            } else {
                return;
            }
        } else {
            assert(turn == q);
        }
        if (online_judge) {
            for (int i = 0; i < n; ++i) {
                cout << answer[i] << (i == n - 1 ? "\n" : " ");
            }
        } else {
            for (int i = 0; i < n; ++i) {
                out << answer[i] << (i == n - 1 ? "\n" : " ");
            }
        }
    }

    void comment(const string& message) {
        if (!online_judge) {
            out << "# " << message << "\n";
        }
    }

    ll get_cost(const vector<int>& answer) const {
        assert(!online_judge);
        assert(turn == q);
        assert(answer.size() == static_cast<size_t>(n));

        vector<double> t(d, 0);
        for (int i = 0; i < n; ++i) {
            assert(0 <= answer[i] && answer[i] < d);
            t[answer[i]] += w[i];
        }
        double mu = accumulate(t.begin(), t.end(), 0) / d;

        double v = 0.0;
        for (int x : t) {
            v += (x - mu) * (x - mu);
        }
        v /= d;
        return 1ll + static_cast<ll>(round(100.0 * sqrt(v)));
    }
};

struct History {
    vector<tuple<vector<int>,vector<int>,char>> data;
    map<tuple<ull,ull,ull,ull>,char> dict;

    History() {}

    History(int q) {
        data.reserve(q);
    }

    void push_result(const ItemSet& l, const ItemSet& r, char res) {
        assert(res == '<' || res == '>' || res == '=');
        if (res == '>') {
            data.push_back({bitset_to_vector(r), bitset_to_vector(l), '<'});
        } else {
            data.push_back({bitset_to_vector(l), bitset_to_vector(r), res});
        }
        dict[to_key(l, r)] = res;
        dict[to_key(r, l)] = res_inv(res);
    }

    char res_inv(char res) {
        if (res == '<') {
            return '>';
        } else if (res == '>') {
            return '<';
        } else {
            return '=';
        }
    }

    char compare(ItemSet l, ItemSet r) {
        ItemSet lr = l & r;
        l ^= lr;
        r ^= lr;
        tuple<ull,ull,ull,ull> key = to_key(l, r);
        if (dict.contains(key)) {
            return dict[key];
        } else {
            return '?';
        }
    }

    tuple<ull,ull,ull,ull> to_key(const ItemSet& l, const ItemSet& r) {
        ull l_low = (l & ItemSet(ULLONG_MAX)).to_ullong();
        ull l_high = (l >> 64).to_ullong();
        ull r_low = (r & ItemSet(ULLONG_MAX)).to_ullong();
        ull r_high = (r >> 64).to_ullong();
        return {l_low, r_low, l_high, r_high};
    }

    void set_order(const vector<int>& order) {
        for (size_t i = 0; i < order.size() - 1; ++i) {
            ItemSet l;
            l.set(order[i]);
            ItemSet r;
            r.set(order[i + 1]);
            push_result(l, r, '<');
        }
    }
};

constexpr double delta_ampllification = 2.0;
constexpr int max_updates = 30;

struct Estimator {
    int n, d;
    double min_w, max_w;
    vector<double> w;
    double sum_w;
    size_t mitm_max_n;
    bool converged;

    Estimator() {}

    Estimator(int n, int d, Xorshift& engine): n(n), d(d) {
        min_w = 1.0;
        max_w = 1e5 * n / d;
        generate_w(engine);
        converged = false;
    }

    void set_mitm_max_n(size_t max_n) {
        mitm_max_n = max_n;
    }

    void generate_w(Xorshift& engine) {
        w = vector<double>(n);
        for (int i = 0; i < n; ++i) {
            do {
                w[i] = max(min_w, -log(1.0 - engine.random()) / lambda);
            } while (w[i] > max_w);
        }
        update_sum_w();
    }

    void update_sum_w() {
        sum_w = accumulate(w.begin(), w.end(), 0.0);
    }

    void set_order(const vector<int>& order) {
        assert(order.size() == static_cast<size_t>(n));
        vector<double> v = w;
        sort(v.begin(), v.end());
        for (int i = 0; i < n; ++i) {
            w[order[i]] = v[i];
        }
    }

    void latest_update(const History& history, bool converge) {
        if (history.data.empty()) {
            return;
        }
        if (update(history, history.data.size() - 1)) {
            converged = false;
            if (converge) {
                update_all(history);
            }
        }
    }

    void kick(Xorshift& engine, const History& history) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            do {
                v[i] = max(min_w, -log(1.0 - engine.random()) / lambda);
            } while (v[i] > max_w);
        }
        sort(v.begin(), v.end());

        // order = argsort(w)
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(),
            [&](int a, int b) {
                return w[a] < w[b];
            }
        );
        for (int i = 0; i < n; ++i) {
            w[order[i]] = v[i];
        }
        update_all(history);
    }

    void update_all(const History& history) {
        converged = false;
        size_t cnt = history.data.size();
        int i = max_updates * history.data.size();
        while (cnt && i-- >= 0) {
            if (update(history, i % history.data.size())) {
                cnt = history.data.size();
            } else {
                --cnt;
            }
        }
        if (cnt == 0) {
            converged = true;
        }
        update_sum_w();
    }

    bool update(const History& history, int i) {
        const auto& [l, r, res] = history.data[i];
        double ls = sum(l);
        double rs = sum(r);
        if (res == '<' && ls < rs) {
            return false;
        }
        double delta = (ls - rs) / 2.0;
        if (res == '<') {
            delta *= delta_ampllification;
        }
        scale((ls - delta) / ls, l);
        scale((rs + delta) / rs, r);
        return res == '<';
    }

    double sum(const vector<int>& g) {
        double ret = 0.0;
        for (int i : g) {
            ret += w[i];
        }
        return ret;
    }

    double sum(const ItemSet& l) {
        return sum(bitset_to_vector(l));
    }

    void scale(double rate, const vector<int>& l) {
        for (int i : l) {
            w[i] = min(max(min_w, w[i] * rate), max_w);
        }
    }

    pair<ItemSet,ItemSet> partition(ItemSet l, ItemSet r, Xorshift& engine, double temperature) {
        assert(l.any() && r.any());
        assert(!(l & r).any());
        double ls = sum(l);
        double rs = sum(r);
        if (l.count() == 1 && ls > rs) {
            return {r, l};
        }
        if (r.count() == 1 && ls < rs) {
            return {l, r};
        }
        auto [l1, l2] = split(l, engine, temperature, abs(ls - rs));
        auto [r1, r2] = split(r, engine, temperature, abs(ls - rs));
        double l2s = sum(l2);
        double r2s = sum(r2);
        if (l2s > r2s) {
            swap(l, r);
            swap(l1, r1);
            swap(l2, r2);
            swap(l2s, r2s);
        }
        int goal = (sum(l1) + sum(r1) - (r2s - l2s)) / 2.0;
        if (goal <= 0) {
            ItemSet rn = vector_to_bitset(r2);
            ItemSet ln = ((l | r) ^ rn);
            return {ln, rn};
        }
        // Meet in the Middle
        vector<vector<int>> lt = enumerate(l1, goal);
        vector<vector<int>> rt = enumerate(r1, goal);
        int l3s = -1;
        int r3s = -1;
        size_t i = lt.back().size() - 1;
        for (size_t j = 0; j < rt.back().size(); ++j) {
            while (lt.back()[i] + rt.back()[j] > goal) {
                --i;
            }
            if (lt.back()[i] + rt.back()[j] > l3s + r3s) {
                l3s = lt.back()[i];
                r3s = rt.back()[j];
            }
        }
        ItemSet l3 = vector_to_bitset(restore(l1, lt, l3s));
        ItemSet r3 = vector_to_bitset(restore(r1, rt, r3s));
        ItemSet rn = (l3 | r3 | vector_to_bitset(r2));
        ItemSet ln = ((l | r) ^ rn);
        return {rn, ln};
    }

    pair<vector<int>,vector<int>> split(const ItemSet& l, Xorshift& engine, double temperature, double diff) {
        diff = max(1.0, 0.25 * diff);
        vector<int> lg = bitset_to_vector(l);
        if (lg.size() <= mitm_max_n) {
            return {lg, {}};
        }
        if (true) {
            vector<pair<double,int>> order(lg.size());
            for (size_t i = 0; i < lg.size(); ++i) {
                order[i] = {engine.uniform(0.0, temperature) + abs(log2(w[lg[i]] / diff)), lg[i]};
            }
            sort(order.begin(), order.end());
            for (size_t i = 0; i < lg.size(); ++i) {
                lg[i] = order[i].second;
            }
        } else {
            // shuffle
            for (size_t i = 0; i < mitm_max_n; ++i) {
                swap(lg[i], lg[engine.randrange(i, lg.size())]);
            }
        }
        vector<int> lh(lg.begin() + mitm_max_n, lg.end());
        lg.erase(lg.begin() + mitm_max_n, lg.end());
        return {lg, lh};
    }

    vector<vector<int>> enumerate(const vector<int>& g, int goal) {
        vector<vector<int>> ret(g.size() + 1);
        ret[0].push_back(0);
        for (size_t i = 0; i < g.size(); ++i) {
            ret[i + 1].reserve(2 * ret[i].size());
            int weight = static_cast<int>(w[g[i]]);
            size_t l = 0;
            size_t r = 0;
            while (r < ret[i].size() && ret[i][l] + weight <= goal) {
                if (ret[i][r] <= ret[i][l] + weight) {
                    ret[i + 1].push_back(ret[i][r++]);
                } else {
                    ret[i + 1].push_back(ret[i][l++] + weight);
                }
            }
            while (r < ret[i].size()) {
                ret[i + 1].push_back(ret[i][r++]);
            }
            while (l < ret[i].size() && ret[i][l] + weight <= goal) {
                ret[i + 1].push_back(ret[i][l++] + weight);
            }
        }
        return ret;
    }

    vector<int> restore(const vector<int>& l1, const vector<vector<int>>& lt, int l3s) {
        vector<int> ret;
        for (int i = static_cast<int>(l1.size()) - 1; i >= 0; --i) {
            if (!binary_search(lt[i].begin(), lt[i].end(), l3s)) {
                l3s -= static_cast<int>(w[l1[i]]);
                ret.push_back(l1[i]);
            }
        }
        assert(l3s == 0);
        return ret;
    }

    double calculate_profit(const ItemSet& i, const ItemSet& j, const ItemSet& l, const ItemSet& r) {
        double mu = sum_w / d;
        double sum_i = sum(i) - mu;
        double sum_j = sum(j) - mu;
        double sum_l = sum(l) - mu;
        double sum_r = sum(r) - mu;
        return max(0.0, sum_i * sum_i + sum_j * sum_j - sum_l * sum_l - sum_r * sum_r);
    }

    void print(const string& filename) {
        ofstream out("estimation/" + filename);
        for (size_t i = 0; i < w.size(); ++i) {
            out << w[i] << (i == w.size() - 1 ? "\n" : " ");
        }
    }
};

struct Comparison {
    int n;
    vector<bitset<100>> to_greater;

    Comparison() {}

    Comparison(int n): n(n) {
        assert(n <= 100);
        to_greater = vector<bitset<100>>(n);
    }

    void set(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(u != v);
        // data[u] < data[v]
        to_greater[u].set(v);
    }

    char compare(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(u != v);
        if (to_greater[u][v]) {
            return '<';
        } else if (to_greater[v][u]) {
            return '>';
        }
        bitset<100> visited;
        dfs(u, visited);
        if (visited[v]) {
            return '<';
        }
        visited.reset();
        dfs(v, visited);
        if (visited[u]) {
            return '>';
        }
        return '?';
    }

    void dfs(int u, bitset<100>& visited) {
        visited.set(u);
        for (int v : bitset_to_vector(to_greater[u])) {
            if (!visited[v]) {
                dfs(v, visited);
            }
            to_greater[u] |= to_greater[v];
        }
    }

    void mix(int u, int v) {
        assert(to_greater[u][v]);
        to_greater[u] = to_greater[v];
        for (int w = 0; w < n; ++w) {
            if (to_greater[w][u]) {
                to_greater[w].set(v);
            } else {
                to_greater[w].reset(v);
            }
        }
    }
};

struct Solver {
    Xorshift engine;
    Timer timer;
    IO io;

    int n, d, q;
    vector<ItemSet> groups;
    History history;
    vector<Estimator> estimators;
    Comparison group_comparison;
    int hill_climbing_start_turn;
    int hill_climbing_start_time;
    int estimator_index;

    Solver() {
        io.input();
        init();
    }

    Solver(const string& filename) {
        io.input(filename);
        init();
    }

    void init() {
        n = io.n;
        d = io.d;
        q = io.q;
        history = History(q);
        estimator_index = 0;
    }

    void solve() {
        if (whether_merge_sort()) {
            vector<int> order(n);
            iota(order.begin(), order.end(), 0);
            merge_sort(order, 0, n);
            history.set_order(order);
            init_estimators();
            for (Estimator& estimator : estimators) {
                estimator.set_order(order);
            }
        } else {
            init_estimators();
        }
        init_groups();
        group_comparison = Comparison(d);

        hill_climbing_start_turn = io.turn;
        hill_climbing_start_time = timer.get_time();
        while (io.turn < q && timer.yet(time_limit)) {
            int start_turn = io.turn;
            hill_climbing();
            if (io.turn == start_turn && !can_use_time(io.turn)) {
                estimators[0].kick(engine, history);
            }
        }
        while (io.turn < q) {
            query(1, 2, false);
        }
        io.print(make_answer(), false);
    }

    ll get_cost() const {
        return io.get_cost(make_answer());
    }

    void init_estimators() {
        int num_estimators = get_num_estimators();
        estimators.clear();
        for (int i = 0; i < num_estimators; ++i) {
            Estimator estimator(n, d, engine);
            estimator.set_mitm_max_n(get_mitm_max_n());
            estimators.emplace_back(estimator);
        }
    }

    int get_num_estimators() {
        if (whether_merge_sort()) {
            return max(1ll, (15000000ll * d) / (static_cast<ll>(n) * (q - io.turn + n) * (q - io.turn + n)));
        } else {
            return max(1ll, (20000000ll * d) / (static_cast<ll>(n) * q * q));
        }
    }

    int merge_sort_threshold() {
        return (log2(n) + 3.0 + 0.05 * log2(d)) * n;
    }

    bool whether_merge_sort() {
        return q > merge_sort_threshold();
    }

    char query(ItemSet l, ItemSet r, bool update_history) {
        ItemSet lr = l & r;
        l ^= lr;
        r ^= lr;
        char res = io.query(l, r);
        if (update_history) {
            history.push_result(l, r, res);
        }
        return res;
    }

    void merge_sort(vector<int>& order, size_t l, size_t r) {
        if (r - l <= 1) {
            return;
        }
        size_t m = (l + r) / 2;
        merge_sort(order, l, m);
        merge_sort(order, m, r);
        vector<int> left(order.begin() + l, order.begin() + m);
        vector<int> right(order.begin() + m, order.begin() + r);
        size_t i = 0;
        size_t j = 0;
        size_t k = l;
        while (i < left.size() && j < right.size()) {
            ItemSet si;
            si.set(left[i]);
            ItemSet sj;
            sj.set(right[j]);
            char res = query(si, sj, false);
            if (res == '<') {
                order[k++] = left[i++];
            } else if (res == '>') {
                order[k++] = right[j++];
            } else {
                history.push_result(si, sj, '=');
                order[k++] = left[i++];
                order[k++] = right[j++];
            }
        }
        while (i < left.size()) {
            order[k++] = left[i++];
        }
        while (j < right.size()) {
            order[k++] = right[j++];
        }
        assert(k == r);
    }

    size_t get_mitm_max_n() {
        if (!whether_merge_sort()) {
            if (q < 5 * n) {
                return 3;
            } else if (q < 7 * n) {
                return 4;
            } else {
                return 5;
            }
        } else {
            if (q < 12 * n) {
                return 7;
            } else if (q < 14 * n) {
                return 8;
            } else if (q < 24 * n) {
                return 9;
            } else {
                return 10;
            }
        }
    }

    void init_groups() {
        groups = vector<ItemSet>(d);
        for (int i = 0; i < n; ++i) {
            groups[i % d].set(i);
        }
    }

    char compare(ItemSet l, ItemSet r) {
        ItemSet lr = l & r;
        l ^= lr;
        r ^= lr;
        if (l == r) {
            return '=';
        } else if (!l.any()) {
            return '<';
        } else if (!r.any()) {
            return '>';
        }
        char res = history.compare(l, r);
        if (res != '?') {
            return res;
        } else if (io.turn == q) {
            return '?';
        } else {
            io.print(make_answer(), true);
            char res = query(l, r, true);
            return res;
        }
    }

    bool can_use_time(double turn) {
        return timer.get_time() < hill_climbing_start_time + (0.9 * time_limit - hill_climbing_start_time) * (turn - hill_climbing_start_turn) / (q - hill_climbing_start_turn);
    }

    double get_temperature() {
        return (n * static_cast<double>(q - io.turn)) / (23000 * d);
    }

    tuple<int,int,ItemSet,ItemSet> get_random_swap_candidate() {
        int i = engine.randrange(d);
        int j = engine.randrange(d - 1);
        if (i <= j) {
            ++j;
        }
        auto [l, r] = estimators[0].partition(groups[i], groups[j], engine, get_temperature());
        return {i, j, l, r};
    }

    tuple<int,int,ItemSet,ItemSet> get_best_swap_candidate() {
        if (!can_use_time(io.turn)) {
            return get_random_swap_candidate();
        }
        Estimator estimator = estimators[0];
        if (estimators.size() > 1) {
            fill(estimator.w.begin(), estimator.w.end(), 0.0);
            for (size_t i = 0; i < estimators.size(); ++i) {
                for (int j = 0; j < n; ++j) {
                    estimator.w[j] += estimators[i].w[j];
                }
            }
            for (int i = 0; i < n; ++i) {
                estimator.w[i] /= estimators.size();
            }
            estimator.update_sum_w();
        }
        vector<double> group_sum(d);
        for (int i = 0; i < d; ++i) {
            group_sum[i] = estimator.sum(groups[i]);
        }
        vector<tuple<double,int,int>> order;
        order.reserve(d * (d - 1) / 2);
        for (int i = 0; i < d; ++i) {
            for (int j = i + 1; j < d; ++j) {
                if (group_sum[i] < group_sum[j]) {
                    order.push_back({group_sum[j] - group_sum[i], i, j});
                } else {
                    order.push_back({group_sum[i] - group_sum[j], j, i});
                }
            }
        }
        sort(order.begin(), order.end());
        tuple<int,int,ItemSet,ItemSet> ret = {-1, -1, 0, 0};
        double max_profit = -numeric_limits<double>::infinity();
        int cnt = 0;
        for (auto [_, i, j] : order) {
            auto [l, r] = estimator.partition(groups[i], groups[j], engine, get_temperature());
            if (l == groups[i] || r == groups[i]) {
                continue;
            }
            double profit = (estimators.size() == 1) ? 0.0 : (0.5 * sqrt(estimators.size()) * estimator.calculate_profit(groups[i], groups[j], l, r));
            for (Estimator& estimator : estimators) {
                profit += estimator.calculate_profit(groups[i], groups[j], l, r);
            }
            if (profit > max_profit) {
                ret = {i, j, l, r};
                max_profit = profit;
            }
            if (++cnt >= 2 * d + 1 && !can_use_time(io.turn)) {
                return ret;
            }
        }
        return ret;
    }

    void hill_climbing() {
        if (can_use_time(io.turn)) {
            double local_turn = io.turn - 0.5;
            size_t estimator_index_copy = estimator_index;
            for (size_t i = estimator_index_copy; i < estimator_index_copy + estimators.size(); ++i) {
                if (can_use_time(local_turn)) {
                    estimators[i % estimators.size()].latest_update(history, true);
                    estimator_index = i;
                } else {
                    estimators[i % estimators.size()].latest_update(history, false);
                }
            }
            estimator_index_copy = estimator_index;
            for (size_t i = estimator_index_copy; i < estimator_index_copy + estimators.size(); ++i) {
                if (!can_use_time(local_turn)) {
                    break;
                }
                estimators[i % estimators.size()].kick(engine, history);
                estimator_index = i;
            }
            bool updated = true;
            while (updated && can_use_time(local_turn)) {
                updated = false;
                for (Estimator& estimator : estimators) {
                    if (!can_use_time(local_turn)) {
                        updated = true;
                        break;
                    }
                    if (!estimator.converged) {
                        estimator.update_all(history);
                        updated = true;
                    }
                }
            }
        } else {
            estimators[0].latest_update(history, true);
        }
        auto [i, j, l, r] = get_best_swap_candidate();
        if (i == -1) {
            return;
        }
        char res = group_comparison.compare(i, j);
        if (res == '?') {
            res = compare(groups[i], groups[j]);
        }
        if (res == '>') {
            swap(i, j);
        } else if (res == '=' || res == '?') {
            return;
        }
        group_comparison.set(i, j);

        res = compare(groups[i], l);
        if (res != '<') {
            return;
        }
        res = compare(groups[i], r);
        if (res != '<') {
            return;
        }
        // improve
        groups[i] = l;
        groups[j] = r;
        group_comparison.mix(i, j);
    }

    vector<int> make_answer() const {
        vector<int> answer = vector<int>(n);
        for (int g = 0; g < d; ++g) {
            for (int i : bitset_to_vector(groups[g])) {
                answer[i] = g;
            }
        }
        return answer;
    }
};

void multi_test(int cases) {
    if (cases <= 0) {
        return;
    }
    cerr << "cases: " << cases << endl;

    vector<double> costs(cases);
    vector<double> times(cases);

#ifndef ONLINE_JUDGE
    #pragma omp parallel for
#endif
    for (int seed = 0; seed < cases; ++seed) {
        string filename = to_string(seed);
        filename = string(4 - filename.size(), '0') + filename + ".txt";

        Solver solver(filename);
        solver.solve();
        solver.estimators[0].print(filename);

        times[seed] = solver.timer.get_time();
        ll cost = solver.get_cost();
        costs[seed] = log2(cost);

        cerr << filename << " " << cost << " " << times[seed] << " sec" << endl;
    }
    cerr << "Average Cost: " << accumulate(costs.begin(), costs.end(), 0.0) / cases << endl;
    cerr << "Max Time: " << *max_element(times.begin(), times.end()) << " sec" << endl;
    cerr << "Average Time: " << accumulate(times.begin(), times.end(), 0.0) / cases << " sec" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Solver solver;
    solver.solve();

    return 0;
}
