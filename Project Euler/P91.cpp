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
    for(int x=0;x<=N;x++) for(int y=0;y<=N;y++){
        for(int dx=0;dx<=N;dx++) for(int dy=1;dy<=N;dy++){
            int g=__gcd(dx,dy);
            if(g>1) continue;
            int A=0,B=0;
            int fA=0,fB=0;
            int cx=x+dx,cy=y+dy;
            while(cx<=N && cy<=N){
                if(cx==0 && cy==0) fA=1;
                A++,cx+=dx,cy+=dy;
            }
            cx=x-dx,cy=y-dy;
            while(cx>=0 && cy>=0){
                if(cx==0 && cy==0) fA=1;
                A++,cx-=dx,cy-=dy;
            }
            cx=x+dy,cy=y-dx;
            while(cx<=N && cy>=0){
                if(cx==0 && cy==0) fB=1;
                B++,cx+=dy,cy-=dx;
            }
            cx=x-dy,cy=y+dx;
            while(cx>=0 && cy<=N){
                if(cx==0 && cy==0) fB=1;
                B++,cx-=dy,cy+=dx;
            }
            if(x==0 && y==0){
                res+=A*B;
                //cout << '*' << A*B << '\n';
            }
            else if(fA){
                res+=B;
                //cout << "B " << x << ' ' << y << ' ' << B << '\n';
            }
            else if(fB){
                res+=A;
                //cout << "A " << x << ' ' << y << ' ' << A << '\n';
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
