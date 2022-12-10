#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#else
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

/* 
 * Include Headers
 */
#if defined(EVAL) || defined(ONLINE_JUDGE) || defined(_DEBUG)
// #include <atcoder/all>
// using namespace atcoder;
#endif
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

/*
 * Additional Type Definition
 */
using ll=long long;
using ld=long double;
using ull=unsigned long long;
using vb=vector<bool>;
using vvb=vector<vb>;
using vd=vector<ld>;
using vvd=vector<vd>;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using vp=vector<pll>;
using tl2=tuple<ll,ll>;
using tl3=tuple<ll,ll,ll>;
using vs=vector<string>;
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;
template<class V> using minpq = priority_queue<V, vector<V>, greater<V>>;

#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i=((ll)(n)-1);i>=((ll)a);--i)
#define sz(a) ((ll)(a).size())

/*
 * Constants
 */
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-14);
constexpr ll MOD=998244353ll;
constexpr long double PI=3.14159265358979323846;

/*
 * Utilities
 */
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

namespace IO {
	// container detection
	template<typename T, typename _=void> struct is_container : false_type {};
	template<> struct is_container<string> : false_type {};
	template<class T> struct is_container<valarray<T>> : true_type {};
	template<typename...Ts> struct is_container_helper {};
	template<typename T> struct is_container<T, conditional_t<
		true, void, is_container_helper<
			typename T::value_type, typename T::size_type, typename T::iterator,
			decltype(declval<T>().size()),
			decltype(declval<T>().begin()),
			decltype(declval<T>().end()) >>> : public true_type {};
	template<typename T,
		typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr,
		char Separator = is_container<typename T::value_type>{} ? '\n' : ' ' >
	constexpr ostream&operator<<(ostream&os, T t){
		if(auto b=begin(t), e=end(t) ; t.size()) for(os<<(*b++);b!=e;os<<Separator<<(*b++)) ;
		return os;
	}

