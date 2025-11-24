#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int> 
const int maxn = 2e5+5;
const int mod = 998244353;

void solve(){
    int n,m,X,Y;cin >> n >> m >> X >> Y;
    vector<vector<int>> g(n+1);
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bool adj=false;
    for(int v:g[X]) if(v==Y) adj=true;

    if(!adj){
        cout << "Yes\n";
        for(int u=1;u<=n;u++) for(int v:g[u]) if(u<v){
            if(u==X || u==Y) cout << v << ' ' << u << '\n';
            else cout << u << ' ' << v << '\n';
        }
        return;
    }
    vector<bool> vis(n+1,false);
    vector<int> S;

    bool ret=false;
    auto print = [&](vector<int> path){
        if(ret) return;
        ret=true;
        vector<int> f(n+1);
        for(int x:path) f[x]=1;
        cout << "Yes\n";
        for(int i=0;i+1<(int)path.size();i++) cout << path[i] << ' ' << path[i+1] << '\n';

        int cnt=0;
        for(int u=1;u<=n;u++) for(int v:g[u]) if(u<v){
            if(f[u] && f[v]){
                cnt++;
                continue;
            }
            if(f[u]) cout << v << ' ' << u << '\n'; 
            else cout << u << ' ' << v << '\n';
        }
        assert(cnt==(int)path.size()-1);
    };
    function<void(int)> dfs = [&](int u){
        vis[u]=true;
        vector<int> ss;
        for(int v:g[u]){
            if(v==S.back()) continue;
            if(vis[v]) ss.push_back(v);
        }
        vector<int> T=S;
        if(!ss.empty()){
            ss.push_back(S.back());
            vector<int> f(n+1);
            for(int i=0;i<(int)S.size();i++) f[S[i]]=i+1;
            sort(ss.begin(),ss.end(),[&](int x,int y){
                return f[x]<f[y];
            });
            while(!S.empty() && S.back()!=ss[1]) S.pop_back();
            S.push_back(u);
            S.push_back(ss[0]);
            print(S);
        }
        else{
            S.push_back(u);
            for(int v:g[u]) if(!vis[v]) dfs(v);
        }
        S=T;
    };

    vis[Y]=true;
    S.push_back(Y);
    dfs(X);
    if(ret) return;

    S.clear();
    swap(X,Y);
    vis.assign(n+1,false);
    vis[Y]=true;
    S.push_back(Y);
    dfs(X);
    if(ret) return;
    cout << "No\n";
}
  
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    for(int t=1;t<=test;t++){
        solve();
    }
}