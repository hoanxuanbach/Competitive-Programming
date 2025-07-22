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
const int maxn = 1e5+5;
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

int n,a[maxn],res;
vector<int> edge[maxn],A[maxn],B[maxn];

void get(vector<int> &y,vector<int> &x){
    for(int i=0;i<(int)y.size();i++){
        int pos=lower_bound(x.begin(),x.end(),-y[i])-x.begin();
        res=max(res,pos+i+1);
    }
}

void update(vector<int> &x,int val){
    int pos=lower_bound(x.begin(),x.end(),val)-x.begin();
    if(pos==(int)x.size()) x.push_back(val);
    else x[pos]=val;
}

void merg(vector<int> &x,vector<int> &y){
    for(int i=0;i<(int)y.size();i++) x[i]=min(x[i],y[i]);
}

void dfs(int u,int p){
    A[u].push_back(a[u]);B[u].push_back(-a[u]);
    for(int v:edge[u]){
        if(v==p) continue;
        dfs(v,u);
        if((int)A[u].size()<(int)B[v].size()) get(A[u],B[v]);
        else get(B[v],A[u]);
        if((int)A[v].size()<(int)B[u].size()) get(A[v],B[u]);
        else get(B[u],A[v]);

        update(A[v],a[u]);update(B[v],-a[u]);
        if((int)A[u].size()<(int)A[v].size()) swap(A[u],A[v]);
        if((int)B[u].size()<(int)B[v].size()) swap(B[u],B[v]);
        merg(A[u],A[v]);merg(B[u],B[v]);
    }
}

void solve(){   
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,0);
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
/*
7
4
2
5
3
1
8
7
1 2
2 3
3 4
4 5
3 6
6 7
*/