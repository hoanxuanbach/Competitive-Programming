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

const int B = 450;
const int maxn = 1e5+5;
const int maxl = 25;
const int LG = 20;

const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

vector<int> g[maxn];
int L[maxn],cn[2*maxn],T,par[maxn];
pii E[2*maxn];

int Min[2*maxn][maxl],lg2[2*maxn];
void dfs(int u,int p){
    par[u]=p;
    cn[T]=u;
    E[T]={u,1};
    L[u]=T++;
    for(int v:g[u]) if(v!=p) dfs(v,u);
    E[T++]={u,-1};
}
int lca(int u,int v){
    u=L[u];v=L[v];
    if(u>v) swap(u,v);
    int k=lg2[v-u+1];
    return min(Min[u][k],Min[v-(1<<k)+1][k]);
}

int A[maxn];
int cnt[450][2*maxn],val[2*maxn];

void solve(){

    int N;cin >> N;
    for(int i=1;i<=N;i++) cin >> A[i];
    for(int i=1;i<N;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);

    for(int i=2;i<=T;i++) lg2[i]=lg2[i/2]+1;
    for(int i=0;i<T;i++) Min[i][0]=(E[i].second==1?L[E[i].first]:L[par[E[i].first]]);
    for(int j=1;j<LG;j++) for(int i=0;i<=T-(1<<j);i++) Min[i][j]=min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);

    vector<vector<array<int,3>>> f(T+1);
    auto small_add = [&](int l,int r,int x,int y,int d){
        f[x].push_back({l,r,d});
        f[y+1].push_back({l,r,-d});
    };
    auto update = [&](int l,int r,int x,int y,int d){
        for(int i=l/B+1;i<r/B;i++) cnt[i][x]+=d,cnt[i][y+1]-=d;
        if(l/B==r/B) small_add(l,r,x,y,d);
        else{
            small_add(l,(l/B)*B+B-1,x,y,d);
            small_add((r/B)*B,r,x,y,d);
        }
    };

    int M;cin >> M;
    vector<int> total(T+1),del(N+1);
    for(int i=0;i<M;i++){
        int u,v;cin >> u >> v;
        int x=lca(u,v);
        u=L[u];v=L[v];
        total[x]++;
        total[x+1]++;
        total[u+1]--;
        total[v+1]--;
        update(x,u,x+1,v,2);    
        update(x,u,x,u,1);
        update(x+1,v,x+1,v,1);
    }
    for(int i=0;i<T;i++){
        if(i) total[i]+=total[i-1];
        del[A[E[i].first]]+=total[i]*E[i].second;;
    }

    int Q;cin >> Q;
    vector<int> K(Q),res(Q);
    for(int i=0;i<Q;i++){
        cin >> K[i];
        if(K[i]%2==0) res[i]-=del[K[i]/2];
    }

    for(int i=0;i<T;i++){
        for(auto [l,r,d]:f[i]) for(int j=l;j<=r;j++) val[A[E[j].first]]+=E[j].second*d;
        for(int t=0;t<Q;t++) if(A[E[i].first]<=K[t]) res[t]+=val[K[t]-A[E[i].first]]*E[i].second;
    }

    for(int x=0;x<=(T-1)/B;x++){
        int l=x*B,r=min(T-1,x*B+B-1);
        for(int i=0;i<=T;i++) val[i]=0;
        for(int i=0;i<T;i++){
            if(i) cnt[x][i]+=cnt[x][i-1];
            val[A[E[i].first]]+=E[i].second*cnt[x][i];
        }
        for(int i=l;i<=r;i++) for(int t=0;t<Q;t++) if(A[E[i].first]<=K[t]){
            res[t]+=val[K[t]-A[E[i].first]]*E[i].second;
        }
    }

    for(int i=0;i<Q;i++) cout << res[i]/2 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
