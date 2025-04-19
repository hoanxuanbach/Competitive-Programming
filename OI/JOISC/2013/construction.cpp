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
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/

#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=131;

vector<piii> e;

struct Rec{
    int x,y,u,v;
}rec[maxn];
int X[maxn],Y[maxn];
int n,m,q;

void build(){
    map<int,vector<pii>> mp;
    for(int i=1;i<=n;i++) mp[X[i]].push_back({Y[i],i});
    for(int i=1;i<=m;i++){
        mp[rec[i].x].push_back({rec[i].y,0});
        mp[rec[i].u+1].push_back({rec[i].y,-1});
    }
    multiset<int> s;
    for(auto &it:mp){
        vector<pii> cc;
        for(auto [p,id]:it.se){
            if(id==0) s.insert(p);
            else if(id==-1) s.erase(s.find(p));
            else cc.push_back({p,id});
        }
        sort(cc.begin(),cc.end());
        for(int i=0;i<(int)cc.size()-1;i++){
            int x=cc[i].fi;
            auto it=s.lower_bound(x);
            if(it==s.end() || cc[i+1].fi<*it){
                e.push_back({cc[i+1].fi-cc[i].fi,{cc[i].se,cc[i+1].se}});
            }
        }
    }
}

int par[maxn];
int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
bool unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return false;
    return par[v]=u,true;
}

vector<pii> qq[maxn];
int val[maxn],res[maxq];

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
        if(l.a==y.a) l.p=(l.b<y.b)?inf:-inf;
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
        if(x.empty()) return -1;
        auto l=*lower_bound(x.begin(),x.end(),v);
        return l.a*v+l.b;
    }
}cht;

void solve(){
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++) cin >> X[i] >> Y[i],par[i]=i;
    for(int i=1;i<=m;i++) cin >> rec[i].x >> rec[i].y >> rec[i].u >> rec[i].v;
    build();
    for(int i=1;i<=n;i++) swap(X[i],Y[i]);
    for(int i=1;i<=m;i++) swap(rec[i].x,rec[i].y),swap(rec[i].u,rec[i].v);
    build();

    sort(e.begin(),e.end());
    vector<int> d;
    for(auto [w,x]:e) if(unions(x.fi,x.se)) d.push_back(w);
    memset(val,-1,sizeof(val));
    val[n]=0;
    int sum=0;
    for(int i=0;i<(int)d.size();i++){
        sum+=d[i];
        val[n-i-1]=sum;
    }

    for(int i=1;i<=q;i++){
        int h,b;cin >> b >> h;
        qq[h].push_back({b,i});
    }
    for(int i=1;i<=n;i++){
        if(val[i]!=-1) cht.add({-i,val[i],inf});
        for(auto [x,id]:qq[i]) res[id]=cht.query(-x);
    }
    for(int i=1;i<=q;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
