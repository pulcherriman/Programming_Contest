 
#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;
using msi=map<string,int>;
using mii=map<int,int>;
using pii=pair<int,int>;
using vlai=valarray<int>;
using ll=long long;
#define rep(i,n) for(int i=0;i<n;i++)
#define range(i,s,n) for(int i=s;i<n;i++)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define INF 1e9
#define EPS 1e-9

int main(){
    int n;cin>>n;
    queue<int> q;
    rep(i,(1<<n)){
        int p;
        cin>>p;
        q.push(p);
    }
    while(q.size()!=1){
        int a=q.front(); q.pop();
        int b=q.front(); q.pop();
        if(a==b)q.push(a);
        else q.push(abs(a-b));
    }
    cout<<q.front()<<endl;
    return 0;
}
