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
    int n;cin >> n;
    vector<int> p(n);
    for(int i=0;i<n;i++) cin >> p[i];

    vector<int> f(n+1);

    vector<int> g(n),a(n);
    function<void(int,int)> dnc = [&](int l,int r){
        if(l>=r-1) return;
        vector<pair<int,int>> bit(n+1,{-inf,-1});
        auto update = [&](int x,pair<int,int> val){
            for(int i=x;i<=n;i+=(i&(-i))) bit[i]=max(bit[i],val);
        };
        auto query = [&](int x){
            pair<int,int> res={-inf,-1};
            for(int i=x;i>=1;i-=(i&(-i))) res=max(res,bit[i]);
            return res;
        };
        
        int x=r-l,y=f[r]-f[l];
        for(int i=0;i<n;i++){
            g[i]=x-y;
            a[i]=1;
            
            auto [d,j]=query(p[i]);
            if(d+x>g[i]){
                g[i]=d+x;
                a[i]=j;
            }
            if(i && g[i-1]+x-y>g[i]){
                g[i]=g[i-1]+x-y;
                a[i]=a[i-1]+1;
            }
            update(p[i],{g[i],a[i]});
            if(i && g[i-1]>g[i]){
                g[i]=g[i-1];
                a[i]=a[i-1];
            }
        }
        int G=-inf,A=-1;
        for(int i=0;i<n;i++) if(g[i]>G) A=a[i],G=g[i];
        f[A]=(G+A*y)/x;
        if((f[r]-f[A])*(A-l)==(f[A]-f[l])*(r-A)){
            int d=(f[r]-f[l])/(r-l);
            for(int i=l+1;i<r;i++) f[i]=f[i-1]+d;
            return;
        }
        dnc(l,A);dnc(A,r);
        
    };
    f[n]=n;
    dnc(0,n);
    for(int i=1;i<=n;i++) cout << f[i] << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
