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
#pragma GCC target("popcnt,lzcnt")

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
const int inf=LLONG_MAX;
const int mod=998244353;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=2000000;
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
const int base=101;

struct line{
    int a,b,p,id;
    bool operator<(line l){return a<l.a;}
    bool operator<(int k){return p<k;}
};
struct cvht{
    vector<line> x;
    int div(int a,int b){
        return a/b-((a^b)<0 && a%b);
    }
    bool isect(line &l,line y){
        if(l.a==y.a) l.p=(l.b>y.b)?inf:-inf;
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
    void reset(){
        x.clear();
    }
    pii query(int v){
        auto l=*lower_bound(x.begin(),x.end(),v);
        return {l.a*v+l.b,l.id};
    }
}cht;

int n,q,ans[maxn],dd[maxn],dd2[maxn];
vector<pii> edge[maxn],query[maxn],pos[maxn],cc[maxn];
int D,Max[maxn];

void dfs(int u,int par){
    for(auto [v,w]:edge[u]){
        if(v==par) continue;
        dfs(v,u);cc[u].push_back({w,dd[v]+w});
        D=max(D,dd[u]+dd[v]+w);
        if(dd[v]+w>dd[u]){
            dd2[u]=dd[u];
            dd[u]=dd[v]+w;
        }
        else if(dd[v]+w>dd2[u]) dd2[u]=dd[v]+w;
    }
}

void redfs(int u,int par,int mx){
    for(auto [v,w]:edge[u]){
        if(v==par){
            cc[u].push_back({w,mx});
            continue;
        }
        int nxt=(dd[v]+w==dd[u]?dd2[u]:dd[u]);
        redfs(v,u,max(nxt,mx)+w);
    }
}

void solve(){
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        int u,k;cin >> u >> k;k--;
        query[u].push_back({k,i});
    }

    dfs(1,0);
    redfs(1,0,0);

    for(int u=1;u<=n;u++){
        sort(cc[u].begin(),cc[u].end());
        int sz=(int)cc[u].size();
        cht.reset();
        for(int i=0;i<sz;i++){
            cht.add({cc[u][i].fi,cc[u][i].se,inf,i});
            pos[i].clear();
        }
        for(auto [k,id]:query[u]){
            pii res=cht.query(k);ans[id]=res.fi;
            pos[res.se].push_back({k,id});
        }
        cht.reset();
        for(int i=0;i<sz;i++){
            for(auto [k,id]:pos[i]){
                if(i!=0) Max[id]=max(Max[id],cht.query(k).fi);
            }
            cht.add({cc[u][i].fi,cc[u][i].se,inf,i});
        }
        cht.reset();
        for(int i=sz-1;i>=0;i--){
            for(auto [k,id]:pos[i]){
                if(i!=sz-1) Max[id]=max(Max[id],cht.query(-k).fi);
            }
            cht.add({-cc[u][i].fi,cc[u][i].se,inf,i});
        }
    }

    for(int i=1;i<=q;i++) cout << max(ans[i]+Max[i],D) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
