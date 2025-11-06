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

    int cnt=0;
    for(int d=2;d<=N;d++){
        vector<int> f(d,1);
        for(int i=1;i<d;i++) f[i]=f[i-1]*10;

        vector<int> g;
        for(int i=0;i<d/2;i++) g.push_back(f[i]+f[d-i-1]);

        int val=-1;
        if(d&1) val=2*f[d/2];
        auto check = [&](int x){
            while(x){
                int k=x%10;x/=10;
                if(!(k&1)) return false;
            }
            return true;
        };
        function<void(int,int,int)> dfs = [&](int i,int x,int y){
            if(i==d/2){
                if(d&1){
                    for(int a=0;a<=9;a++) cnt+=x*check(y+a*val);
                }
                else cnt+=x*check(y);
                return;
            }
            for(int a=0;a<=18;a++){
                int ny=y+a*g[i];
                int nx=x;
                if(i){
                    int r=min(a,9LL);
                    int l=max(0LL,a-9);
                    if(l<=r) nx*=(r-l+1);
                    else nx=0LL;
                }
                else{
                    int r=min(a-1,9LL);
                    int l=max(1LL,a-9);
                    if(l<=r) nx*=(r-l+1);
                    else nx=0LL;
                }
                dfs(i+1,nx,ny);
            }
        };
        dfs(0,1,0);
    }
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
