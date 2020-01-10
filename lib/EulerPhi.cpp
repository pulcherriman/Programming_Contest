/* オイラーのφ関数
 * 1以上n以下の，nと互いに素な数字の個数
 * 計算量：通常 O(sqrt(n))，列挙 O(NloglogN)
 * ---------------------------
 * φ(nm) = φ(n)φ(m)
 * n,m が素ならば， n^φ(m) == 1 mod m
 * x>=log2N ならば，A^x == A^(x+φ(N))
 *   -> A の指数はφ(N)で上方向に周期性がある
 */

ll euler_phi(ll n){
    ll ret=n;
    for(ll i=2;i*i<=n;i++){
        if(n%i==0){
            ret-=ret/i;
            while(n%i==0)n/=i;
        }
    }
    if(n!=1)ret-=ret/n;
    return ret;
}

vl euler_phi_vec(ll n) {
  vl ret(++n); iota(all(ret),0);
  range(i,2,n)if(ret[i]==i)for(ll j=i;j<n;j+=i)ret[j]-=ret[j]/i;
  return ret;
}