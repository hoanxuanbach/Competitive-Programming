#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int inf = 9e18;

void solve(){
    int n,m;cin >> n >> m;
    vector<vector<int>> g(n+1);
    vector<bool> key(n+1);
    for(int i=1;i<=n;i++){
        int p;cin >> p;
        g[p].push_back(i);
    }

    vector<char> C(n+1);
    for(int i=1;i<=m;i++){
        int k;cin >> k;
        key[k]=true;
    }

    vector<int> d(n+1);
    vector<deque<pair<int,int>>> P(n+1);
    function<void(int)> dfs = [&](int u){
        for(int v:g[u]) d[v]=d[u]+1,dfs(v);
        stable_sort(g[u].begin(),g[u].end(),[&](int x,int y){
            for(int i=0;i<min((int)P[x].size(),(int)P[y].size());i++){
                if(P[x][i].first!=P[y][i].first) return P[x][i].first<P[y][i].first;
                if(P[x][i].second!=P[y][i].second) return P[x][i].second>P[y][i].second;
            }
            return false;
        });
        if(key[u]) P[u].push_back({d[u],-1});

        char cur='a';
        for(int v:g[u]){
            C[v]=cur,cur++;
            if(!P[u].empty()) P[u][(int)P[u].size()-1].second=d[u];
            if((int)P[u].size()<(int)P[v].size()){
                swap(P[u],P[v]);
                while(!P[v].empty()){
                    P[u].push_front(P[v].back());
                    P[v].pop_back();
                }
            }
            else{
                for(auto x:P[v]) P[u].push_back(x);
            }
        }
    };
    dfs(0);

    for(int i=1;i<=n;i++) cout << C[i];
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}