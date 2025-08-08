#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 1e9+7;
const int inv2 = (mod+1)/2;
const int maxn = 4e5+5;
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

void solve(){   
    int n,k;cin >> n >> k;
    vector<int> w(n+1),c(n+1);c[0]=1;
    for(int i=1;i<=n;i++) cin >> w[i];
    for(int i=1;i<=n;i++) cin >> c[i];
    vector<vector<int>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int res=0;
    vector<set<int>> s(n+1);
    function<void(int,int)> dfs = [&](int u,int p){
        vector<int> col;
        for(int v:g[u]) if(v!=p){
            dfs(v,u);
            if((int)s[u].size()<(int)s[v].size()) s[u].swap(s[v]);
            for(int x:s[v]){
                if(s[u].find(x)!=s[u].end()) col.push_back(x);
                else s[u].insert(x);
            }
        }
        sort(col.begin(),col.end());
        col.erase(unique(col.begin(),col.end()),col.end());
        if((int)col.size()>=2) res+=w[u];
        else if(!col.empty()){
            if(!c[u]) c[u]=col[0];
            if(c[u]!=col[0]) res+=w[u];
        }
        if(c[u]) s[u].insert(c[u]);
    };
    dfs(1,0);
    function<void(int,int)> dfs2 = [&](int u,int p){
        if(!c[u]) c[u]=c[p];
        for(int v:g[u]) if(v!=p) dfs2(v,u);
    };
    dfs2(1,0);
    cout << res << '\n';
    for(int i=1;i<=n;i++) cout << c[i] << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}