#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
#define range(i,a,n) for(int i=a;i<n;i++)
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end()
#define INF (int)(1e9)

int h,w,k;

int clear(vvi&f, int combo){
    int del=0;
    range(i,1,h+1)range(j,1,w+2-k){
        if(f[i][j]==-1) continue;
        if(f[i][j]==f[i][j+1] and f[i][j]==f[i][j+2])  del+=f[i][j]*3,f[i][j]=f[i][j+1]=f[i][j+2]=0,j+=2;
        if(f[i][j]==f[i][j+1] and k==2) del+=f[i][j]*2, f[i][j]=f[i][j+1]=0, j++;
    }
    return del<<combo;
}
void fall(vvi&f){
    vvi nf(h+2,vi(w+2,-1));
    range(j,1,w+1){
        int p=h;
        for(int i=h;i>=1;i--){
            if(f[i][j]>0) nf[p--][j]=f[i][j];
        }
    }
    f=nf;
}

int solve(vvi f, int i, int j){
    f[i][j]=0;
    fall(f);
    int score=0,add=0,ren=0;
    while((add=clear(f,ren++))!=0){
        score+=add;
        fall(f);
    }
    return score;
}

int main(){
    cin>>h>>w>>k;
    if(k>=4){
        cout<<0<<endl;
        return 0;
    }
    vvi f(h+2,vi(w+2,-1));
    range(i,1,h+1)range(j,1,w+1){char c; cin>>c; f[i][j]=c-'0';}
    int ans=0;
    range(i,1,h+1)range(j,1,w+1) ans=max(ans,solve(f,i,j));
    cout<<ans<<endl;
}