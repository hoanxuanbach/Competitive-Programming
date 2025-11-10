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

#define ld long double 
const ld eps = 1e-6;

void solve(){
    //4*x*x + y*y = 100
    //y = a*x + b
    auto cal = [&](ld a,ld b,ld fx,ld fy){
        ld fa = a,fb = b;

        ld c = b*b-100;
        b = 2*a*b;
        a = a*a+4;
        c/=a;b/=a;
        ld s = sqrtl(b*b-4*c);

        ld x1=(s-b)/2,x2=(-s-b)/2;
        ld y1=fa*x1+fb,y2=fa*x2+fb;
        if(abs(x1-fx)>eps && abs(y1-fx)>eps) return make_pair(x1,y1);
        else return make_pair(x2,y2);
    };

    ld x=1.4,y=-9.6,m=(-19.7)/1.4;
    
    int cnt=0;
    while(cnt<10000 && (abs(x)>0.01 || y<0)){
        ld a = y/(4*x);
        ld b = (2*a-m+a*a*m)/(2*a*m-a*a+1);
        ld c = y-b*x;
        tie(x,y)=cal(b,c,x,y);
        cnt++;m=b;
    }
    cout << cnt << '\n';

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
