#include<bits/stdc++.h>
using namespace std;
const int maxn = 105;

int N,d[maxn],par[maxn];
vector<int> edge[maxn];

void dfs(int u,int p){
    d[u]=d[p]+1;par[u]=p;
    for(int v:edge[u]) if(v!=p) dfs(v,u);
}

vector<int> a[maxn],b[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N;
    for(int i=1;i<N;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(0,N);
    int u=max_element(d,d+N)-d;
    dfs(u,N);
    int v=max_element(d,d+N)-d,k=d[v]/2;
    while(k--) v=par[v];
    dfs(v,N);

    vector<int> a;
    for(int i=1;i<10;i++) for(int j=1;j<(1<<i);j++) a.push_back(j&1);
    int S=(int)a.size();

    cout << S << '\n';
    for(int i=0;i<N;i++){
        int x=i;
        for(int j=0;j<S;j++){
            if(!(j&1) && par[x]!=N && a[j]) x=par[x];
            cout << x << ' ';
        }
        cout << '\n';
    }
    for(int i=0;i<N;i++){
        int x=i;
        for(int j=0;j<S;j++){
            if((j&1) && par[x]!=N && a[j]) x=par[x];
            cout << x << ' ';
        }
        cout << '\n';
    }
}
