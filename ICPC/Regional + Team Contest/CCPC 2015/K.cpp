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
const int maxn=4005;
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
struct line{
    int a,b,p;
    bool operator<(line l){return a>l.a;}
    bool operator<(int k){return p<k;}
};
struct cvht{
    vector<line> x;
    int div(int a,int b){
        return a/b-((a^b)<0 && a%b);
    }
    bool isect(line &l,line y){
        if(l.a==y.a) l.p==(l.b<y.b)?inf:-inf;
        else l.p=div(y.b-l.b,l.a-y.a);
        return l.p>=y.p;
    }
    void add(line l){
        if(!x.empty()) isect(x.back(),l);
        while((int)x.size()>=2 && x[(int)x.size()-2].p>=x.back().p){
            x.pop_back();
            isect(x.back(),l);
        }
        x.push_back(l);
    }
    int query(int v){
        if(x.empty()) return inf;
        auto l=*lower_bound(x.begin(),x.end(),v);
        return l.a*v+l.b;
    }
    void reset(){
        x.clear();
    }
}cht[2][2];
int n,cnt=0,p[2][maxn],pre[2][maxn],preup[2][maxn],predown[2][maxn];
int dp[maxn][2][2];
/*
dim1: 0: up 1:down
dim2: 0: col0 1:col1
dp[i][0][0] = dp[j][1][1] + calup(j+1,i,0)=preup[0][i]-preup[0][j]-j*(pre[0][i]-pre[0][j]) => preup[0][i]-pre[0][i]*j -preup[0][j]+j*pre[0][j]
dp[i][0][1] = dp[j][1][0] + calup(j+1,i,1)=preup[1][i]-preup[1][j]-j*(pre[1][i]-pre[1][j]) => preup[1][i]-pre[1][i]*j -preup[1][j]+j*pre[1][j]
dp[i][1][0] = dp[j][0][0] + caldown(j+1,i,0)=predown[0][i]-predown[0][j]-(n-i)*(pre[0][i]-pre[0][j]) => predown[0][i]-(n-i)*pre[0][i] + -pre[0][j]*-(n-i)-predown[0][j]
dp[i][1][1] = dp[j][0][1] + caldown(j+1,i,1)=predown[1][i]-predown[1][j]-(n-i)*(pre[1][i]-pre[1][j]) =>
*/
void solve(){
    cin >> n;cnt++;
    for(int i=1;i<=n;i++) cin >> p[0][i] >> p[1][i];
    for(int i=1;i<=n;i++){
        for(int j=0;j<=1;j++){
            pre[j][i]=pre[j][i-1]+p[j][i];
            preup[j][i]=preup[j][i-1]+p[j][i]*i;
            predown[j][i]=predown[j][i-1]+p[j][i]*(n-i+1);
        }
    }
    for(int i=0;i<=1;i++){
        for(int j=0;j<=1;j++) cht[i][j].reset();
    }
    cht[0][1].add({0,0,inf});cht[0][0].add({0,0,inf});
    dp[0][1][1]=dp[0][1][0]=inf;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=1;j++){
            for(int k=0;k<=1;k++) dp[i][j][k]=inf;
        }
        dp[i][0][0]=min(dp[i][0][0],preup[0][i]+cht[1][1].query(pre[0][i]));
        dp[i][0][1]=min(dp[i][0][1],preup[1][i]+cht[1][0].query(pre[1][i]));
        dp[i][1][0]=min(dp[i][1][0],predown[0][i]-(n-i)*pre[0][i]+cht[0][0].query(i-n));
        dp[i][1][1]=min(dp[i][1][1],predown[1][i]-(n-i)*pre[1][i]+cht[0][1].query(i-n));
        dp[i][1][0]=min(dp[i][1][0],dp[i-1][1][1]+p[0][i]);
        dp[i][1][1]=min(dp[i][1][1],dp[i-1][1][0]+p[1][i]);
        if(dp[i][0][0]!=inf) cht[0][0].add({-pre[0][i],dp[i][0][0]-predown[0][i],inf});
        if(dp[i][0][1]!=inf) cht[0][1].add({-pre[1][i],dp[i][0][1]-predown[1][i],inf});
        if(dp[i][1][0]!=inf) cht[1][0].add({-i,dp[i][1][0]+i*pre[1][i]-preup[1][i],inf});
        if(dp[i][1][1]!=inf) cht[1][1].add({-i,dp[i][1][1]+i*pre[0][i]-preup[0][i],inf});
    }
    cout << "Case #" << cnt << ": " << min(dp[n][0][0],dp[n][0][1]) << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}

