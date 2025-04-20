#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int maxn = 205;
int par[maxn],cnt;

int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}

bool unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return false;
    return cnt--,par[v]=u,true;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);

    vector<piii> e;
    int n,m;cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        e.push_back({w,{u,v}});
        sort(e.begin(),e.end());
        vector<piii> ne;cnt=n;
        for(int j=1;j<=n;j++) par[j]=j;
        int total=0;
        for(auto x:e) if(unions(x.se.fi,x.se.se)){
            total+=x.fi;
            ne.push_back(x);
        }
        cout << (cnt==1?total:-1) << endl;
        e=ne;
    }
}
