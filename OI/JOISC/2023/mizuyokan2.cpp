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
const int maxn=250005;
const int bl=400;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=65;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
void solve(){
    int n;cin >> n;
    vector<int> L(n,0),nxt(n,0),f(n,0);
    vector<pii> jmp(n);
    for(int i=0;i<n;i++) cin >> L[i];
    auto cal_f = [&](int i){
        int sum=0,j=i-1,st=max(0LL,i-maxl);
        while(j>=st && sum<=max(L[i],L[j])) sum+=L[j--];
        f[i]=(j>=st?j:-1);
    };
    auto cal_nxt = [&](int i){
        nxt[i]=i+1;
        while(nxt[i]<n && f[nxt[i]]<i) nxt[i]++;
    };
    auto build_jmp = [&](int x){
        for(int i=min(n,(x+1)*bl)-1;i>=x*bl;i--){
            int cur=nxt[i];
            if(cur<n && cur/bl==x) jmp[i]=jmp[cur],jmp[i].se++;
            else jmp[i]={cur,1};
        }
    };
    for(int i=0;i<n;i++) cal_f(i);
    for(int i=0;i<n;i++) cal_nxt(i);
    for(int i=0;i<=(n-1)/bl;i++) build_jmp(i);
    auto update = [&](int x,int y){
        L[--x]=y;
        int st=max(x-maxl,0LL),en=min(x+maxl,n-1);
        for(int i=x;i<=min(x+maxl,n-1);i++) cal_f(i);
        for(int i=st;i<=en;i++) cal_nxt(i);
        build_jmp(en/bl);
        if(en/bl!=st/bl) build_jmp(st/bl);
    };
    auto query = [&](int l,int r){
        if(l>r) return -inf;
        int cnt=0;
        while(nxt[l]<=r){
            if(jmp[l].fi<=r) cnt+=jmp[l].se,l=jmp[l].fi;
            else cnt++,l=nxt[l];
        }
        return cnt;
    };
    auto cal = [&](int l,int r){
        r--;
        int lt=l,sum=0;
        while(lt<n && sum<=L[lt]) sum+=L[lt++];
        int rt=r;sum=0;
        while(rt>=0 && sum<=L[rt]) sum+=L[rt--];
        int res=1;
        res=max(res,query(l,r)*2+1);
        res=max(res,max(query(lt,r),query(l,rt))*2+2);
        res=max(res,query(lt,rt)*2+3);
        return res;
    };
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int x,y,a,b;cin >> x >> y >> a >> b;
        update(x,y);
        cout << cal(a,b) << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
