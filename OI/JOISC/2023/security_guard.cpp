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
const int maxn=200005;
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
struct ed{
    int u,v,w;
    ed(int _u=-1,int _v=-1,int _w=-1):u(_u),v(_v),w(_w){}
    bool operator <(const ed &o)const{
        if(w!=o.w) return w<o.w;
        else if(u!=o.u) return u<o.u;
        else return v<o.v;
    }
};
void solve(){
    int n,m,q,mx=0,mn=inf,sum=0;cin >> n >> m >> q;
    vector<int> s(n+1),par(n+1,0),r(n+1,1);
    vector<ed> e;
    vector<set<ed>> ss(n+1);
    set<ed> st;
    map<pii,int> mp;
    for(int i=1;i<=n;i++) cin >> s[i],sum+=s[i],mx=max(mx,s[i]),mn=min(mn,s[i]),par[i]=i;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        e.push_back({u,v,s[u]+s[v]});
        mp[{u,v}]=mp[{v,u}]=s[u]+s[v];
    }
    function<int(int)> findpar = [&](int u){
        if(u!=par[u]) return par[u]=findpar(par[u]);
        return u;
    };
    function<void(int,int)> add = [&](int u,int val){
        if(ss[u].empty()) return;
        auto x = *ss[u].begin();
        //cout << x.u << ' ' << x.v << ' ' << x.w-s[u] << ' ' << val << '\n';
        if(val==-1) st.erase(ed(x.u,x.v,x.w-s[u]));
        else st.insert(ed(x.u,x.v,x.w-s[u]));
    };
    function<bool(int,int,int)> unions = [&](int u,int v,int t){
        int pu=findpar(u),pv=findpar(v);
        if(pu==pv) return false;
        if(r[pu]<r[pv]) swap(pu,pv),swap(u,v);
        par[pv]=pu;r[pu]+=r[pv];
        if(t){
            int w=mp[{u,v}];
            add(pu,-1);add(pv,-1);
            ss[pu].erase(ed(u,v,w));
            ss[pv].erase(ed(v,u,w));
            s[pu]=min(s[pu],s[pv]);
            for(auto x:ss[pv]) ss[pu].insert(x);
            add(pu,1);
        }
        return true;
    };
    sort(e.begin(),e.end());
    for(auto x:e){
        if(unions(x.u,x.v,0)){
            ss[x.u].insert(ed(x.u,x.v,x.w));
            ss[x.v].insert(ed(x.v,x.u,x.w));
        }
    }
    for(int i=1;i<=n;i++) par[i]=i,r[i]=1;
    int cur=sum;
    for(int i=1;i<=n;i++) add(i,1);
    vector<int> ans(n,0);
    for(int i=n-1;i>=1;i--){
        ans[i]=cur+(i-1)*mn-sum+mx;
        ed x=*st.begin();cur+=x.w;
        //cout << x.u << ' ' << x.v << ' ' << x.w << '\n';
        unions(x.u,x.v,1);
    }
    ans[0]=cur-mn-sum+mx;
    for(int i=0;i<=q;i++) cout << (i<n?ans[i]:ans[n-1]) << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
