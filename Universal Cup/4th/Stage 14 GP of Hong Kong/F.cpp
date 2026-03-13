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

namespace First{
    void solve(){
        int n,m;cin >> n >> m;
        
        vector<pii> E(m);
        vector<vector<int>> g(n+1);
        for(int i=0;i<m;i++){
            int u,v;cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
            E[i]={u,v};
        }

        int T=0;
        queue<int> q;
        vector<int> f(n+1),d(n+1,-1);

        int k;cin >> k;
        vector<int> P(k);
        for(int i=0;i<k;i++){
            cin >> P[i];
            f[P[i]]=++T;
            d[P[i]]=0;
            q.push(P[i]);
        }
        for(int i=1;i<=n;i++) if(!f[i]) f[i]=++T;

        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v:g[u]) if(d[v]==-1){
                d[v]=d[u]+1;
                q.push(v);
            }
        }

        vector<int> ord(n);
        iota(ord.begin(),ord.end(),1);
        sort(ord.begin(),ord.end(),[&](int x,int y){
            if(d[x]!=d[y]) return d[x]<d[y];
            else return f[x]<f[y];
        });
        for(int i=0;i<n;i++) f[ord[i]]=i+1;
        for(auto [u,v]:E){
            if(f[u]>f[v]) swap(u,v);
            if(f[u]==1 && f[v]==k) swap(u,v);
            cout << u << ' ' << v << '\n';
        }
    }
}


namespace Second{
    void solve(){
        int n,m;cin >> n >> m;

        vector<int> deg(n+1);
        vector<vector<int>> g(n+1),rev(n+1);
        for(int i=1;i<=m;i++){
            int u,v;cin >> u >> v;
            g[u].push_back(v);
            rev[v].push_back(u);
            deg[u]++;
        }

        queue<int> q;
        for(int i=1;i<=n;i++) if(!deg[i]) q.push(i);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v:rev[u]){
                deg[v]--;
                if(!deg[v]) q.push(v);
            }
        }

        vector<int> S;
        for(int i=1;i<=n;i++) if(deg[i]) S.push_back(i);
        
        for(int x:S) rev[x].clear();
        for(int x:S){
            vector<int> T;
            for(int y:g[x]) if(deg[y]) T.push_back(y),rev[y].push_back(x);
            g[x]=T;deg[x]=(int)g[x].size();
        }

        vector<bool> del(n+1);
        vector<int> nxt(n+1);
        for(int x:S) if(deg[x]==1) q.push(x);
        while(!q.empty()){
            int x=q.front();q.pop();
            int y=-1;
            for(int v:g[x]) if(!del[v]) y=v;
            assert(y!=-1);
            del[y]=true;
            nxt[x]=y;
            for(int v:rev[y]){
                if(!nxt[v]){
                    deg[v]--;
                    if(deg[v]==1) q.push(v);
                }
            }
        }


        int T=S[0];
        vector<int> res;
        do{
            res.push_back(T);
            T=nxt[T];
        }while(T!=S[0]);

        for(int x:res) cout << x << ' ';
        cout << '\n';
    }
}

void solve(){
    int op;cin >> op;
    if(op==1) First::solve();
    else Second::solve();
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}