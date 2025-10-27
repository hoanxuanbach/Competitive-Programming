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
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int N;cin >> N;
    int S=sqrtl(N);
    vector<int> p(S+1);
    for(int i=2;i<=S;i++){
        if(!p[i]){
            for(int j=i;j<=S;j+=i) p[j]=i;
        }
    }
    int res=0;
    for(int i=1;i<=S;i++){
        vector<int> pp;
        int x=i;
        while(x>1){
            int j=p[x];
            while(x%j==0) x/=j;
            pp.push_back(j);
        }
        int sz=(int)pp.size();
        array<int,2> S={0,0};
        for(int j=0;j<(1<<sz);j++){
            int d=1,t=1;
            for(int k=0;k<sz;k++) if(j>>k&1) d*=pp[k],t^=1;
            //cout << i << ' ' << d << '\n';
            d=i/d;
            S[t]=(S[t]+d*d)%mod;
        }
        res=(res+(N/(i*i))%mod*(S[1]-S[0]+mod))%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
