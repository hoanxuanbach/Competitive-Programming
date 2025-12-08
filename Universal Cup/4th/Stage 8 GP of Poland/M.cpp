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
    int n,k;cin >> n >> k;k=min(k,n-1);
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin >> a[i] >> b[i];
    auto g = [&](int m,int d){
        m=min(m,d);
        return d*m-m*m/2;
    };
    auto f = [&](int S,int T){
        T=min(T,S);T=(S-T);
        return S*S*S-T*T*T;
    };

    ld res=0;
    auto sum = [&](int X,int Y){
        int g=__gcd(X,Y);X/=g;Y/=g;
        int T=X/Y;X%=Y;res+=T;
        ld cur=1;
        for(int t=0;t<20;t++){
            cur/=10;X*=10;
            res+=cur*(X/Y);
            X%=Y;
        }
    };
    vector<pair<int,int>> add;
    for(int i=1;i<n;i++){
        int d=(a[i]+b[i])*2;
        int X=3*(g(4*b[i-1],d)-g(4*a[i-1],d))*(b[i]-a[i]);
        int Y=(f(b[i],b[i-1])-f(b[i],a[i-1])-f(a[i],b[i-1])+f(a[i],a[i-1]))*8;
        int D=(b[i]-a[i])*(b[i-1]-a[i-1])*48;

        sum(X,D);
        add.push_back({Y-X,D}); 
    }
    sort(add.begin(),add.end(),[&](pii x,pii y){
        return (__int128)x.first*y.second>(__int128)x.second*y.first;
    });
    for(int i=0;i<k;i++) sum(add[i].first,add[i].second);
    cout << setprecision(20) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
