#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
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

void solve(){
    int N;cin >> N;

    int res=0;
    vector<int> p(N+1);
    auto cal = [&](int n,vector<pii> X){
        int sz=(int)X.size(),val=0;
        vector<int> f(sz);
        for(int i=0;i<sz;i++) f[i]=(n/X[i].first)*power(n/X[i].first,X[i].second-1,X[i].first)%n;
        for(int i=0;i<(1<<sz);i++){
            int x=0;
            for(int j=0;j<sz;j++) if(i>>j&1) x=(x+f[j])%n;
            val=max(val,x);
        }
        res+=val;
    };
    for(int i=2;i<=N;i++){
        if(!p[i]){
            for(int j=i;j<=N;j+=i) p[j]=i;
        }
        int x=i;
        vector<pii> P;
        while(x>1){
            int j=p[x],k=1;
            while(x%j==0) x/=j,k*=j;
            P.push_back({k,k/j*(j-1)});
        }
        cal(i,P);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
