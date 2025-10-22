#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

#define pii pair<int,int>
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
    int n,m;cin >> n >> m;
    vector<vector<int>> g(n+1);
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> d(n+1);
    
    int X=0;
    vector<int> D;
    for(int x=1;x<=n;x++){
        for(int i=1;i<=n;i++) d[i]=-1;
        queue<int> q;q.push(x);d[x]=0;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v:g[u]) if(d[v]==-1) d[v]=d[u]+1,q.push(v);
        }
        bool check=true;
        for(int i=1;i<=n;i++) if(d[i]>2) check=false;
        if(check){
            X=x;
            D=d;
            break;
        }
    }
    assert(X);

    vector<int> c(n+1,-1);
    vector<array<int,2>> cnt(n+1,array<int,2>{0,0});
    function<void(int,int)> add = [&](int x,int val){
        bool nw=(c[x]<0);
        c[x]=val;
        if(nw) for(int v:g[x]) cnt[v][val]++;
        for(int v:g[x]){
            if(cnt[v][val]>=2 && c[v]<0) add(v,val);
        } 
        if(cnt[x][val^1]){
            if(nw){
                bool used=true;
                for(int v:g[x]) if(c[v]==(val^1) && used){
                    add(v,val^1);
                    used=false;
                    break;
                }
            }
            for(int v:g[x]) if(c[v]<0) add(v,val);
        }
    };
    auto ret = [&](){
        bool check=true;
        for(int i=1;i<=n;i++) if(c[i]!=-1 && cnt[i][c[i]^1]>1) check=false;
        if(!check) return false;

        vector<int> X;
        function<void(int)> build = [&](int u){
            X.push_back(u);c[u]=-2;
            for(int v:g[u]) if(c[v]==-1) build(v);
        };

        vector<int> f(n+1,-1);
        
        int S=0;
        for(int i=1;i<=n;i++) if(c[i]==-1){
            X.clear();
            build(i);
            for(int u:X) f[u]=S;
            S++;
        }

        int T=2*S;
        vector<vector<int>> adj(2*S);
        
        for(int u=1;u<=n;u++) if(c[u]>=0){
            X.clear();
            for(int x:g[u]) if(f[x]!=-1) X.push_back(f[x]);
            if((int)X.size()<=1) continue;

            int k=c[u];
            int sz=(int)X.size()-1;
            for(int i=0;i<2*sz;i++) adj.emplace_back();
            for(int i=0;i<sz;i++){
                adj[2*X[i+1]+(k^1)].push_back(T+i);
                adj[T+i].push_back(2*X[i]+k);
                if(i) adj[T+i].push_back(T+i-1);

                adj[2*X[i]+(k^1)].push_back(T+sz+i);
                adj[T+sz+i].push_back(2*X[i+1]+k);
                if(i+1<sz) adj[T+sz+i].push_back(T+sz+i+1);
            }
            T+=2*sz;
        }

        vector<int> scc(T,-1);
        vector<bool> vis(T);
        vector<vector<int>> rev(T);
        for(int i=0;i<T;i++){
            for(int j:adj[i]) rev[j].push_back(i);
        }

        int tt=0;
        vector<int> ord;

        function<void(int)> dfs = [&](int u){
            vis[u]=true;
            for(int v:adj[u]) if(!vis[v]) dfs(v);
            ord.push_back(u);
        };
        function<void(int)> dfs2 = [&](int u){
            scc[u]=tt;
            for(int v:rev[u]) if(scc[v]==-1) dfs2(v);
        };

        for(int i=0;i<T;i++) if(!vis[i]) dfs(i);
        reverse(ord.begin(),ord.end());
        for(int u:ord) if(scc[u]==-1) dfs2(u),tt++;

        vector<int> cc(S);
        for(int i=0;i<S;i++){
            if(scc[2*i]==scc[2*i+1]) check=false;
            cc[i]=(scc[2*i]<scc[2*i+1]);
        }

        if(!check) return false;
        for(int i=1;i<=n;i++) if(c[i]<0){
            c[i]=cc[f[i]];
            for(int v:g[i]) cnt[v][c[i]]++;
        }

        for(int i=1;i<=n;i++) if(cnt[i][c[i]^1]>1) check=false;
        if(!check) return false;

        for(int i=1;i<=n;i++) cout << c[i];
        cout << '\n';
        return true;
    };
    for(int i=1;i<=n;i++) if(D[i]==1){
        c.assign(n+1,-1);
        cnt.assign(n+1,array<int,2>{0,0});
        add(X,0);
        if(c[i]==-1) add(i,1);
        else if(c[i]!=1) continue;
        if(ret()) return;
    }

    for(int i=1;i<=n;i++) if(D[i]==2){
        c.assign(n+1,-1);
        cnt.assign(n+1,array<int,2>{0,0});
        add(X,0);
        bool check=true;
        for(int j=1;j<=n;j++){
            if(D[j]==1){
                if(c[j]==-1) add(j,0);
                else if(c[j]!=0) check=false;
            }
        }
        if(c[i]==-1) add(i,1);
        else if(c[i]!=1) check=false;
        if(!check) continue;
        if(ret()) return;
    }

    cout << -1 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