	// output
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args); // support clang
	template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){ return os<<'['<<p.first<<", "<<p.second<<']'; };
	template<class...Ts>constexpr ostream&operator<<(ostream&os,tuple<Ts...>t){
		return apply([&os](auto&&t,auto&&...args)->ostream&{return pargs(os, t, args...);}, t);
	};
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args) {
		return ((os<<t)<<...<<(os<<' ', args));
	}

	template<class...Ts> constexpr ostream& out(Ts...args) { return pargs(cout, args...)<<'\n'; }
	template<class...Ts> constexpr ostream& debug_f(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#ifdef _DEBUG
	template<class...Ts> constexpr ostream& debug(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#else
	#define debug(...) if(false)debug_f(__VA_ARGS__)
	#endif
	void Yn(bool f) { out(f?"Yes":"No"); }

	// input
	template<class T, class...Ts> constexpr istream& gargs(istream&is, T&&t, Ts&&...args) {
		return ((is>>t)>>...>>args);
	}
	template<class S,class T>auto&operator>>(istream&is,pair<S,T>&p){return is>>p.first>>p.second;}
	template<class...Ts>constexpr istream&operator>>(istream&is,tuple<Ts...>&t){
		return apply([&is](auto&&t,auto&&...args)->istream&{return gargs(is, t, args...);}, t);
	};

	template<typename...S>auto&in(S&...s){return gargs(cin, s...);}
	#define def(t,...) t __VA_ARGS__; in(__VA_ARGS__)
	template<typename T, typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr>
	auto&operator>>(istream&is,T&t){for(auto&a:t)is>>a; return is;}
}
using namespace IO;

class Random {
public:
	typedef uint_fast32_t result_type;
	constexpr result_type operator()(){return operator()((ll)min(),(ll)max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
	constexpr double operator()(double a,double b){return (b-a)*next()/4294967296.0+a;}
private:
	result_type y;
	constexpr result_type next(){return y^=(y^=(y^=y<<13)>>17)<<5;}
} Random(0);

class Timer {
	#ifdef _DEBUG
	static constexpr uint64_t ClocksPerMsec = 3587000;
	#else
	static constexpr uint64_t ClocksPerMsec = 2987000;
	#endif
	const uint64_t start,limit;
	uint64_t getClocks() const{
		unsigned int lo,hi;
		__asm__ volatile ("rdtsc" : "=a" (lo), "=d" (hi));
		return((uint64_t)hi<<32)|lo;
	}
public:
	Timer(uint64_t _limit=1970): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 2000;
	static inline Timer timer = Timer(TLE-20);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(11);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

namespace std::tr1 {
	template<class T>
	struct hash_base {
		const static inline size_t hash_value = 0x9e3779b9;
		static inline size_t hash_rnd = Random(0, numeric_limits<size_t>::max());
		template<class V> static size_t& do_hash(size_t&seed, V&v) {
			return seed ^= hash<V>{}(v) + hash_value + (seed<<6) + (seed>2);
		}
		virtual size_t operator()(T p) const = 0;
	};

	template<class S, class T>
	struct hash<pair<S,T>> : public hash_base<pair<S,T>> {
		size_t operator()(pair<S,T> p) const {
			size_t seed = 0;
			this->do_hash(seed, p.first);
			this->do_hash(seed, p.second);
			return this->do_hash(seed, this->hash_value);
		}
	};
}


// template <typename T, int MAX_LOG, int NODES = 16777216>
// struct BinaryTrie {
//   using Container = vector<int>;
//   struct Node {
//     Node *nxt[2];
//     int exist;
//     Container accept;
//     Node() {}
//   };

//   Node *pool;
//   int pid;
//   T lazy;
//   Node *nil;
//   Node *root;

//   BinaryTrie() : pid(0), lazy(T(0)), nil(nullptr) {
//     pool = new Node[NODES];
//     nil = my_new();
//     nil->nxt[0] = nil->nxt[1] = root = nil;
//   }

//   Node *my_new(int exist_ = 0, int id = -1) {
//     pool[pid].nxt[0] = pool[pid].nxt[1] = nil;
//     pool[pid].exist = exist_;
//     if (id != -1) pool[pid].accept.push_back(id);
//     return &(pool[pid++]);
//   }

//   Node *merge(Node *l, Node *r) {
//     pool[pid].nxt[0] = l;
//     pool[pid].nxt[1] = r;
//     pool[pid].exist = l->exist + r->exist;
//     return &(pool[pid++]);
//   }

//  private:
//   Node *add_(const T &x, int id, Node *n, int bit_idx) {
//     if (bit_idx == -1) {
//       if (n == nil) return my_new(1, id);
//       n->exist++;
//       n->accept.push_back(id);
//       return n;
//     } else {
//       if (((lazy >> bit_idx) & 1) == ((x >> bit_idx) & 1))
//         return merge(add_(x, id, n->nxt[0], bit_idx - 1), n->nxt[1]);
//       else
//         return merge(n->nxt[0], add_(x, id, n->nxt[1], bit_idx - 1));
//     }
//   }

//  public:
//   void add(const T &x, int id = -1) { root = add_(x, id, root, MAX_LOG); }

//  private:
//   T max_element_(Node *n, int bit_idx) {
//     if (bit_idx == -1) return 0;
//     if (n->nxt[~(lazy >> bit_idx) & 1]->exist) {
//       auto ret = max_element_(n->nxt[~(lazy >> bit_idx) & 1], bit_idx - 1);
//       ret |= T(1) << bit_idx;
//       return ret;
//     } else {
//       return max_element_(n->nxt[(lazy >> bit_idx) & 1], bit_idx - 1);
//     }
//   }

//  public:
//   T max_element() { return max_element_(root, MAX_LOG); }

//   void operate_xor(T x) { lazy ^= x; }
// };

// BinaryTrie<int,30,32*150000> bt;


template <typename Key = uint32_t, int KeyLog = 30,
          int bitlen = sizeof(Key) * 8>
struct binary_trie {
    struct node {
        Key k;
        int l, r, count;
        int ch[2];
        node(Key _k = 0, int _l = 0, int _r = 0)
            : k(_k), l(_l), r(_r), count(0) {
            ch[0] = ch[1] = -1;
        }
    };
    const int root = 0; int sz = 0;
    std::vector<node> nodes{node()};
    static Key mask(int l, int r) { return ((1LL << (r - l + 1)) - 1) << l; }
    binary_trie() {}
    int make_node(Key x, int l, int r) {
        nodes.push_back(node(x, l, r));
        return ++sz;
    }
    int next_bit(int v, Key k) {
        Key x = (nodes[v].k ^ k) & mask(nodes[v].l, nodes[v].r);
        if constexpr (bitlen > 32)
            return (x ? bitlen - 1 - __builtin_clzll(x) : -1);
        return (x ? bitlen - 1 - __builtin_clz(x) : -1);
    }
    void insert(Key x, int k = 1) {
        int v = root;
        int bit = KeyLog - 1;
        while (bit >= 0) {
            nodes[v].count += k;
            int nxt = (x >> bit) & 1;
            if (nodes[v].ch[nxt] == -1) {
                nodes[v].ch[nxt] = make_node(x, 0, bit);
                nodes[nodes[v].ch[nxt]].count = k;
                return;
            }
            v = nodes[v].ch[nxt];
            int diff_bit = std::max(nodes[v].l - 1, next_bit(v, x));
            if (diff_bit == nodes[v].l - 1) {
                bit = diff_bit;
            } else {
                nxt = (x >> diff_bit) & 1;
                int tmp = make_node(nodes[v].k, nodes[v].l, diff_bit);
                nodes[v].l = diff_bit + 1;
                nodes[tmp].count = nodes[v].count;
                nodes[v].count += k;
                nodes[tmp].ch[!nxt] = nodes[v].ch[!nxt];
                nodes[tmp].ch[nxt] = nodes[v].ch[nxt];
                nodes[v].ch[!nxt] = tmp;
                nodes[v].ch[nxt] = make_node(x, 0, diff_bit);
                nodes[nodes[v].ch[nxt]].count = k;
                return;
            }
        }
        nodes[v].count += k;
    }
    int find(Key x, int v, int bit) {
        v = nodes[v].ch[(x >> bit) & 1];
        if (!v) return 0;
        int diff_bit = std::max(nodes[v].l - 1, next_bit(v, x));
        if (diff_bit != nodes[v].l - 1) return 0;
        if (nodes[v].l == 0) return nodes[v].count;
        return find(x, v, diff_bit);
    }
    int count(int v) { return (v == -1 ? 0 : nodes[v].count); }
    int erase(Key x, int k, int v, int bit) {
        v = nodes[v].ch[(x >> bit) & 1];
        if (count(v) == 0) return 0;
        int diff_bit = std::max(nodes[v].l - 1, next_bit(v, x));
        if (diff_bit > nodes[v].l - 1) return 0;
        if (nodes[v].l == 0) {
            k = std::min(k, nodes[v].count);
            nodes[v].count -= k;
            return k;
        }
        k = erase(x, k, v, diff_bit);
        nodes[v].count -= k;
        return k;
    }
    int erase(Key x, int k = std::numeric_limits<int>::max()) {
        k = erase(x, k, root, KeyLog - 1);
        nodes[root].count -= k;
        return k;
    }
    int find(Key x) { return find(x, root, KeyLog - 1); }
    int size() { return nodes[root].count; }

    Key xor_min(Key x) {
        return xor_ope(x, false);
    }
    Key xor_max(Key x) {
        return xor_ope(x, true);
    }

    int next(int v, int k, bool is_right) {
        if (v == root || k == nodes[v].l - 1) {
            return nodes[v].ch[is_right];
        } else {
            if (((nodes[v].k >> k) & 1) == is_right)
                return v;
            else
                return -1;
        }
    }

    // bool xor_range_satisfiable(Key x, Key l, Key r) {
    //     if (l >= r) return false;
    //     r--;
    //     int v = root;
    //     for (int i = KeyLog - 1; i >= 0; i--) {
    //         if (((l >> i) & 1) == ((r >> i) & 1)) {
    //             int target = ((x >> i) & 1) ^ ((l >> i) & 1);
    //             v = nodes[next(v, i, target)].ch[target];
    //             if (count(v) == 0) return false;
    //         } else {
    //             int ith = (x >> i) & 1;
    //             int u = next(v, i, ith);
    //             if (u != -1) {
    //                 int j = i - 1;
    //                 for (; j >= 0; j--) {
    //                     if (u == -1) break;
    //                     int target = (l >> j) & 1, flip = (x >> j) & 1;
    //                     int ch_sz = count(next(u, j, flip ^ 1));
    //                     if (target == 1 && ch_sz == 0) break;
    //                     if (target == 0 && ch_sz) return true;
    //                     u = next(u, j, target ^ flip);
    //                 }
    //                 if (j == -1 && count(u)) return true;
    //             }
    //             u = next(v, i, ith ^ 1);
    //             if (u != -1) {
    //                 int j = i - 1;
    //                 for (; j >= 0; j--) {
    //                     if (u == -1) break;
    //                     int target = (r >> j) & 1, flip = (x >> j) & 1;
    //                     int ch_sz = count(next(u, j, flip));
    //                     if (target == 0 && ch_sz == 0) break;
    //                     if (target == 1 && ch_sz) return true;
    //                     u = next(u, j, target ^ flip);
    //                 }
    //                 if (j == -1 && count(u)) return true;
    //             }
    //             return false;
    //         }
    //     }
    //     return true;
    // }

private:
    Key xor_ope(Key x, bool isMax) {
        assert(size());
        int v = root, bit = KeyLog - 1;
        Key k = 0;
        while (bit >= 0) {
            int target = ((x >> bit) & 1) ^ isMax;
            if (count(nodes[v].ch[target]) == 0) target ^= 1;
            v = nodes[v].ch[target];
            k += (x ^ nodes[v].k) & mask(nodes[v].l, nodes[v].r);
            bit = nodes[v].l - 1;
        }
        return k;
    }
};

binary_trie bt;

int main() {
	bt.insert(0);
	bt.insert(1);
	bt.insert(2);
	bt.insert(3);
	bt.insert(4);
	bt.insert(5);
	bt.insert(10);
	bt.insert(11);
	bt.insert(12);
	bt.insert(13);

	out(bt.xor_range_satisfiable(7,1000,10000));
}