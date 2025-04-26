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
const int maxn=(1<<17)+5;
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
int n,a[maxn],c[maxn],dp[maxl][maxn],ans=inf,cn=-1,cmask=-1;
vector<int> v;
void cal(int x){
    //for(int i=0;i<(1<<n);i++) cout << a[i] << ' ';
    //cout << '\n';
    for(int j=1;j<=n;j++){
        for(int i=0;i<(1<<n);i+=(1<<j)){
            int num=0,l=i,cur=0;
            for(int k=i+(1<<(j-1));k<(i+(1<<j));k++){
                while(l<(i+(1<<(j-1))) && a[l]<a[k]) v[cur++]=a[l++];
                num+=(i+(1<<(j-1)))-l;v[cur++]=a[k];
            }
            //cout << j << ' ' << i << ' ' << num << '\n';
            while(l<(i+(1<<(j-1)))) v[cur++]=a[l++];
            for(int k=0;k<(1<<j);k++) a[i+k]=v[k];
            for(int k=0;k<(1<<j);k++){
                int d=k&((1<<(j-1))-1);
                dp[j][i+k]=dp[j-1][i+d]+dp[j-1][i+(1<<(j-1))+d];
                if(k&(1<<(j-1))) dp[j][i+k]+=(1LL<<(2*j-2))-num;
                else dp[j][i+k]+=num;
            }
        }
    }
    for(int i=0;i<(1<<n);i++){
        if(dp[n][i]<ans){ans=dp[n][i];cn=x;cmask=i;}
    }
}
void solve(){
    cin >> n;v.assign((1<<n),0);
    if(n==0){
        cout << 0 << '\n';
        cout << 2 << '\n';
        return;
    }
    for(int i=0;i<(1<<n);i++) cin >> a[i];
    for(int i=0;i<n;i++){
        for(int j=0;j<(1<<n);j++) c[j]=a[j];
        cal(i);
        for(int j=0;j<(1<<n);j++){
            int cur=j;cur=(j>>1)+(1<<(n-1))*(j&1);
            a[cur]=c[j];
        }
    }
    cout << ans << '\n';
    string s;
    for(int i=1;i<=cn;i++) s.push_back('2');
    for(int i=0;i<n;i++){
        s.push_back('2');
        if(cmask&(1<<i)) s.push_back('1');
    }
    cout << s << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;//cin >> t;
    while(t--) solve();
}
