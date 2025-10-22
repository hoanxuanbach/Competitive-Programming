#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

void solve(){
    int n;cin >> n;
    vector<vector<int>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int S=0;
    vector<int> sz(n+1);
    vector<bool> used(n+1);

    vector<vector<int>> op;
    function<void(int,int)> pre_dfs = [&](int u,int p){
        sz[u]=1;
        for(int v:g[u]){
            if(v==p || used[v]) continue;
            pre_dfs(v,u);sz[u]+=sz[v];
        }
    };
    function<int(int,int)> get_centroid = [&](int u,int p){
        for(int v:g[u]){
            if(v==p || used[v]) continue;
            if(sz[v]>S/2) return get_centroid(v,u);
        }
        return u;
    };

    function<int(int,int)> decompose = [&](int u,int d){
        pre_dfs(u,0);S=sz[u];
        int x=get_centroid(u,0);
        used[x]=true;
        if(d==(int)op.size()) op.push_back({});
        for(int v:g[x]) if(!used[v]){
            int y=decompose(v,d+1);
            op[d].push_back(y);
        }
        return x;
    };

    int x=decompose(1,0);
    while(!op.empty() && op.back().empty()) op.pop_back();
    reverse(op.begin(),op.end());
    op.push_back({x});

    cout << (int)op.size() << '\n';
    for(auto v:op){
        cout << (int)v.size() << ' ';
        for(int x:v) cout << x << ' ';
        cout << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}