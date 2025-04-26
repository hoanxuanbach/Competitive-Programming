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
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=15;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int C(int k,int n){
    if(k<0) return 0;
    int res=1;
    for(int i=n;i>=n-k+1;i--) res*=i;
    for(int i=1;i<=k;i++) res/=i;
    return res;
}
int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};
int n,m;
char c[maxn][maxn];
void solve(){
    cin >> n >> m;
    int k=0,sum=0,num=0,total=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> c[i][j];
            if(c[i][j]=='O') sum+=i+j;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> c[i][j];
            if(c[i][j]=='O'){sum+=i+j;k++;}
        }
    }
    if(sum&1){
        cout << 0 << '\n';
        return;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int t=0;t<4;t++){
                int xt=i+dx[t],yt=j+dy[t];
                if(xt<=0 || yt<=0 || xt>n || yt>m) continue;
                if(c[i][j]=='O' && c[xt][yt]!='O') num++;
                total+=C(k-1,n*m-2);
            }
        }
    }
    total/=2;
    long double ans=num;ans/=total;
    cout << setprecision(15) << fixed << ans << '\n';
}
signed main(){
    //freopen("WIE.INP","r",stdin);
    //freopen("WIE.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
