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

void solve(){
    ld res=0;
    int cnt=0;

    auto calD = [&](ld qx,ld qy,ld rx,ld ry,ld sx,ld sy){
        ld a = qx*qx+qy*qy;
        ld b = rx*rx+ry*ry;
        ld c = sx*sx+sy*sy;
        ld d = 2*(qx*(ry-sy)+rx*(sy-qy)+sx*(qy-ry));

        ld dx = (a*(ry-sy)+b*(sy-qy)+c*(qy-ry))/d;
        ld dy = (a*(sx-rx)+b*(qx-sx)+c*(rx-qx))/d;

        return pair<ld,ld>{dx,dy};
    };
    auto calE = [&](ld S,ld R,ld X,ld Y,ld ra,ld rb,ld rc){
        ld da = ra-R;
        ld db = rb-R;
        ld dc = rc-R;

        ld ex = (S*S-(db-da)*(da+db))/(2*S);
        ld rhs = dc*dc-da*da-(X*X+Y*Y);
        ld ey = -(rhs+2*ex*X)/(2*Y);

        return pair<ld,ld>{ex,ey};
    };

    for(int ra=1;ra<=100;ra++) for(int rb=ra+1;rb<=100;rb++) for(int rc=rb+1;rc<=100;rc++){
        int g=__gcd(ra,__gcd(rb,rc));
        if(g!=1) continue;
        cnt++;
        int S=ra+rb,A=ra+rc,B=rb+rc;
        ld R=(ld)ra*rb*rc/(ra*rb+rb*rc+rc*ra+2*sqrtl(ra*rb*rc*(ra+rb+rc)));
        ld X=(ld)(A*A+S*S-B*B)/(2*S);
        ld Y=sqrtl(A*A-X*X);

        pair<ld,ld> D=calD(ra,0,ra*X/A,ra*Y/A,S+rb*(X-S)/B,rb*Y/B);
        pair<ld,ld> E=calE(S,R,X,Y,ra,rb,rc);

        auto [dx,dy]=D;
        auto [ex,ey]=E;
        ld dist=sqrtl((dx-ex)*(dx-ex)+(dy-ey)*(dy-ey));
        res+=dist;
    }
    cout << setprecision(8) << fixed << res/cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
