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
    int n,m;cin >> n >> m;
    combi(n);
    vector<vector<int>> G(n);
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;u--;v--;
        G[u].push_back(v);G[v].push_back(u);
    }
    if(m>=n){
        cout << 0 << '\n';
        return;
    }
    if(n==2){
        cout << 2 << '\n';
        return;
    }
    int root=0;
    while((int)G[root].size()<=1) root++;

    vector<int> child;
    for(int v:G[root]) if((int)G[v].size()>1) child.push_back(v);

    int res=fac[(int)G[root].size()-(int)child.size()];
    if(!child.empty()) res=res*2%mod;

    if((int)child.size()>2){
        cout << 0 << '\n';
        return;
    }
    
    function<int(int,int)> dfs = [&](int u,int p){
        child.clear();
        for(int v:G[u]){
            if(v==p) continue;
            if((int)G[v].size()>1) child.push_back(v);
        }
        if((int)child.size()>1) return 0LL;
        int val=fac[(int)G[u].size()-1-(int)child.size()];
        if(!child.empty()) val=val*dfs(child[0],u)%mod;
        return val;
    };
    
    for(int v:child) res=res*dfs(v,root)%mod;
    cout << res*2%mod << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}