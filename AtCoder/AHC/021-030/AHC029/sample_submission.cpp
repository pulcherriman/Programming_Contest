#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

constexpr int MAX_INVEST_LEVEL = 20;

struct Project {
    int64_t h;
    int64_t v;
};

enum class CardType {
    WORK_SINGLE = 0,
    WORK_ALL = 1,
    CANCEL_SINGLE = 2,
    CANCEL_ALL = 3,
    INVEST = 4,
};

ostream& operator<<(ostream& os, CardType ct) {
    switch(ct) {
        case CardType::WORK_SINGLE:
            os << "WORK_SINGLE";
            break;
        case CardType::WORK_ALL:
            os << "WORK_ALL";
            break;
        case CardType::CANCEL_SINGLE:
            os << "CANCEL_SINGLE";
            break;
        case CardType::CANCEL_ALL:
            os << "CANCEL_ALL";
            break;
        case CardType::INVEST:
            os << "INVEST";
            break;
    }
    return os;
}

struct Card {
    CardType t;
    int64_t w;
    int64_t p;
};


struct Judge {
    const int n;
    const int m;
    const int k;

    Judge(int n, int m, int k): n(n), m(m), k(k) {}

    vector<Card> read_initial_cards() {
        vector<Card> cards;
        for (int i = 0; i < n; i++) {
            int64_t t, w;
            cin >> t >> w;
            cards.push_back(Card{(CardType)t, w, 0ll});
        }
        return cards;
    }

    vector<Project> read_projects() {
        vector<Project> projects;
        for (int i = 0; i < m; i++) {
            int64_t h, v;
            cin >> h >> v;
            projects.push_back(Project{h, v});
        }
        return projects;
    }

    void use_card(int c, int m) {
        cout << c << " " << m << endl;
    }

    int64_t read_money() {
        int64_t money;
        cin >> money;
        return money;
    }

    vector<Card> read_next_cards() {
        vector<Card> cards;
        for (int i = 0; i < k; i++) {
            int64_t t, w, p;
            cin >> t >> w >> p;
            cards.push_back(Card{(CardType)t, w, p});
        }
        return cards;
    }

    void select_card(int r) {
        cout << r << endl;
    }

    void comment(const string& message) {
        cout << "# " << message << endl;
    }
};

struct Solver {
    const int n;
    const int m;
    const int k;
    const int t;
    Judge judge;
    int turn;
    int invest_level;
    int64_t money;
    vector<Project> projects;
    vector<Card> cards;


    Solver(int n, int m, int k, int t) : 
        n(n), m(m), k(k), t(t), judge(n, m, k), turn(0), invest_level(0), money(0) {
    }

    int64_t solve() {
        cards = judge.read_initial_cards();
        projects = judge.read_projects();
        for (turn = 0; turn < t; ++turn) {
            auto [use_card_i, use_target] = select_action();
            const Card& use_card = cards[use_card_i];
            if (use_card.t == CardType::INVEST) {
                invest_level++;
            }
            // example for comments
            stringstream msg;
            msg << "used Card(t=" << use_card.t << " w=" << use_card.w << " p=" << use_card.p << ") to target " << use_target;
            judge.comment(msg.str());
            judge.use_card(use_card_i, use_target);
            assert(invest_level <= MAX_INVEST_LEVEL);

            projects = judge.read_projects();
            money = judge.read_money();

            vector<Card> next_cards = judge.read_next_cards();
            int select_card_i = select_next_card(next_cards);
            cards[use_card_i] = next_cards[select_card_i];
            judge.select_card(select_card_i);
            money -= next_cards[select_card_i].p;
            assert(money >= 0);
        }
        return money;
    }

    pair<int, int> select_action() {
        // TODO: implement your strategy
        return {0, 0};
    }

    int select_next_card(const vector<Card>& next_cards) {
        // TODO: implement your strategy
        return 0;
    }
};

int main() {
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    Solver solver(n, m, k, t);
    int64_t score = solver.solve();
    cerr << "score:" << score << endl;
}
