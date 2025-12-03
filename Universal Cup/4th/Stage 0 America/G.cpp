#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int n,m,res=-inf;cin >> n >> m;
    vector<map<int,int>> g(n+1);
    auto add = [&](int u,int v,int w){
        auto it=g[u].find(v);
        if(it!=g[u].end()){
            res=max(res,w+it->second);
            w=max(w,it->second);
        }
        g[u][v]=g[v][u]=w;
    };
    for(int i=0;i<m;i++){
        int u,v,w;cin >> u >> v >> w;
        add(u,v,w);
    }
    queue<int> q;
    auto del = [&](int u,int v){
        g[u].erase(v);
        g[v].erase(u);
        if((int)g[v].size()<=2) q.push(v);
    };
    for(int i=1;i<=n;i++) if((int)g[i].size()<=2) q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        if((int)g[u].size()==1) del(u,g[u].begin()->first);
        else if((int)g[u].size()==2){
            int x=g[u].begin()->first,wx=g[u].begin()->second;
            del(u,x);
            int y=g[u].begin()->first,wy=g[u].begin()->second;
            del(u,y);
            add(x,y,wx+wy);
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
