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

int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};

void solve(){
    int n;cin >> n;

    int T=0;
    vector<vector<int>> f(n,vector<int>(n,-1));
    for(int i=0;i<n;i+=2) for(int j=1;j<n;j+=2) f[i][j]=f[j][i]=T++;

    set<int> S;
    vector<vector<int>> g(2*n,vector<int>(2*n,-1));
    g[n][n]=0;g[n][n+1]=1;
    function<void(int,int,int,int)> dfs = [&](int i,int x,int y,int M){
        for(int t=0;t<4;t++){
            int xt=x+dx[t],yt=y+dy[t];
            if(g[xt][yt]!=-1) M|=1LL<<f[g[xt][yt]][i];
        }
        if(i==n-1){
            S.insert(M);
            return;
        }
        for(int t=0;t<4;t++){
            int xt=x+dx[t],yt=y+dy[t];
            if(g[xt][yt]!=-1) continue;
            g[xt][yt]=i+1;
            dfs(i+1,xt,yt,M);
            g[xt][yt]=-1;
        }
    };
    dfs(1,n,n+1,0);

    vector<int> ss;
    for(int x:S) ss.push_back(x);
    
    vector<int> X;
    for(int x:ss){
        bool add=true;
        for(int y:ss) if(x!=y && (x&y)==x){
            add=false;
            break;
        }
        if(add) X.push_back(x);
    }

    int total=0;
    for(int mask=0;mask<(1<<n);mask++){
        int Y=0;
        for(int i=0;i<n;i+=2) for(int j=1;j<n;j+=2) if((mask>>i&1) && (mask>>j&1)) Y|=(1LL<<f[i][j]);
        int mx=0;
        for(int x:X) mx=max(mx,(int)__builtin_popcountll(x&Y));
        total+=mx;
    }

    int k=n;
    while(total%2==0 && k>0) total/=2,k--;
    for(int i=0;i<k;i++) total*=5;
    string res=to_string(total);
    while((int)res.length()<=k) res="0"+res;

    res.insert(res.begin()+(int)res.length()-k,'.');
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
