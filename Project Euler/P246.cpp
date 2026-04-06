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
#define double long double
const double eps = 1e-7;
const double PI = acosl(-1);
void solve(){
    int A=7500*7500,B=A-5000*5000;
    double a=sqrtl(A),b=sqrtl(B);
    double K=acosl(-1.0)/4;

    int M=30000,res=0;
    for(int x=0;x<=M;x++){
        bool start=false;
        double preG = -1;
        for(int y=0;y<=M;y++){
            double R=(double)x*x/A+(double)y*y/B;
            if(R<=1) continue;
            double T=2*a*b*sqrtl(R-1);
            T/=x*x+y*y-A-B;
            double G=atan(T);
            if(G<0) G+=PI;
            if(G>=K){
                res+=2+2*(x && y);
                start=true;
            }
            else{
                if(start || G<preG-eps) break;
            }
            preG=G;
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
