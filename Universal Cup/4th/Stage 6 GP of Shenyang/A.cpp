#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int> 
const int maxn = 2e5+5;
const int mod = 998244353;
#define i128 __int128

void solve(){
    int n,K,A,B;
    cin >> n >> K >> A >> B;
    int lim=sqrtl(K);
    auto cal = [&](int X){
        int cnt=0,d=1;
        while(d<n){
            int T=X/d;
            if(T<2*B) return cnt;
            T-=2*B;T/=A;
            if(T<d+2) return cnt;
            int r=min(n-d,(T-d)/2);
            cnt+=r;
            if(cnt>=K) return cnt;
            if(r!=n-d && r<lim) break;
            d++;
        }
        if(d==n) return cnt;
        for(int x=lim-1;x>=1;x--){
            int T=A*x+B;
            i128 S=(i128)X*A+(i128)T*T;
            int nd=sqrtl(S);
            nd-=T;nd/=A;
            nd=min(nd,n-x);
            if(d<=nd){
                cnt+=(nd-d)*x;
                d=nd;
            }
            if(cnt>=K) return cnt;
        }
        return cnt;
    };

    int l=1,r=8e18,res=0;
    while(l<=r){
        int x=l+(r-l)/2;
        if(cal(x)>=K) res=x,r=x-1;
        else l=x+1;
    }
    int g=__gcd(res,A);
    cout << res/g << ' ' << A/g << '\n';

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}