#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+9;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 4e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int N,D;
int T[maxn],res[maxn];
vector<int> g[maxn];

int sz[maxn],SZ;
bool used[maxn];

void dfs_sz(int u,int p){
    sz[u]=1;
    for(int v:g[u]){
        if(v==p || used[v]) continue;
        dfs_sz(v,u);
        sz[u]+=sz[v];
    }
}
int get_centroid(int u,int p){
    for(int v:g[u]){
        if(v==p || used[v]) continue;
        if(sz[v]>SZ/2) return get_centroid(v,u);
    }
    return u;
}


int cnt[maxn],add[maxn];
int dd[maxn],A[maxn],B[maxn];
vector<int> all,S[maxn];

void dfs(int u,int p,int t){
    all.push_back(u); 
    if(t) S[t].push_back(u);
    for(int v:g[u]){
        if(v==p || used[v]) continue;
        dd[v]=dd[u]+1;
        B[v]=max(0LL,min(T[v]-dd[v],B[u]));
        A[v]=max(0LL,min(T[v],A[u]-1));
        dfs(v,u,(t==0?v:t));
    }
}

void update(vector<int> ss,int sgn){
    int M=0;
    for(int v:ss) M=max(M,dd[v]);
    for(int v:ss){
        cnt[dd[v]]++;
        if(dd[v]>D) continue;
        if(B[v]<=min(M,D-dd[v])){
            add[B[v]]++;
            add[min(M,D-dd[v])+1]--;
        }
    }
    for(int i=1;i<=M+1;i++) cnt[i]+=cnt[i-1],add[i]+=add[i-1];
    for(int v:ss){
        if(dd[v]>D) continue;
        int val=0;
        if(!A[v]) val=sgn*cnt[min(M,D-dd[v])];
        else val=sgn*add[dd[v]];
        res[v]+=val;
    }
    for(int i=0;i<=M+1;i++) add[i]=cnt[i]=0;
}

void decompose(int u){
    dfs_sz(u,0);SZ=sz[u];
    int x=get_centroid(u,0);

    all.clear();
    for(int v:g[x]) S[v].clear();

    dd[x]=0;
    B[x]=T[x];
    A[x]=T[x];
    dfs(x,0,0);

    update(all,1);
    for(int v:g[x]) if(!used[v]) update(S[v],-1);


    used[x]=true;
    for(int v:g[x]) if(!used[v]) decompose(v);
}

void solve(){
    cin >> N >> D;
    for(int i=1;i<=N;i++) cin >> T[i];
    for(int i=1;i<N;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    decompose(1);
    for(int i=1;i<=N;i++) cout << res[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
