// Generator.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>
#include <set>
#include <numeric>
#include <cmath>
#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>
#include <random>
#include <chrono>
#include <limits>


using namespace std;

constexpr double EPS = 1e-9;
const double PI = acos(-1);

struct xorshift128 {

    const unsigned int ini_x = 123456789, ini_y = 362436069, ini_z = 521288629, ini_w = 88675123;
    unsigned int x, y, z, w;

    xorshift128() {}

    // シードによってx,y,z,wを初期化 ... initialize x,y,z,w by seed
    void set_seed(unsigned int seed) {
        x = ini_x, y = ini_y, z = ini_z, w = ini_w ^ seed;
    }

    unsigned int randint() {
        unsigned int t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    // [0,r)の範囲の整数で乱数発生 ... generate random integer in [0,r)
    unsigned int randint(unsigned int r) {
        assert(r != 0);
        return randint() % r;
    }

    // [l,r)の範囲の整数で乱数発生 ... generate random integer in [l,r)
    unsigned int randint(unsigned int l, unsigned int r) {
        assert(r > l);
        return l + randint(r - l);
    }

    // 長さnの順列をランダムに生成し、その前k個分を出力する ... generate a random permutation of size n, and return the first k
    vector<int> randperm(int n, int k) {
        assert(k >= 0 && k <= n);
        vector<int> ret(n);
        for (int i = 0; i < n; i++) {
            ret[i] = i;
        }
        for (int i = 0; i < k; i++) {
            swap(ret[i], ret[randint(i, n)]);
        }
        return vector<int>(ret.begin(), ret.begin() + k);
    }


    // [0,1]の範囲の実数で乱数発生 ... generate random real number in [0,1]
    double uniform() {
        return double(randint()) * 2.3283064370807974e-10;
    }

    // [0,r]の範囲の実数で乱数発生 ... generate random real number in [0,r]
    double uniform(double r) {
        assert(r >= 0.0);
        return uniform() * r;
    }

    // [l,r]の範囲の実数で乱数発生 ... generate random real number in [l,r]
    double uniform(double l, double r) {
        assert(r >= l);
        return l + uniform(r - l);
    }

    // normal distribution (μ = mean, σ = sigma) 
    double normal(double mean,double sigma) {
        double x = sqrt(-2.0 * log(uniform())) * sin(2.0 * PI * uniform());
        return mean + sigma * x;
    }

    // 要素[l,r)からなる長さnの数列を生成 ... Generate a sequence of numbers of length n consisting of elements [l,r)
    vector<int> randseq(int n, int l, int r) {
        vector<int> ret(n);
        for (int i = 0; i < n; i++) {
            ret[i] = randint(l, r);
        }
        return ret;
    }
};

xorshift128 Random;

// 文字列をスペース区切りで分割 ... seperate string with a whitespace character 
vector<string> split(string S) {
    vector<string> ret;
    string temp;
    for (char c : S) {
        if (c == ' ') {
            if (!temp.empty()) ret.push_back(temp);
            temp.clear();
        }
        else {
            temp += c;
        }
    }
    ret.push_back(temp);
    return ret;
}


void generate_testcase(int t, string INPUT, string outputfile_name) {

    unsigned long long sd = 0;                  // seed


    // 入力によるパラメータ変更 ... process input parameter
    vector<string> argv = split(INPUT);
    int argc = argv.size();

    for (int i = 0; i < argc - 1; i += 2) {
        string temp = argv[i];
        if (temp == "-seed") {
            sd = stoull(argv[i + 1]);
        }
    }


    Random.set_seed(sd);

    int N = Random.randint(1000, 5000 + 1);     // 製造数量 ... production
    int S = Random.randint(4, 10 + 1);          // 形状の種類数 ... Shape types
    int C = Random.randint(4, 10 + 1);          // 色の種類数 ... Color types
    int H = 250;                                // フック数 ... hucks
    int _a = Random.randint(1, 100 + 1);        // 重みα ... weight α
    int _b = Random.randint(1, 500 + 1);        // 重みβ ... weight β
    int a = std::min<int>(99, ceil((double)_a / (_a + _b) * 100));
    int b = 100 - a;

    // コマンドラインで指定されているパラメータをセット ... Setting parameters specified in the command line
    for (int i = 0; i < argc - 1; i += 2) {
        string temp = argv[i];
        if (temp == "-N") {
            N = stoi(argv[i + 1]);
        }
        else if (temp == "-S") {
            S = stoi(argv[i + 1]);
        }
        else if (temp == "-C") {
            C = stoi(argv[i + 1]);
        }
        //else if (temp == "-H") {
        //   H = stoi(argv[i + 1]);
        //}
        else if (temp == "-a") {
            a = stoi(argv[i + 1]);
        }
        else if (temp == "-b") {
            b = stoi(argv[i + 1]);
        }
        else if (temp == "-seed") {
        }
        else {
            cerr << "unknown option: " << argv[i] << '\n';
            exit(0);
        }
    }

    vector<int> K(S);                               // 形状ごとのハンガー数 ... Number of hangers per shape
    vector<vector<int>> Nsc(S, vector<int>(C, 0));  // (s,c)の製造数量 ... Production Quantity (s,c)
    vector<vector<int>> S_setup(S, vector<int>(S)); // s→s'の切り替えに必要な空き間隔 ... required interval for switching from s to s'.
    vector<vector<int>> C_setup(C, vector<int>(C)); // c→c'の切り替えに必要な空き間隔 ... required interval for switching from c to c'.

    // 製造数量 N_{s,c}の決定 ... Calclation of production quantity N_{s,c}
    {

        double W_sum = 0.0;
        vector<vector<double>> W(S, vector<double>(C));
        vector<double> a(S), b(C);
        auto dist = []() {return Random.normal(0.0, 0.5); };

        for (int i = 0; i < S; i++) {
            a[i] = dist();
        }
        for (int i = 0; i < C; i++) {
            b[i] = dist();
        }
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < C; j++) {
                W[i][j] = exp( a[i] + b[j] );
                W_sum += W[i][j];
            }
        }
        for (int i = 0; i < N; i++) {
            double sum = 0.0;
            double t = Random.uniform(0, W_sum);
            for (int j = 0; j < S * C; j++) {
                int s = j / C;
                int c = j % C;
                sum += W[s][c];
                if (sum < t + EPS) continue;
                Nsc[s][c]++;
                break;
            }
        }
    }

    //ハンガー数 K_{i} の決定 ... Calculation of the number of hangers K_{i}
    {
        for (int i = 0; i < S; i++) {
            double sum = std::accumulate(Nsc[i].begin(), Nsc[i].end(), 0);
            K[i] = std::clamp((int)ceil(H * (sum / N) * Random.uniform(1.2, 1.5)), 1, H);
        }
    }

    // 切り替え間隔の決定
    // 形状・色を3次元空間にランダムにマッピング．
    // 形状間・色間のユークリッド距離に基づいて切り替え間隔を決定．
    // Calculate the switching interval
    // randomly map the shapes and colors into 3D space.
    // interval calculated by Euclidean distance between shapes and colors.
    {
        struct Point { 
            double x = 0, y = 0,z = 0;
            Point() {}
            Point(double x, double y,double z) :x(x), y(y), z(z) {}
            double diff(Point& p) {
                return hypot(abs(p.x - x), abs(p.y - y), abs(p.z - z));
            }
            Point* operator +=(Point r) {
                this->x += r.x;
                this->y += r.y;
                this->z += r.z;
                return this;
            }
        };

        //形状切り替え時の空きフック数 A_{(i,j)} の決定 ... Calculation of shape switching interval
        {
            auto DistGroup = []() {return Random.normal(0.0, 100.0); };
            auto DistShape = []() {return Random.normal(0.0, 10.0); };

            int N_ShapeGroup = Random.uniform(1, S + 1);                    // 形状グループ数　... Number of shape groups
            std::vector< int > Group = Random.randseq(S, 0, N_ShapeGroup);  // グループ割り当て ... Grouping
            std::vector< Point > GroupBasePoint(N_ShapeGroup);  // グループの基準座標 ... Base coordinates of the group
            std::vector< Point > ShapePoint(S);                 // 形状の座標 ... Coordinates of the shape

            // グループを3次元空間にマッピング ... Mapping groups in 3D space
            for (int i = 0; i < N_ShapeGroup; i++) {
                GroupBasePoint[i] = Point(DistGroup(), DistGroup(), DistGroup());
            }

            // 形状を3次元空間にマッピング ... Mapping shapes in 3D space
            for (int i = 0; i < S; i++) {
                Point p = GroupBasePoint[Group[i]];
                p += Point(DistShape(), DistShape(), DistShape());
                ShapePoint[i] = p;
            }

            double S_MAX = std::numeric_limits<double>::min();
            double S_MIN = std::numeric_limits<double>::max();

            for (int i = 0; i < S; i++) {
                for (int j = 0; j < S; j++) {
                    Point p1 = ShapePoint[i];
                    Point p2 = ShapePoint[j];

                    S_setup[i][j] = i == j ? 0 : ceil(p1.diff(p2));
                    if (S_setup[i][j] == 0)continue;
                    S_MAX = std::max(S_MAX, (double)S_setup[i][j]);
                    S_MIN = std::min(S_MIN, (double)S_setup[i][j]);
                }
            }

            // S_setupの要素を[S_setup_MIN, S_setup_MAX]の範囲に正規化 ... Normalize the elements of S_setup to the range [S_setup_MIN, S_setup_MAX
            double S_setup_MAX = Random.uniform(10,20);
            double S_setup_MIN = Random.uniform(1,5);
            for (int i = 0; i < S; i++) {
                for (int j = 0; j < S; j++) {
                    if (S_setup[i][j] == 0) continue;
                    double _S = ((double)S_setup[i][j] - S_MIN + EPS) / (S_MAX - S_MIN + EPS);
                    S_setup[i][j] = ceil((S_setup_MAX - S_setup_MIN) * _S + S_setup_MIN);
                }
            }
        }

        //色切り替え時の空きハンガー数 B_{(i,j)} の決定 ... Calculation of color switching interval
        {
            auto DistGroup = []() {return Random.normal(0.0, 100.0); };
            auto DistColor = []() {return Random.normal(0.0, 10.0); };

            int N_ColorGroup = Random.uniform(1, C + 1);                    //色グループ数 ... Number of color groups
            std::vector< int > Group = Random.randseq(C, 0, N_ColorGroup);  //色のグループ割り当て ... Grouping
            std::vector< Point > GroupBasePoint(N_ColorGroup);  // グループの基準座標 ... Base coordinates of the group
            std::vector< Point > ColorPoint(C);                 // 色の座標 ... Coordinates of the color

            // グループを3次元空間にマッピング ... Mapping groups in 3D space
            for (int i = 0; i < N_ColorGroup; i++) {
                GroupBasePoint[i] = Point(DistGroup(), DistGroup(), DistGroup());
            }

            // 色を3次元空間にマッピング ... Mapping shapes in 3D space
            for (int i = 0; i < C; i++) {
                Point p = GroupBasePoint[Group[i]];
                p += Point(DistColor(), DistColor(), DistColor());
                ColorPoint[i] = p;
            }

            double C_MAX = std::numeric_limits<double>::min();
            double C_MIN = std::numeric_limits<double>::max();

            for (int i = 0; i < C; i++) {
                for (int j = 0; j < C; j++) {
                    Point p1 = ColorPoint[i];
                    Point p2 = ColorPoint[j];

                    C_setup[i][j] = i == j ? 0 : ceil(p1.diff(p2));
                    if (C_setup[i][j] == 0)continue;
                    C_MAX = std::max(C_MAX, (double)C_setup[i][j]);
                    C_MIN = std::min(C_MIN, (double)C_setup[i][j]);
                }
            }

            // C_setupの要素を[C_setup_MIN, C_setup_MAX]の範囲に正規化 ... Normalization
            double C_setup_MAX = Random.uniform(15, 40);
            double C_setup_MIN = Random.uniform(5, 10);
            for (int i = 0; i < C; i++) {
                for (int j = 0; j < C; j++) {
                    if (C_setup[i][j] == 0) continue;
                    double _C = ((double)C_setup[i][j] - C_MIN + EPS) / (C_MAX - C_MIN + EPS);
                    C_setup[i][j] = ceil((C_setup_MAX - C_setup_MIN) * _C + C_setup_MIN);
                }
            }
        }
    }

    // テストケースを出力 ... output testcase
    {
        string OUTPUT = to_string(t);
        while (OUTPUT.size() < 4) OUTPUT = '0' + OUTPUT;
        OUTPUT = outputfile_name + OUTPUT;
        OUTPUT += ".txt";
        ofstream outputfile(OUTPUT);

        outputfile << S << ' ' << C << ' ' << H << ' ' << a << ' ' << b << '\n';
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < C; j++) {
                outputfile << Nsc[i][j] << (j == C - 1 ? '\n' : ' ');
            }
        }
        for (int i = 0; i < S; i++) {
            outputfile << K[i] << (i == S - 1 ? '\n' : ' ');
        }
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < S; j++) {
                outputfile << S_setup[i][j] << (j == S - 1 ? '\n' : ' ');
            }
        }
        for (int i = 0; i < C; i++) {
            for (int j = 0; j < C; j++) {
                outputfile << C_setup[i][j] << (j == C - 1 ? '\n' : ' ');
            }
        }
        outputfile.close();
    }


}

int main(int argc, char* argv[]) {


    string outputfile_name = "input";
    if (argc >= 2) outputfile_name = argv[1];
    string INPUT;
    for (int t = 1; getline(cin, INPUT); t++) {
        generate_testcase(t, INPUT, outputfile_name);
    }


}

