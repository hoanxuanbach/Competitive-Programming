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

    int n,m,K;cin >> n >> m >> K;

    vector<int> w(m+1),X(m+1);
    vector<vector<pii>> g(n);
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v >> w[i];u--;v--;
        g[u].push_back({v,i});
        g[v].push_back({u,i});
        X[i]=u^v;
    }

    int ans=0;
    vector<int> res;
    vector<bool> del(m+1);

    /*test 1,2,3
    vector<int> cur;
    vector<int> d(n,inf);
    vector<vector<int>> f(n);
    vector<vector<int>> e;

    auto build = [&](){
        for(int i=0;i<n;i++) d[i]=inf;
        priority_queue<pii,vector<pii>,greater<pii>> pq;
        pq.push({d[0]=0,0});
        while(!pq.empty()){
            auto [dd,u]=pq.top();pq.pop();
            if(d[u]!=dd) continue;
            for(auto [v,id]:g[u]){
                if(!del[id]){
                    if(d[v]>d[u]+w[id]) pq.push({d[v]=d[u]+w[id],v}),f[v].clear();
                    if(d[v]==d[u]+w[id]) f[v].push_back(id);
                }
            }
        }
        if(d[n-1]==inf) return;
        int u=n-1;
        e.clear();
        while(u){
            e.push_back(f[u]);
            u^=X[f[u].back()];
        }
        return;
    };
    function<void(int)> dfs = [&](int k){
        build();
        if(d[n-1]==inf) return;
        if(d[n-1]>ans){
            ans=d[n-1];res=cur;
            cout << ans << '\n';
            for(int x:res) cout << x << ' ';
            cout << endl;
        }
        if(K==k) return;
        vector<vector<int>> E=e;
        for(auto v:E){
            if(k+(int)v.size()>K) continue;
            for(int x:v) del[x]=true,cur.push_back(x);
            dfs(k+1);
            for(int x:v) cur.pop_back(),del[x]=false;
        }
    };
    dfs(0);
    */

    /*Test 4,5
    vector<vector<pii>> W(n,vector<pii>(n,{-inf,-1}));
    vector<vector<int>> dp,trace;
    auto cal = [&](int N){
        dp.assign(N,vector<int>(1<<N,-inf));
        trace.assign(N,vector<int>(1<<N,-1));
        dp[0][1]=0;

        for(int mask=1;mask<(1<<N);mask++){
            for(int u=0;u<N;u++){
                if(dp[u][mask]==-inf) continue;
                for(int v=0;v<N;v++){
                    if((mask>>v&1) || W[u][v].second==-1) continue;
                    int id=W[u][v].second;
                    if(dp[u][mask]+w[id]>dp[v][mask^(1<<v)]){
                        dp[v][mask^(1<<v)]=dp[u][mask]+w[id];
                        trace[v][mask^(1<<v)]=id;
                    }
                }
            }
        }

        int mask=0;
        for(int i=1;i<(1<<N);i++) if(dp[N-1][i]>dp[N-1][mask]) mask=i;
        cerr << dp[N-1][mask] << endl;

        int u=N-1;
        while(u){
            int id=trace[u][mask];del[id]=true;
            mask^=(1<<u);u^=X[id];
        }
    };
    
    int S=0;
    for(int T=20;T<=n;T+=20){
        int N=T-S;
        W.assign(N,vector<pii>(N,{-inf,-1}));
        for(int u=S;u<T;u++) for(auto [v,id]:g[u]) if(v>=S && v<T){
            X[id]=(u-S)^(v-S);
            W[u-S][v-S]=W[v-S][u-S]=max(W[u-S][v-S],{w[id],id});
        }
        cal(N);
        S=T-1;
    }
    */

    /*Test 6,7
    int S=0,D=10,Z=n/D;
    
    vector<vector<int>> val(Z),F(Z);
    vector<vector<array<int,3>>> E(Z);

    vector<vector<int>> sum(Z+1,vector<int>(K+1,-inf)),trace(Z+1,vector<int>(K+1,-1));
    sum[0][0]=0;

    for(int i=0;i<Z;i++){
        cerr << i << endl;
        int T=(i+1)*D,N=T-S;
        vector<array<int,3>> e;
        for(int u=S;u<T;u++) for(auto [v,id]:g[u]) if(v>u && v<T) e.push_back({u-S,v-S,id});
        E[i]=e;

        vector<vector<pii>> G(N);
        vector<int> d(N,inf);
        auto cal = [&](){
            d.assign(N,inf);
            priority_queue<pii,vector<pii>,greater<pii>> pq;
            pq.push({d[0]=0,0});
            while(!pq.empty()){
                auto [dd,u]=pq.top();pq.pop();
                if(dd!=d[u]) continue;
                for(auto [v,id]:G[u]) if(d[v]>d[u]+w[id]) pq.push({d[v]=d[u]+w[id],v});
            }
            return d[N-1];
        };

        int sz=(int)e.size();
        val[i].assign(sz+1,-1);
        F[i].assign(sz+1,-1);
        for(int mask=0;mask<(1<<sz);mask++){
            int cnt=__builtin_popcount(mask);
            for(int j=0;j<N;j++) G[j].clear();
            for(int j=0;j<sz;j++) if(!(mask>>j&1)){
                auto [u,v,id]=e[j];
                G[u].push_back({v,id});
                G[v].push_back({u,id});
            }
            int dist=cal();
            if(dist==inf) continue;
            if(dist>val[i][cnt]) val[i][cnt]=dist,F[i][cnt]=mask;
        }

        for(int j=0;j<=K;j++){
            if(sum[i][j]==-inf) continue;
            for(int k=0;k<=min(K-j,sz);k++){
                if(val[i][k]==-1) continue;
                if(sum[i][j]+val[i][k]>sum[i+1][j+k]){
                    sum[i+1][j+k]=sum[i][j]+val[i][k];
                    trace[i+1][j+k]=k;
                }
            }
        }
        S=T-1;
    }

    int i=Z,x=0;
    for(int j=0;j<=K;j++) if(sum[i][j]>sum[i][x]) x=j;
    del.assign(m+1,1);
    while(i){
        int k=trace[i][x];i--;x-=k;
        for(int j=0;j<(int)E[i].size();j++) if(F[i][k]>>j&1) del[E[i][j][2]]=0;
    }
    */
    
    /*Test 8
    map<pii,int> mp;
    for(int i=0;i<n;i++) for(auto [v,id]:g[i]) mp[{i+1,v+1}]=id;
    del.assign(m+1,false);

    int S=100;
    for(int i=1;i<=S-2;i++){
        for(int j=1;j<S;j++) del[mp[{(i-1)*S+j,(i-1)*S+j+1}]]=true;
        if(i&1) del[mp[{(i-1)*S+S,i*S+S}]]=true;
        else del[mp[{(i-1)*S+1,i*S+1}]]=true;
    }
    for(int i=1;i<S;i++){
        del[mp[{(S-2)*S+i,(S-1)*S+i}]]=true;
        if(i&1) del[mp[{(S-1)*S+i,(S-1)*S+i+1}]]=true;
        else del[mp[{(S-2)*S+i,(S-2)*S+i+1}]]=true;
    }
    */

    /*Test 9
    int N=n/2;
    vector<array<int,3>> f(N+1,{0,0,0});
    for(int u=0;u<n;u++){
        for(auto [v,id]:g[u]){
            if(u>v) continue;
            int U=u+1,V=v+1;
            if(V<=N && V==U+1) f[U][0]=id;
            else if(U>N && V==U+1) f[U-N][1]=id;
            else if(V==U+N) f[U][2]=id;
            else assert(false);
        }
    }
    w[0]=-inf;
    vector<array<pii,2>> dp(N+1,{pii{-inf,-1},pii{-inf,-1}});
    dp[1][0]={0,-1};
    for(int i=1;i<N;i++){
        dp[i+1][0]=max(dp[i+1][0],{dp[i][0].first+w[f[i][0]],0});
        dp[i+1][1]=max(dp[i+1][1],{dp[i][0].first+w[f[i][1]]+w[f[i][2]],1});

        dp[i+1][1]=max(dp[i+1][1],{dp[i][1].first+w[f[i][1]],0});
        dp[i+1][0]=max(dp[i+1][0],{dp[i][1].first+w[f[i][0]]+w[f[i][2]],1});
    }
    int i=N,x=1;
    if(dp[N][0].first+w[f[N][2]]>dp[N][1].first) x=0,del[f[N][2]]=true;
    while(i>1){
        int k=dp[i][x].second;i--;
        del[f[i][x]]=true;
        if(k) del[f[i][2]]=true;
        x^=k;
    }
    */
    
    /*Test 10
    del.assign(m+1,true);
    vector<int> deg(n),E;
    for(int i=0;i<n;i++) deg[i]=(int)g[i].size();
    for(int i=0;i<n;i++) for(auto [v,id]:g[i]) if(deg[i]>2 && deg[v]>2 && i<v) E.push_back(id),del[id]=false;
    
    vector<int> d(n,0);
    auto cal = [&](){
        d.assign(n,0);d[0]=1;
        queue<int> q;q.push(0);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(auto [v,id]:g[u]) if(del[id] && !d[v]){
                d[v]=d[u]+1;
                q.push(v);
            }
        }
        return d.back()==n;
    };
    for(int i:E){
        //cerr << i << endl;
        del[i]=true;
        if(cal()) break;
        del[i]=false;
    }
    */
    
    for(int i=1;i<=m;i++) if(!del[i]) res.push_back(i);
    cout << (int)res.size() << '\n';
    for(int x:res) cout << x << '\n';
}
 
signed main(){
    freopen("shortest9.in","r",stdin);
    freopen("shortest9.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
