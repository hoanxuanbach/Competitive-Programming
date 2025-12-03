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
    int n,m,w,h;cin >> n >> m >> w >> h;
    vector<int> L(w+1,-h),R(w+1,h);

    auto cal = [&](int a,int b,int c,int d,int x){
        if(a==c) return min(b,d);
        int A=(d-b)*(x-a)+b*(c-a),B=(c-a);
        return A/B-(A%B<0);
    };

    int px=0,py=0;
    for(int i=0;i<n;i++){
        int cx,cy;cin >> cx >> cy;
        for(int j=px;j<=cx;j++) R[j]=min(R[j],-cal(px,-py,cx,-cy,j));
        px=cx,py=cy;
    }
    px=0,py=0;
    for(int i=0;i<m;i++){
        int cx,cy;cin >> cx >> cy;
        for(int j=px;j<=cx;j++) L[j]=max(L[j],cal(px,py,cx,cy,j));
        px=cx,py=cy;
    }

    int l=0,r=0;
    for(int i=1;i<=w;i++){
        l=max(l-1,L[i]+1);r=min(r+1,R[i]-1);
        if((l+i)&1) l++;
        if((r+i)&1) r--;
        if(l>r){
            cout << "impossible\n";
            return;
        }
    }
    cout << l << ' ' << r << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
