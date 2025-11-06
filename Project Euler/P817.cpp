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

    int res=0;
    for(int i=1;i<=N;i++){
        int x=mod-i;

        int s=power(x,(mod-1)/2);
        int d=inf;

        if(s!=mod-1){
            d=power(x,(mod+1)/4);
            if(d>mod-d) d=mod-d;
            assert(d*d%mod==x);
        }
        cout << i << endl;
        int t=0;
        bool check=false;
        while(!check){
            __int128 val=(__int128)t*mod*mod+x*mod;
            __int128 k=sqrtl(val);
            assert(0<=k<inf);
            while((__int128)k*k>=val) k--;
            while((__int128)k*k<val) k++;
            if((__int128)k*k<val+mod) d=min(d,(int)k),check=true;
            t++;
        }
        assert(check);
        res+=d;
        //cout << i << ' ' << d << '\n';
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
