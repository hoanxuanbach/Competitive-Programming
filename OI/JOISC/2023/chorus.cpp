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
const int inf=9e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=1e6+5;
const int bl=650;
const int maxs=650;
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
    int a,b,c,p;
    bool operator<(line l){return a>l.a;}
    bool operator<(int k){return p<k;}
};
struct cvht{
    line x[maxn];
    int sz=0,pos=1;
    int div(int a,int b){
        return a/b-((a^b)<0 && a%b);
    }
    bool isect(line &l,line y){
        if(l.a==y.a){
            if(l.b<y.b) l.p=inf;
            else if(l.b>y.b) l.p=-inf;
            else l.p=(l.c<y.c?inf:-inf);
        }
        else l.p=div(y.b-l.b,l.a-y.a);
        return l.p>=y.p;
    }
    void add(line l){
        if(sz>0) isect(x[sz],l);
        while(sz>=2 && x[sz-1].p>=x[sz].p){
            sz--;
            isect(x[sz],l);
        }
        x[++sz]=l;
    }
    line query(int v){
        auto l=*lower_bound(x+1,x+sz+1,v);
        //pos=min(pos,sz);
        //while(pos<=sz && x[pos].p<v) pos++;
        //while(pos>1 && x[pos-1].p>=v) pos--;
        return l;
    }
};
cvht cht;
int a[maxn],b[maxn],bb[maxn],f[maxn],sum[maxn],na,nb,n,k;
pii dp[maxn];
pii cal(int mid){
    cht.sz=0;cht.pos=1;
    int cur=0;
    deque<int> dq;
    dq.push_back(0);
    for(int i=1;i<=n;i++){
        dp[i]={inf,-1};
        while(cur<n && i>=f[cur+1]){
            cur++;
            cht.add({2*f[cur]-2*bb[cur],2*dp[cur-1].fi-2*sum[f[cur]-1]+2*bb[cur]*(f[cur]-1)-f[cur]*f[cur]+f[cur],dp[cur-1].se,inf});
            if(!dq.empty() && dq.front()==cur-1) dq.pop_front();
        }
        line l=cht.query(i);
        if(!dq.empty()) dp[i]={dp[dq.front()].fi+mid,dp[dq.front()].se+1};
        if(cht.sz!=0) dp[i]=min(dp[i],{(i*l.a+l.b+2*sum[i]-i*i-i)/2+mid,l.c+1});
        while(!dq.empty() && dp[dq.back()]>dp[i]) dq.pop_back();
        dq.push_back(i);
        //cout << dp[i].fi << ' ' << dp[i].se << ' ' << cur << '\n';
    }
    return dp[n];
}
void solve(){
    cin >> n >> k;
    for(int i=1;i<=2*n;i++){
        char c;cin >> c;
        if(c=='A') a[++na]=i;
        else b[++nb]=i;
    }
    for(int i=1;i<=n;i++){
        bb[i]=0;
        sum[i]=a[i]+sum[i-1];
        int l=i,r=n;
        while(r>=l){
            int mid=(r+l)>>1;
            if(a[i]>b[mid]){bb[i]=mid-i+1;l=mid+1;}
            else r=mid-1;
        }
        if(bb[i]==0) bb[i]=b[i];
        else bb[i]=a[i]-bb[i];
        l=i,r=n;
        f[i]=n+1;
        while(r>=l){
            int mid=(r+l)>>1;
            if(a[mid]>bb[i]){f[i]=mid;r=mid-1;}
            else l=mid+1;
        }
        //cout << f[i] << ' ' << bb[i] << '\n';
    }
    int l=0,r=2e12,Min=0,use=0;
    while(r>=l){
        int mid=(r+l)>>1;
        pii res=cal(mid);
        if(res.se<=k){Min=res.fi;use=mid;r=mid-1;}
        else l=mid+1;
    }
    cout << Min-k*use << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}