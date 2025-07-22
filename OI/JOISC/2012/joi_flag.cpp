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
    int k,n;cin >> k >> n;
    vector<int> x(n),y(n),g(n);

    for(int i=0;i<n;i++){
        char C;cin >> x[i] >> y[i] >> C;
        x[i]--;y[i]--;
        if(C=='O') g[i]=1;
        else if(C=='I') g[i]=2;
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);

    function<int(int,vector<int>)> dp = [&](int t,vector<int> id){
        if(t==-1 || id.empty()) return 0LL;
        vector<vector<int>> f(4);
        vector<vector<int>> sum(4,vector<int>(3,0));

        for(int i:id){
            int a=x[i]>>t&1,b=y[i]>>t&1;
            f[2*a+b].push_back(i);
            sum[2*a+b][(g[i]+1)%3]++;
            sum[2*a+b][(g[i]+2)%3]++;
        }
        int res=inf;
        for(int i=0;i<4;i++){
            int cur=dp(t-1,f[i]);
            for(int a=0;a<4;a++){
                if(a==i) continue;
                for(int b=0;b<4;b++){
                    if(b==i || b==a) continue;
                    int c=a^b^i;
                    res=min(res,cur+sum[a][0]+sum[b][1]+sum[c][2]);
                }
            }
        }
        return res;
    };

    cout << dp(k-1,ord) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
/*
2 10
2 2 J
3 3 I
1 3 I
1 1 O
3 2 J
2 1 I
4 1 O
3 4 I
4 4 O
2 3 O
*/