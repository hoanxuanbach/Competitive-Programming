#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e9;

void solve(){
    int n,m;cin >> n >> m;
    vector<int> A(m),B(m);
    vector<vector<pair<int,int>>> g(n+1);
    vector<int> d(n);
    
    for(int i=0;i<m;i++){
        cin >> A[i] >> B[i];A[i]--;B[i]--;
        d[A[i]]^=1;d[B[i]]^=1;
    }

    int M=m;
    for(int i=0;i<n;i++){
        if(d[i]){
            A.push_back(i);
            B.push_back(n);
            m++;
        }
    }
    for(int i=0;i<m;i++){
        g[A[i]].push_back({B[i],i});
        g[B[i]].push_back({A[i],i});
    }

    vector<bool> del(m);
    vector<int> c(m);
    int col=1;

    vector<int> X,Y;
    vector<bool> vis(n+1);

    function<void(int)> dfs = [&](int u){
        if(vis[u]){
            int v=-1;
            do{
                v=X.back();X.pop_back();
                int id=Y.back();Y.pop_back();
                c[id]=col;vis[v]=false;
            }while(v!=u);
            col++;
        }

        while(!g[u].empty()){
            auto [v,id]=g[u].back();g[u].pop_back();
            if(del[id]) continue;
            del[id]=true;
            X.push_back(u);vis[u]=true;
            Y.push_back(id);
            dfs(v);
        }
    };

    for(int i=0;i<=n;i++){
        while(!g[i].empty()){
            dfs(i);
            Y.clear();
            X.clear();
        }
    }

    for(int i=0;i<M;i++) cout << c[i] << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}