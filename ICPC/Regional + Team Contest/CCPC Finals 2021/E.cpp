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
const int mod2=1e9+7;
const int maxn=200005;
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
struct step{
    char bl;
    int rt,pos;
};
int n,m,p=1;
void solve(){
    cin >> m >> n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;cin >> c;
            if(c=='#'){p=j;break;}
        }
        if(p!=0) break;
    }
    vector<step> ans;
    int cl=0,cr=0;
    if(p==1){
        ans.push_back({'T',2,1});
        cl=1;cr=3;
    }
    else if(p==m){
        ans.push_back({'T',2,m-2});
        cl=m-2;cr=m;
    }
    else{
        ans.push_back({'T',2,p-1});
        cl=p-1;cr=p+1;
    }
    while(cl>=3){
        ans.push_back({'S',0,cl-2});
        cl-=2;
    }
    while(cr<=m-2){
        ans.push_back({'Z',0,cr});
        cr+=2;
    }
    ans.push_back({'T',1,m-1});
    ans.push_back({'T',3,1});
    cl^=3;cr=m-((m-cr)^1);
    while(cl<cr-2){
        ans.push_back({'Z',0,cl});cl+=2;
    }
    ans.push_back({'T',0,cl});
    cout << (int)ans.size() << '\n';
    for(auto x:ans) cout << x.bl << ' ' << x.rt << ' ' << x.pos << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;//cin >> t;
    while(t--) solve();
}
