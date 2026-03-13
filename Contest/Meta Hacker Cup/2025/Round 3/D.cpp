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
 
const int maxn = 1e5+5;
const int maxl = 20;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int n,d[maxn];
vector<int> g[maxn],adj[maxn];
int L[maxn],R[maxn],cn[2*maxn],T;
int mn[2*maxn][maxl],lg2[2*maxn];

void dfs(int u,int p){
    L[u]=++T;
    mn[T][0]=T;cn[T]=u;
    for(int v:g[u]){
        if(v==p) continue;
        d[v]=d[u]+1;
        dfs(v,u);
        mn[++T][0]=L[u];
    }
    R[u]=T;
}
int lca(int u,int v){
    u=L[u];v=L[v];
    if(u>v) swap(u,v);
    int p=lg2[v-u+1],a=min(mn[u][p],mn[v-(1<<p)+1][p]);
    return cn[a];
}
int getdist(int u,int v){
    return d[u]+d[v]-2*d[lca(u,v)];
}
void build(){
    dfs(1,0);
    for(int i=2;i<=T;i++) lg2[i]=lg2[i/2]+1;
    for(int i=1;i<18;i++){
        for(int j=1;j<=(T-(1<<i)+1);j++) mn[j][i]=min(mn[j][i-1],mn[j+(1<<(i-1))][i-1]);
    }
}

int cnt[maxn],total,sz;
void dfs2(int x){
    for(int v:adj[x]){
        dfs2(v);
        cnt[x]+=cnt[v];
        total+=(d[v]-d[x])*cnt[v]*(sz-cnt[v]);
    }
}

int virtual_tree(int d){
    vector<int> S;
    for(int i=d;i<=n;i+=d) S.push_back(i);
    sort(S.begin(),S.end(),[&](int x,int y){
        return L[x]<L[y];
    });
    sz=(int)S.size();
    for(int i=0;i+1<sz;i++) S.push_back(lca(S[i],S[i+1]));
    sort(S.begin(),S.end(),[&](int x,int y){
        return L[x]<L[y];
    });
    S.erase(unique(S.begin(),S.end()),S.end());
    int root=-1;
    vector<int> v;
    for(int x:S){
        while(!v.empty() && R[v.back()]<L[x]) v.pop_back();
        if(!v.empty()) adj[v.back()].push_back(x);
        else root=x;
        v.push_back(x);
    }
    for(int x:S) cnt[x]=(x%d==0);
    total=0;
    dfs2(root);
    for(int x:S) adj[x].clear();
    return total;
}

void solve(){
    cin >> n;

    T=0;
    for(int i=1;i<=n;i++){
        g[i].clear();
        adj[i].clear();
    }
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    build();

    vector<int> res(n+1);
    for(int i=1;i<=n;i++) res[i]=virtual_tree(i);
    for(int i=n;i>=1;i--) for(int x=i*2;x<=n;x+=i) res[i]-=res[x];
    for(int i=1;i<=n;i++) cout << res[i] << ' ';
    cout << '\n';
}
 
signed main(){
    freopen("A.txt","r",stdin);
    freopen("out.txt","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    for(int t=1;t<=test;t++){
        cout << "Case #" << t << ": ";
        solve();
    }
}
