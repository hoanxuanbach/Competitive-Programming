#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int N=10000019;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

pii add(pii a,pii b){
    a.first=(a.first+b.first)%mod;
    a.second=(a.second+b.second)%mod;
    return a;
}
pii nxt(pii a,int x){
    a.first=(a.first+a.second*x)%mod;
    return a;
}

pii bit[N+100][4];

void update(int x,int k,pii val){
    x++;
    for(int i=x;i<=N;i+=(i&(-i))) bit[i][k]=add(bit[i][k],val);
}
pii query(int x,int k){
    pii res={0,0};
    for(int i=x;i>=1;i-=(i&(-i))) res=add(res,bit[i][k]);
    return res;
}

const int maxn = 1e6+5;
pii dp[maxn][5];

void solve(){
    int n;cin >> n;
    vector<int> a(n+1);a[0]=1;
    for(int i=1;i<=n;i++) a[i]=a[i-1]*153%N;

    int res=0;
    for(int i=1;i<=n;i++){
        dp[i][1]={a[i],1};
        for(int j=2;j<=4;j++) dp[i][j]=nxt(query(a[i],j-1),a[i]);
        res=(res+dp[i][4].first)%mod;
        for(int j=1;j<=3;j++) update(a[i],j,dp[i][j]);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
