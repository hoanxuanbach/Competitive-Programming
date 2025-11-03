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
    int cnt=0,M=0;
    while(cnt<=1000000){
        cnt=0;M++;
        for(int x=1;x<=M;x++) for(int y=x+1;x*y<=M;y++){
            if((x&1) && (y&1)) continue;
            if(__gcd(x,y)!=1) continue;
            int a=2*x*y,b=y*y-x*x;
            
            if(b<=M){
                for(int k=1;b*k<=M;k++){
                    int r=min(a*k-1,b*k);
                    int l=(a*k+1)/2;
                    //cout << '*' << a << ' ' << b << ' ' << l << ' ' << r << '\n';
                    if(l<=r) cnt+=(r-l+1);
                }
            }
            swap(a,b);
            if(b<=M){
                for(int k=1;b*k<=M;k++){
                    int r=min(a*k-1,b*k);
                    int l=(a*k+1)/2;
                    //cout << '*' << a << ' ' << b << ' ' << l << ' ' << r << '\n';
                    if(l<=r) cnt+=(r-l+1);
                }
            }
        } 
        /*
        for(int a=1;a<=M;a++) for(int b=a;b<=M;b++) for(int c=b;c<=M;c++){
            int s=(a+b)*(a+b)+c*c;
            int x=sqrtl(s);
            if(x*x==s) cnt+=1;
        }
        */
        cout << M << ' ' << cnt << endl;
    }
    cout << M << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
