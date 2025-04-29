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
const int mod1=998244353;
const int mod2=1e9+7;
const int crt1=4924091;
const int crt2=993328907;
const int maxn=300005;
const int maxm=1505;
const int maxq=500005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n,int mod){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int n,m,cnt1[maxm][maxm],cnt2[maxm][maxm],sum[maxm][maxm],total[maxm][maxm],mul1[maxm][maxm],mul2[maxm][maxm];
int x[maxn],y[maxn],u[maxn],v[maxn];
void add(int a,int b,int sa,int ta,int m1,int m2){
    sum[a][b]+=sa;
    total[a][b]+=ta;
    mul1[a][b]=mul1[a][b]*m1%mod1;
    mul2[a][b]=mul2[a][b]*m2%mod2;
}
int cal_cnt1(int a,int b,int c,int d){
    return cnt1[c][d]-cnt1[a-1][d]-cnt1[c][b-1]+cnt1[a-1][b-1];
}
int cal_cnt2(int a,int b,int c,int d){
    return cnt2[c][d]-cnt2[a-1][d]-cnt2[c][b-1]+cnt2[a-1][b-1];
}
pii cal(int ss,int p1,int p2){
    int p=(((p1*crt2)%mod1*mod2))+((p2*crt1)%mod2)*mod1;
    p%=(mod1*mod2);
    int delta=ss*ss-4*p;
    int id1=(ss-sqrtl(delta))/2;
    return {id1,ss-id1};
}
int ok=0;
void solve(){
    cin >> n >> m;
    ok++;
    for(int i=0;i<=m;i++){
        for(int j=0;j<=m;j++){
            sum[i][j]=total[i][j]=cnt1[i][j]=cnt2[i][j]=0;
            mul1[i][j]=mul2[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++){
        cin >> x[i] >> u[i] >> y[i] >> v[i];
        int d1=power(i,mod1-2,mod1),d2=power(i,mod2-2,mod2);
        add(x[i],y[i],1,i,i,i);
        add(x[i],v[i]+1,-1,-i,d1,d2);
        add(u[i]+1,y[i],-1,-i,d1,d2);
        add(u[i]+1,v[i]+1,1,i,i,i);
    }
    int res=0,ans=0,Max1=0,Max2=0;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
            if(sum[i][j]==1) cnt1[i][j]++;
            else if(sum[i][j]==2) cnt2[i][j]++;
            total[i][j]+=total[i-1][j]+total[i][j-1]-total[i-1][j-1];
            cnt1[i][j]+=cnt1[i-1][j]+cnt1[i][j-1]-cnt1[i-1][j-1];
            cnt2[i][j]+=cnt2[i-1][j]+cnt2[i][j-1]-cnt2[i-1][j-1];
            mul1[i][j]=mul1[i][j]*mul1[i-1][j]%mod1;
            mul2[i][j]=mul2[i][j]*mul2[i-1][j]%mod2;
            res+=(sum[i][j]>=1);
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            mul1[i][j]=mul1[i][j]*mul1[i][j-1]%mod1;
            mul2[i][j]=mul2[i][j]*mul2[i][j-1]%mod2;
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            //cout << sum[i][j] << ' ';
            if(sum[i][j]==2){
                //cout << i << ' ' << j << '\n';
                pii id=cal(total[i][j],mul1[i][j],mul2[i][j]);
                int xn=max(x[id.fi],x[id.se]),yn=max(y[id.fi],y[id.se]),un=min(u[id.fi],u[id.se]),vn=min(v[id.fi],v[id.se]);
                int del=cal_cnt1(x[id.fi],y[id.fi],u[id.fi],v[id.fi])+cal_cnt1(x[id.se],y[id.se],u[id.se],v[id.se])+cal_cnt2(xn,yn,un,vn);
                ans=max(ans,del);
                //if(min(id.fi,id.se)==7 && max(id.fi,id.se)==10) cout << i << ' ' << j << '\n';
                //cout << id.first << ' ' << id.second << ' ' << del << '\n';
            }
        }
        //cout << '\n';
    }
    //cout << res << ' ' << ans << '\n';
    for(int i=1;i<=n;i++){
        int val=cal_cnt1(x[i],y[i],u[i],v[i]);
        if(val>Max1){Max2=Max1;Max1=val;}
        else if(val>Max2) Max2=val;
    }
    ans=max(ans,Max1+Max2);
    cout << res-ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
