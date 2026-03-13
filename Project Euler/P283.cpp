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

void solve(){
    int N;cin >> N;
    
    int res=0;
    for(int k=1;k<=N;k++){
        cout << k << endl;
        for(int x=1;x<=12*k*k;x++) for(int y=max(x,4*k*k/x+1);x*y<=12*k*k;y++){
            int d=4*k*k,a=x*y,b=x+y;
            if((b*d)%(a-d)==0){
                int z=(b*d)/(a-d);
                if(y<=z){
                    //cout << x+y << ' ' << x+z << ' ' << y+z << '\n';
                    res+=2*(x+y+z);
                }
            }
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
