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
 
const int maxn = 1e7+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int cal(int n){
    function<int(int,int,int)> dfs = [&](int mask,int x,int d){
        if(mask==(1<<n)-1) return 1LL;
        int ret=0;
        if(x>=2 && !(mask>>(x-2)&1)) ret+=dfs(mask|(1<<(x-2)),x-2,d^1);
        if(x+2<n && !(mask>>(x+2)&1)) ret+=dfs(mask|(1<<(x+2)),x+2,d^1);
        int y=x;
        if(d) y++;
        else y--;
        if(0<=y && y<n && !(mask>>y&1)) ret+=dfs(mask|(1<<y),y,d);
        return ret;
    };
    int res=0;
    for(int i=0;i<n;i++){
        res+=dfs(1<<i,i,0);
        res+=dfs(1<<i,i,1);
    }
    return res;
}

int S[maxn],M=10;
vector<int> f = {2, -3, 5, -4, 4, -3, 1, -1};

void solve(){
    int n;cin >> n;
    if(n<=M) cout << cal(n) << '\n';
    else{
        for(int i=1;i<=M;i++) S[i]=cal(i);
        for(int i=M+1;i<=n;i++) for(int j=0;j<(int)f.size();j++) (S[i]+=S[i-j-1]*f[j])%=mod;
        cout << (S[n]+mod)%mod << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
