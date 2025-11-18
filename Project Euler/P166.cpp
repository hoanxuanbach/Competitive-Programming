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

int F[20][20][20];

void solve(){
    for(int a=0;a<=9;a++) for(int b=0;b<=9;b++) for(int c=0;c<=9;c++) for(int d=0;d<=9;d++) F[a+b][b+c][c+d]++;

    int res=0;
    for(int a=0;a<=9;a++) for(int b=0;b<=9;b++) for(int c=0;c<=9;c++) for(int d=0;d<=9;d++){
        int T=a+b+c+d;
        for(int x=0;x<=9;x++) for(int y=0;y<=9;y++) for(int z=0;z<=9;z++){
            int t=T-x-y-z;
            if((b+c)!=(x+t)) continue;
            if(t<0 || t>9) continue;
            int ax=T-a-x;
            int by=T-b-y;
            int cz=T-c-z;
            int dt=T-d-t;
            int bz=T-b-z;
            int at=T-a-t;

            int mn=min({ax,by,cz,dt,bz,at}),mx=max({ax,by,cz,dt,bz,at});
            if(mn<0 || mx>18) continue;

            res+=F[ax][bz][dt]*F[by][at][cz];
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
