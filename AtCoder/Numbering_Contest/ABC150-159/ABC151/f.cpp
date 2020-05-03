#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vb=vector<bool>;
using vvb=vector<vb>;
using vd=vector<double>;
using vvd=vector<vd>;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pll=pair<ll,ll>;
using tll=tuple<ll,ll>;
using tlll=tuple<ll,ll,ll>;
using vs=vector<string>;
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define rrep(i,n) for(ll i=(n)-1;i>=0;i--)
#define range(i,a,n) for(ll i=(a);i<(n);i++)
#define LINF ((ll)1ll<<60)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define fs first
#define sc second
#define PI (3.1415926535897932384)

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll max(int a,ll b){return max((ll)a,b);} ll max(ll a,int b){return max(a,(ll)b);}
int sgn(const double&r){return (r>EPS)-(r<-EPS);} // a>0  : sgn(a)>0
int sgn(const double&a,const double&b){return sgn(a-b);} // b<=c : sgn(b,c)<=0

template<class T>void puta(T&&t){cout<<t<<"\n";}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}
template<class S,class T>void tf(bool b,S t,T f){if(b)puta(t);else puta(f);}
void YN(bool b){tf(b,"YES","NO");}
void Yn(bool b){tf(b,"Yes","No");}
void yn(bool b){tf(b,"yes","no");}
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1;for(auto s:t){os<<(a?"":" ")<<s;a=0;}return os;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}

/*他のライブラリを入れる場所*/
using ld = long double;
using P = std::complex<ld>;
using G = std::vector<P>;
const ld pi = std::acos(-1);
const ld eps = 1e-10;
const ld inf = 1e12;

ld cross(const P &a, const P &b) { return a.real() * b.imag() - a.imag() * b.real(); }
ld dot(const P &a, const P &b) { return a.real() * b.real() + a.imag() * b.imag(); }

/*
                    CCW

 -- BEHIND -- [a -- ON -- b] --- FRONT --

                    CW
 */
enum CCW_RESULT { CCW = +1, CW = -1, BEHIND = +2, FRONT = -2, ON = 0 };
int ccw(P a, P b, P c) {
    b -= a;
    c -= a;
    if (cross(b, c) > eps) return CCW;    // counter clockwise
    if (cross(b, c) < -eps) return CW;    // clockwise
    if (dot(b, c) < 0) return BEHIND;     // c--a--b on line
    if (norm(b) < norm(c)) return FRONT;  // a--b--c on line
    return ON;
}

namespace std {
bool operator<(const P &a, const P &b) {
    return std::abs(real(a) - real(b)) > eps ? real(a) < real(b) : imag(a) < imag(b);
}
}

struct L : public std::vector<P> {
    L(const P &a = P(), const P &b = P()) : std::vector<P>(2) {
        begin()[0] = a;
        begin()[1] = b;
    }

    // Ax + By + C = 0
    L(ld A, ld B, ld C) {
        if (std::abs(A) < eps && std::abs(B) < eps) {
            abort();
        } else if (std::abs(A) < eps) {
            *this = L(P(0, -C / B), P(1, -C / B));
        } else if (std::abs(B) < eps) {
            *this = L(P(-C / A, 0), P(-C / A, 1));
        } else {
            *this = L(P(0, -C / B), P(-C / A, 0));
        }
    }
};

struct C {
    P p;
    ld r;
    C(const P &p = 0, ld r = 0) : p(p), r(r) {}
};

using iter=G::iterator;
std::pair<P, ld> min_ball(iter left, iter right, int seed = 1333) {
    const int n = right - left;

    assert(n >= 1);
    if (n == 1) {
        return {*left, ld(0)};
    }

    std::mt19937 mt(seed);
    std::shuffle(left, right, mt);
    // std::random_shuffle(left, right); // simple but deprecated

    iter ps = left;
    using circle = std::pair<P, ld>;

    auto make_circle_3 = [](const P &a, const P &b, const P &c) -> circle {
        ld A = std::norm(b - c), B = std::norm(c - a), C = std::norm(a - b),
           S = cross(b - a, c - a);
        P p = (A * (B + C - A) * a + B * (C + A - B) * b + C * (A + B - C) * c) / (4 * S * S);
        ld r2 = std::norm(p - a);
        return {p, r2};
    };

    auto make_circle_2 = [](const P &a, const P &b) -> circle {
        P c = (a + b) / (ld)2;
        ld r2 = std::norm(a - c);
        return {c, r2};
    };

    auto in_circle = [](const P &a, const circle &c) -> bool {
        return std::norm(a - c.first) <= c.second + eps;
    };

    circle c = make_circle_2(ps[0], ps[1]);

    // MiniDisc
    for (int i = 2; i < n; ++i) {
        if (!in_circle(ps[i], c)) {
            // MiniDiscWithPoint
            c = make_circle_2(ps[0], ps[i]);
            for (int j = 1; j < i; ++j) {
                if (!in_circle(ps[j], c)) {
                    // MiniDiscWith2Points
                    c = make_circle_2(ps[i], ps[j]);
                    for (int k = 0; k < j; ++k) {
                        if (!in_circle(ps[k], c)) {
                            c = make_circle_3(ps[i], ps[j], ps[k]);
                        }
                    }
                }
            }
        }
    }
    return c;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n;
    cin>>n;
    vector<P> p(n);
    rep(i,n){
        ll a,b;cin>>a>>b;
        p[i]=P(a,b);
    }
    fcout(10)<<(sqrt(min_ball(all(p)).sc))<<endl;;
    return 0;
}