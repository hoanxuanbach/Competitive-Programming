#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 5e4+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

vector<int> g[maxn];
int T,L[maxn],R[maxn],dep[maxn],cn[2*maxn];
int lg2[2*maxn],Min[2*maxn][20];

void dfs(int u,int p){
    L[u]=++T;Min[T][0]=T;
    cn[T]=u;dep[u]=dep[p]+1;
    for(int v:g[u]) if(v!=p){
        dfs(v,u);Min[++T][0]=L[u];
    }
    R[u]=T;
}

int lca(int u,int v){
    u=L[u];v=L[v];
    if(u>v) swap(u,v);
    int k=lg2[v-u+1];
    return cn[min(Min[u][k],Min[v-(1<<k)+1][k])];
}
int dist(int u,int v){
    return dep[u]+dep[v]-2*dep[lca(u,v)];    
}
void build(){
    for(int i=1;i<18;i++){
        for(int j=1;j<=T-(1<<i)+1;j++) Min[j][i]=min(Min[j][i-1],Min[j+(1<<(i-1))][i-1]); 
    }
    for(int i=2;i<=T;i++) lg2[i]=lg2[i/2]+1;
}

void solve(){   
    int n,s,t;cin >> n >> s >> t;
    for(int i=1;i<=n;i++) g[i].clear();
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if(n==2){
        cout << s << ' ' << t << '\n';
        return;
    }
    else if(n==3){
        cout << s << ' ' << (s^t) << ' ' << t << '\n';
        return;
    }
    T=0;dfs(1,0);
    build();

    int K=5;
    vector<int> x;
    while(K--){
        x.clear();x.push_back(s);
        for(int i=1;i<=n;i++) if(i!=s && i!=t) x.push_back(i);
        shuffle(x.begin()+1,x.end(),rng);
        x.push_back(t);

        int d=0;
        for(int i=1;i<n;i++) d^=dist(x[i-1],x[i]);
        for(int t=n*15;t>0;t--){
            if(d<=1){
                for(int i=0;i<n;i++) cout << x[i] << ' ';
                cout << '\n';
                return;
            }
            int i=rand_int(1,n-2),j=rand_int(1,n-2);
            while(i==j) j=rand_int(1,n-2); 
            d^=dist(x[i],x[i-1])^dist(x[i],x[i+1])^dist(x[j],x[j-1])^dist(x[j],x[j+1]);
            swap(x[i],x[j]);
            d^=dist(x[i],x[i-1])^dist(x[i],x[i+1])^dist(x[j],x[j-1])^dist(x[j],x[j+1]);
        }
    }
    for(int i=0;i<n;i++) cout << x[i] << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}