#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int maxn = 1e5+5;
const int T = 50;

int N,D,H[maxn];
vector<pair<int,int>> P[maxn];
vector<vector<int>> S[maxn];

void init(int _N, int _D, int _H[]) {
    N=_N,D=_D;
    for(int i=0;i<N;i++) H[i]=_H[i];
}

void curseChanges(int U, int A[], int B[]) {
    for(int i=0;i<U;i++){
        P[A[i]].push_back({B[i],i});
        P[B[i]].push_back({A[i],i});
    }

    for(int i=0;i<N;i++){
        set<int> ss;
        for(int j=0;j<(int)P[i].size();j++){
            int v=P[i][j].first;
            if(ss.count(v)) ss.erase(v);
            else ss.insert(v);
            if(j%T==0){
                vector<int> cc;
                for(int x:ss) cc.push_back(x);
                S[i].push_back(cc);
            }
        }        
    }
}

vector<int> get(int u,int t){
    int l=-1,r=(int)P[u].size()-1;
    while(l<r){
        int m=(l+r+1)>>1;
        if(P[u][m].second<t) l=m;
        else r=m-1;
    }
    if(l==-1) return {};
    int id=l/T;
    set<int> ss;
    for(int i=id*T+1;i<=l;i++){
        int v=P[u][i].first;
        if(ss.count(v)) ss.erase(v);
        else ss.insert(v);
    }
    vector<int> res;
    for(int v:S[u][id]){
        if(ss.count(v)) ss.erase(v);
        else res.push_back(H[v]);
    }
    for(int v:ss) res.push_back(H[v]);
    sort(res.begin(),res.end());
    return res;
}

int question(int x, int y, int v){
    vector<int> X=get(x,v);
    vector<int> Y=get(y,v);
    int res=inf;x=0,y=0;
    while(x<(int)X.size() && y<(int)Y.size()){
        res=min(res,abs(X[x]-Y[y]));
        if(X[x]<Y[y]) x++;
        else y++;
    }
    return res;
}
