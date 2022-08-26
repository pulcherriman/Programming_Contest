/*他のライブラリを入れる場所*/
template<int _MOD>struct modint{
    ll val;
    constexpr static int setModMax = 510000;
    static modint<_MOD> fac[setModMax], finv[setModMax], inv[setModMax];

    static constexpr ll mod(ll a){return(a%_MOD+_MOD)%_MOD;}
    constexpr modint(ll v = 0)noexcept:val(v%_MOD){
        if(val<0)v+=_MOD;
    }
    constexpr int getmod(){return _MOD;}
    constexpr modint operator-()const noexcept{return val?_MOD-val:0;}
    constexpr modint operator+(const modint&r)const noexcept{return modint(*this)+=r;}
    constexpr modint operator-(const modint&r)const noexcept{return modint(*this)-=r;}
    constexpr modint operator*(const modint&r)const noexcept{return modint(*this)*=r;}
    constexpr modint operator/(const modint&r)const noexcept{return modint(*this)/=r;}
    constexpr modint operator^(const modint&r)const noexcept{return modint(*this)^=r;}
    constexpr modint&operator+=(const modint&r)noexcept{val=mod(val+r.val);return*this;}
    constexpr modint&operator-=(const modint&r)noexcept{val=mod(val-r.val);return*this;}
    constexpr modint&operator*=(const modint&r)noexcept{val=mod(val*r.val);return*this;}
    constexpr modint&operator/=(const modint&r)noexcept{
        ll a=r.val,b=_MOD,u=1,v=0;while(b){ll t=a/b;a-=t*b;swap(a,b);u-=t*v;swap(u,v);}
        val=val*u%_MOD;if(val<0)val+=_MOD;return*this;}
    constexpr modint&operator^=(const modint&r)noexcept{val=modpow(val,r.val).val;return*this;}
    constexpr bool operator<(const modint&r)const noexcept{return this->val<r.val;}
    constexpr bool operator>(const modint&r)const noexcept{return r<*this;}
    constexpr bool operator!=(const modint&r)const noexcept{return *this<r||*this>r;}
    constexpr bool operator==(const modint&r)const noexcept{return !(*this!=r);}
    constexpr bool operator<=(const modint&r)const noexcept{return !(*this>r);}
    constexpr bool operator>=(const modint&r)const noexcept{return !(*this<r);}
    friend constexpr ostream&operator<<(ostream&os,const modint<_MOD>&x)noexcept{return os<<x.val;}
    friend constexpr istream&operator>>(istream&is,modint<_MOD>&x)noexcept{return is>>x.val;}
    constexpr modint<_MOD>modpow(const modint<_MOD>&a,ll n)noexcept{
        if(n==0)return 1;auto t=modpow(a,n/2);t*=t;if(n&1)t*=a;return t;}
    friend modint<_MOD>operator+(const ll a,const modint&b){return modint(a)+=b;}
    friend void operator+=(ll&a,const modint&b){a=modint(a)+b;}
    friend modint<_MOD>operator-(const ll a,const modint&b){return modint(a)-=b;}
    friend void operator-=(ll&a,const modint&b){a=modint(a)-b;}
    friend modint<_MOD>operator*(const ll a,const modint&b){return modint(a)*=b;}
    friend void operator*=(ll&a,const modint&b){a=modint(a)*b;}
    friend modint<_MOD>operator/(const ll a,const modint&b){return modint(a)/=b;}
    friend void operator/=(ll&a,const modint&b){a=modint(a)/b;}
    friend modint<_MOD>operator^(const ll a,const modint&b){return modint(a)^=b;}
    friend void operator^=(ll&a,const modint&b){a=modint(a)^b;}
    explicit operator ll(){return val;}
};
using mint = modint<MOD>;
using vm = vector<mint>;
using vvm = vector<vm>;
mint operator""_m(unsigned long long a){return mint(a);}
mint nCr(ll n,ll r){
    const static int setModMax = 200001;
    static mint fac[setModMax],finv[setModMax],inv[setModMax];
    if(fac[0]==0){
        fac[0]=fac[1]=finv[0]=finv[1]=inv[1]=1;
        for(int i=2;i<setModMax;i++) {
            fac[i]=fac[i-1]*i;
            inv[i]=-inv[MOD%i]*(MOD/i);
            finv[i]=finv[i-1]*inv[i];
        }
    }
    return fac[n]*finv[r]*finv[n-r];
}
mint nCr(mint a,mint b){return nCr(a.val,b.val);}
