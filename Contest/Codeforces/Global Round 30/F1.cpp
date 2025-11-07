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

int d[maxn];
vector<int> g[maxn];
int fac[maxn],dfac[maxn];
int cur[maxn],cnt[maxn],h[maxn],f[maxn];
int res;

void add(int u,int x){
    if(h[u]>h[x]) h[u]++;
    else if(h[u]==h[x] && f[u]>f[x]) h[u]++;
    cnt[h[u]]++;
    for(int v:g[u]) add(v,x);
}

void cal(int u){
    for(int v:g[u]){
        add(v,u);
        for(int i=1;i<=d[u]+1;i++){
            cur[i]+=cnt[i];
            res=res*dfac[cnt[i]]%mod;
            cnt[i]=0;
        }
    }
    for(int i=1;i<=d[u]+1;i++){
        res=res*fac[cur[i]]%mod;
        cur[i]=0;
    }
    for(int v:g[u]) cal(v);
}

void solve(){
    int n;cin >> n;
    for(int i=1;i<=n;i++) g[i].clear(),d[i]=1;
    for(int i=2;i<=n;i++){
        int x;cin >> x;
        d[i]=d[x]+1;
        g[x].push_back(i);
    }

    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];

    fac[0]=dfac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;

    set<pii> S;
    for(int i=1;i<=n;i++) if(!a[i]) S.insert({d[i],i});

    function<void(int)> dfs = [&](int u){
        a[u]--;
        if(!a[u]) S.insert({d[u],u});
        for(int v:g[u]) dfs(v);
    };

    vector<int> ord;
    while(!S.empty()){
        pii x=*S.rbegin();S.erase(x);
        auto [dd,u]=x;
        ord.push_back(u);
        for(int v:g[u]) dfs(v);
    } 
    
    res=1;
    for(int i=0;i<n;i++) f[ord[i]]=i+1;
    for(int i=1;i<=n;i++) cout << f[i] << ' ';
    cout << '\n';
    for(int i=1;i<=n;i++) h[i]=1;
    cal(1);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
