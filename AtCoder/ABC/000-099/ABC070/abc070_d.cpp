#include <iostream>
#include <vector>
#include <map>
using namespace std;
 
void search(int node, vector<vector<pair<int,long>>> &path,vector<long> &route, vector<int> &s, vector<int> v){
    static int isSearch=1;
    vector<int> next;
    for(auto n : v){
        for(auto p : path[n]){
            if(s[p.first]==0){
                s[p.first]=1;
                isSearch++;
                next.push_back(p.first);
                route[p.first]=route[n]+p.second;
            }
        }
    }
    if(isSearch!=node){
        search(node,path,route,s,next);
    }
}
 
int main(void){
    int n,q,k;
    cin>>n;
    vector<vector<pair<int,long>>> path(n+1);
    vector<long> route(n+1,0);
    for(int i=0;i<n-1;i++){
        int a,b;
        long c;
        cin>>a>>b>>c;
        path[a].push_back(pair<int,long>(b,c));
        path[b].push_back(pair<int,long>(a,c));
    }
    //for(auto a:path){for(auto p:a)cout<<p.first<<",";cout<<endl;}
    cin>>q>>k;
    vector<int> s(n+1,0);
    s[k]=1;
    search(n,path,route,s,vector<int>(1,k));
    for(int i=0;i<q;i++){
        int a,b;
        cin>>a>>b;
        cout<<route[a]+route[b]<<endl;
    }
}