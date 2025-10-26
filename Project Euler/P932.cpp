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
    int N=10000000000000000,S=0;

    auto cal = [&](int X,int k){
        int mod=X-1;
        vector<pair<int,int>> P;
        for(int i=2;i*i<=mod;i++){
            if(mod%i==0){
                int d=1;
                while(mod%i==0) d*=i,mod/=i;
                P.push_back({d,d/i*(i-1)});
            }
        }
        if(mod>1) P.push_back({mod,mod-1});
        int sz=(int)P.size();


        for(int mask=0;mask<(1<<sz);mask++){
            int s=0;
            for(int i=0;i<sz;i++){
                if(!(mask>>i&1)) continue;
                int val=(X-1)/P[i].first;
                int mul=power(val,P[i].second-1,P[i].first);
                s=(s+mul*val)%(X-1);
            }
            if(!s) s=X-1;
            int b=s*(X-s)/(X-1);
            int a=s-b;
            if((int)to_string(b).length()<k) continue;
            if(a*X+b>N || !a || !b) continue;
            S+=a*X+b;
        }
    };

    int x=1;
    for(int k=1;k<=9;k++){
        x*=10;
        cal(x,k);
    }
    cout << S << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
