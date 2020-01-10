/* 分割数
 * 自然数n<=5100を，k個以下の正整数の和で表す組み合わせ数
 * 計算量：前計算 O(n^2) 取得 O(1)
 * ---------------------------
 * P(n,n)しか使わないなら，O(n sqrt(n))で可能
 */

// require: modint
template<class T> struct Partition {
    vector<vector<T>> P;
    constexpr Partition(int MAX) noexcept : P(MAX, vector<T>(MAX, 0)) {
        rep(k,MAX) P[0][k]=1;
        range(n,1,MAX) range(k,1,MAX) P[n][k]=P[n][k-1]+(n-k>=0?P[n-k][k]:0);
    }
    constexpr T get(int n, int k) {
        if(n< 0 or k<0)return 0;
        return P[n][k];
    }
    constexpr T get(int n){
        return get(n,n);
    }
};
Partition<mint> part(5100);