#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e16;
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

#define ld long double

void solve(){
    int N;cin >> N;
    vector<int> f(N),X;
    ld S=0;
    for(int i=2;i<N;i++) if(!f[i]){
        X.push_back(i);S+=log(i);
        for(int j=i;j<N;j+=i) f[j]=1;
    }

    int n=(int)X.size();
    vector<int> A(X.begin(),X.begin()+n/2),B(X.begin()+n/2,X.end());
    n>>=1;

    vector<pair<ld,int>> P;
    for(int mask=0;mask<(1<<n);mask++){
        ld val=0;
        for(int i=0;i<n;i++) if(mask>>i&1) val+=log(B[i]);
        P.push_back({val,mask});
    }
    sort(P.begin(),P.end());

    ld mx=0;
    int fA=-1,fB=-1;S/=2;
    for(int mask=0;mask<(1<<n);mask++){
        ld val=0;
        for(int i=0;i<n;i++) if(mask>>i&1) val+=log(A[i]);
        int it=upper_bound(P.begin(),P.end(),pair<ld,int>{S-val,0})-P.begin()-1;
        if(it>=0){
            val+=P[it].first;
            if(val>mx) mx=val,fA=mask,fB=P[it].second;
        }
    }
    cout << setprecision(6) << fixed << S << ' ' << mx << '\n';

    int res=1;
    for(int i=0;i<n;i++) if(fA>>i&1) res=res*A[i]%mod;
    for(int i=0;i<n;i++) if(fB>>i&1) res=res*B[i]%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
