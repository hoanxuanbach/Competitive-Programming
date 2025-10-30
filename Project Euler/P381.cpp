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
    vector<int> p(N,1);
    p[0]=p[1]=0;
    for(int i=2;i<N;i++) if(p[i]){
        for(int j=i*i;j<N;j+=i) p[j]=0;
    }

    int S=120,res=0;
    auto g = [&](int x,int k){
        int d=1;
        for(int i=1;i<=x;i++) d=d*i%k;
        return d;
    };
    for(int i=5;i<N;i++){
        if(!p[i]) continue;
        if(i<=S){
            int val=0;
            for(int j=1;j<=5;j++) val+=g(i-j,i);
            res+=(val%i);
        }
        else{
            int X=120,val=0;
            X=power(X,i-2,i);
            for(int j=5;j>=1;j--){
                X=X*(i-j)%i;
                val+=X;
            }
            res+=(val%i);
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
