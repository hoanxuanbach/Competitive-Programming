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

const int S = 1000;

void solve(){
    int x,y,z,a,b,c;cin >> x >> y >> z >> a >> b >> c;
    
    int res=inf;
    for(int i=0;i<=(x+z+1)/2;i++){
        int d=i,cx=x,cy=y,cz=z,cost=i*a;
        int k=min(d,cx/2);
        cx-=2*k;d-=k;
        if(cx && d) d--,cz--,cx--;
        k=min(d,cz/2);
        cz-=2*k;d-=k;
        if(cz && d) d--,cz--;

        d=cx;cost+=cx*b;cx=0;
        k=min(d,cy);cy-=k;d-=k;
        k=min(d,cz);cz-=k;d-=k;

        int cost1=cost+((cy+cz+1)/2)*c;
        res=min(res,cost1);
        
        //cout << i << ' ' << cost1 << '\n';

        k=min(cz,cy);cost+=k*b;
        cz-=k;cy-=k;
        if(cz) cost+=((cz+1)/2)*b;
        else cost+=min(cy*b,(cy/2)*c+(cy&1)*b);
        res=min(res,cost);

        //cout << i << ' ' << cost << '\n';
    }
    cout << res << '\n';    

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}