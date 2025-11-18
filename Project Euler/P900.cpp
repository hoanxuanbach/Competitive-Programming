#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 900497239;
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
    int n;cin >> n;

    int res=0;
    for(int k=1;k<n;k++){
        int val=(power(4,k)-power(2,k+1)+power(2,k+(k/2))+mod)%mod;
        /*
        for(int x=(1<<k);x<(1<<(k+1));x++){
            int d=x&1,y=x*x;
            for(int j=0;j<=k;j++){
                if((y&1)!=d) val+=(1<<j),y++;
                y>>=1;
            }
        }
        */
        res=(res+val)%mod;
        //cout << val << '\n';
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
