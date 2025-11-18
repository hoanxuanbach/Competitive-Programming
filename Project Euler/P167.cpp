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

const int N = 4e7;
bool vis[N];
int s,f[N];

const int M = 1e11;
void solve(){
    auto cal = [&](int n){
        int m=M-1;s=0;
        int a=2,b=4*n+4;
        memset(vis,0,sizeof(vis));

        f[s++]=a;
        for(int x=2*n+1;x<=b;x+=2) f[s++]=x,vis[x>>1]=true;
        f[s++]=b;

        int L=0,R=0;
        bool period=false;
        for(int x=b+1;;x+=2) if(vis[(x-a)>>1]^vis[(x-b)>>1]){
            f[s++]=x,vis[x>>1]=true;
            if(f[s-1]-f[s-2]==b){
                if(!period){
                    L=s-2;
                    period=true;
                }
                else{
                    R=s-2;
                    break;
                }
            }
        }
        int T=R-L;
        if(m<s) return f[m];
        else{
            int k=(m-L)/T,d=f[R]-f[L];
            return f[L+(m-L)%T]+d*k;
        }
    };

    int res=0;
    for(int n=2;n<=10;n++) res+=cal(n);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
