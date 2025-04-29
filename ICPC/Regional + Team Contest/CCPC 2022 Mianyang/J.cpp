// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define pii pair<int,int>
const int inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int pa,pb,pc,res=inf;
void solve(){
    res=inf;
    int n,a,b,c;cin >> n >>  a >> b >> c;
    if(a>b) swap(a,b);
    if(a>c) swap(a,c);
    if(b>c) swap(b,c);
    for(int i=0;i<=n;i++){
        int x=i*a+(n-i)*b,k=0;
        if(b!=c && n*(a+b+c)>3*x) k=min(n-i,(n*(a+b+c)-3*x)/(3*(c-b)));
        int d1=abs(3*(x+k*(c-b))-n*(a+b+c)),d2=abs(3*(x+(k+1)*(c-b))-n*(a+b+c));
        if(d1<res){res=d1;pa=i;pb=n-i-k;pc=k;}
        if(k<n-i && d2<res){res=d2;pa=i;pb=n-i-k-1;pc=k+1;}
    }
    for(int i=1;i<=n;i++){
        if(i<=pa) cout << a << endl;
        else if(i<=pa+pb) cout << b <<  endl;
        else cout << c <<  endl;
        int x,y;cin >> x >> y;
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;cin >> t;
    while(t--) solve();
}
