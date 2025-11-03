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
    vector<bool> win(1<<N);
    win[0]=true;
    for(int i=1;i<(1<<N);i++){
        int d=0,val=1;
        bool start=false;
        win[i]=false;
        for(int j=N-1;j>=0;j--){
            if(i>>j&1) start=true,val*=9;
            int b=(i>>j&1);
            if(start){
                int ni=(d<<j)+(i&((1<<j)-1));
                if(!win[ni] || (ni==0 && b)) win[i]=true;
            }
            d=(d<<1|b);
        }
        if(win[i]) res+=val;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
