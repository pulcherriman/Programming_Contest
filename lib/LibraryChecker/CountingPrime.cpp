#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;

using namespace std;
using ll=long long;
using ull=unsigned long long;
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
#define rrep(i,n) rrange(i,0,n)
#define range(i,a,n) for(ll i=((ll)a);i<((ll)n);i++)
#define rrange(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);i--)
#define LINF ((ll)1ll<<60)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define PI (3.1415926535897932384)

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

//output
template<class T>struct hasItr{
    template<class U>static constexpr true_type check(class U::iterator*);
    template<class U>static constexpr false_type check(...);
    static constexpr bool v=decltype(check<T>(nullptr))::value;
};
template<>struct hasItr<string>{static constexpr bool v=false;};

template<class T>void puta(T&t,false_type,ostream&os,char el){os<<t;}
template<class T>void puta(T&t,true_type,ostream&os,char el){
    constexpr bool h=hasItr<typename T::value_type>::v;
    bool F=true,I;
    for(auto&i:t){
        if(!F)os<<' ';
        puta(i,bool_constant<h>(),os,el);
        F=I=h;
    }
    if(!I)os<<el;
}
template<class T>void puta(const T&t, ostream&os=cout, char el='\n'){
    puta(t,bool_constant<hasItr<T>::v>(),os,el);
    if(!hasItr<T>::v)os<<el;
}
template<class H,class...T>void puta(const H&h,const T&...t){cout<<h<<' ';puta(t...);}
template<size_t i,class...T>void puta(tuple<T...>const&t, ostream&os){
    if constexpr(i==sizeof...(T)-1)puta(get<i>(t),os);
    else{os<<get<i>(t)<<' ';puta<i+1>(t,os);}
}
template<class...T>void puta(tuple<T...>const&t, ostream&os=cout){puta<0>(t,os);}
template<class T>void dump(const T&t){puta(t,cerr);}
template<class H,class...T>void dump(const H&h,const T&...t){cerr<<h<<' ';dump(t...);}
template<class...T>void dump(tuple<T...>const&t){puta(t,cerr);}
template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){
    os<<'['<<p.first<<", ";
    if constexpr(hasItr<T>::v)puta(p.second,bool_constant<true>(),os,']');
    else os<<p.second<<']';
    return os;
};
template<class...T>constexpr ostream&operator<<(ostream&os,tuple<T...>t){
    puta(t,os); return os;
}

void YN(bool b){puta(b?"YES":"NO");}
void Yn(bool b){puta(b?"Yes":"No");}

#ifndef _DEBUG
#define dump(...) 
#endif

//input
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
// #define geta(t,n,...) t n;cin>>n;geta(t,__VA_ARGS__)
// #define vec(t,a,h,...) vector<t>a(h);rep(i,n)a[i]=t(__VA_ARGS__);rep(i,n)cin>>a[i]
template<typename...S>void geta_(S&...s){((cin>>s),...);}

#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)

constexpr int R=1010101,C=10101;
bitset<R>isp;
vi ps;

void init(int c){
	ps.clear(); isp[0]=isp[1]=1;
	for(int p=2;p*p<=R;p++)if(!isp[p])for(int q=p*p;q<=R;q+=p)isp[q]=1;
	range(i,2,R+1)if(!isp[i])ps.push_back(i);
}

ll phi(ll x,ll a,ll cnt){
	ll res=0;
	vi mu(a+1,1),minp(a+1,a);
	range(i,1,a+1){
		if(!isp[i]){
			for(ll j=i;j<=a;j+=i){mu[j]*=-1;chmin(minp[j],(int)i);}
			for(ll j=i*i,k=j;k<=a;k+=j)mu[k]=0;
		}
		res+=x/i*mu[i];
	}
	vl sum(cnt,0);
	bitset<C>is_one;
	for(ll lo=1;lo<x/a;lo+=a){
		is_one.reset();
		ll hi=min(lo+a,x/a);
		atcoder::fenwick_tree<ll>bit(a);
		rep(b,cnt){
			int p=ps[b],mi=max(x/p/hi,a/p),ma=min(x/p/lo,a);
			if(p<ma)range(m,mi+1,ma+1)if(mu[m]&&minp[m]>p)res-=mu[m]*(sum[b]+x/p/m-lo+1-bit.sum(0,x/p/m-lo+1));
			sum[b]+=a-bit.sum(0,a);
			for(int q=(p-lo%p)%p;q<a;q+=p)if(!is_one[q])bit.add(q,is_one[q]=1);
		}
	}
	return res;
}

ll pi(ll x){
	int r=sqrt(x),c=cbrt(x); 
	if(x<=R)return upper_bound(all(ps),x)-ps.begin();
	ll a=upper_bound(all(ps),c)-ps.begin(),b=upper_bound(all(ps),r)-ps.begin();
	ll res=phi(x,c,a)+(b+a-2)*(b-a+1)/2,idx=b-1;
	vl cur(c+1);bitset<C>val;
	for(int s=r;s<=x&&idx>=a;s+=c){
		memset(cur.data(),0,c+1);val.reset();cur[0]=b;
		for(int&p:ps)if(p<=ps[a-1])for(int q=(p-s%p)%p;q<=c;q+=p)val[q]=1;else break;
		range(i,1,c+1)cur[i]=cur[i-1]+1-val[i];
        b=cur[c];
		while(s<=x/ps[idx]&&x/ps[idx]<s+c&&idx>=a)res-=cur[x/ps[idx--]-s];
	}
	return res;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    geta(ll, n);
	init(cbrt(n));
	puta(pi(n));
    return 0;
}