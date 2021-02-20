 
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
#define MOD (1e9+7)
void get(){}template<class H,class...T>void get(H&h,T&...t){cin>>h;get(t...);}
#define dcl(...) int __VA_ARGS__;get(__VA_ARGS__);


int main(){
    dcl(h,w,d,k);
    vector<int> pos(d);
    vector<bool> exist(h*w);
    rep(i,d){
        dcl(y,x);
        pos[i]=y*w+x;
        exist[pos[i]]=true;
    }
    vi cost(d,0);
    vi vec={-1,1,-w,w};
    
    auto c=[](pii a, pii b){return a.sc<b.sc;};
    priority_queue<pii,vector<pii>,decltype(c)> pq(c);
    
    range(i,1,d-1){
        cost[i]+=abs(pos[i]/w-pos[i-1]/w)+abs(pos[i]%w-pos[i-1]%w);
        cost[i]+=abs(pos[i]/w-pos[i+1]/w)+abs(pos[i]%w-pos[i+1]%w);
        pq.emplace(i,cost[i]);
    }
    pq.emplace(0,abs(pos[0]/w-pos[1]/w)+abs(pos[0]%w-pos[1]%w));
    pq.emplace(d-1,abs(pos[d-1]/w-pos[d-2]/w)+abs(pos[d-1]%w-pos[d-2]%w));
    rep(i,k){
        auto p=pq.top(); pq.pop();
        //cout<<p.fs<<","<<p.sc<<endl;
        int index=p.fs;
        int newpos;
        if(index==0 || index==d-1){
            newpos=pos[index==0?1:d-2];
        } else newpos=(pos[index-1]/w+pos[index+1]/w)/2*w+(pos[index-1]%w+pos[index+1]%w)/2;
        //cout<<pos[index]<<","<<newpos<<endl;;
        queue<int> q;
        q.push(newpos);
        while(exist[q.front()]){
            int id=q.front();q.pop();
            for(auto v: {-1,1,-w,w}){
                if(0<=id+v && id+v<h*w)q.push(id+v);
            }
        }
        newpos=q.front();
        //cout<<pos[index]<<","<<newpos<<endl;;
        cout<<pos[index]/w<<" "<<pos[index]%w<<" "<<newpos/w<<" "<<newpos%w<<endl;
        exist[pos[index]]=false;
        exist[newpos]=true;
        pos[index]=newpos;
    }
    
}
