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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=1000005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
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
const int base=101;

struct line{
    int a,b,p;
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
    int query(int v){
        auto l=*lower_bound(x.begin(),x.end(),v);
        return l.a*v+l.b;
    }
}cht[2*maxn];

int n,m,dist[maxn],val[maxn],deg[maxn],cnt;
vector<pii> s[maxn],edge[maxn];
vector<pii> pos[maxn];

void solve(){
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int k;cin >> k;
        s[i].assign(k+1,mpp(0,0));
        for(int j=0;j<=k;j++){
            cin >> s[i][j].fi;
            if(j<k) cin >> s[i][j].se;
            if(j) edge[s[i][j-1].fi].push_back({s[i][j].fi,s[i][j-1].se});
        }
    }
    for(int i=1;i<=n;i++) dist[i]=inf;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    dist[1]=0;pq.push({0,1});
    while(!pq.empty()){
        int u=pq.top().se,d=pq.top().fi;pq.pop();
        if(dist[u]!=d) continue;
        for(auto [v,w]:edge[u]){
            if(d+w<dist[v]){
                dist[v]=d+w;
                pq.push({d+w,v});
            }
        }
    }
    for(int i=1;i<=m;i++){
        int sz=(int)s[i].size(),sum=0;
        pos[s[i][0].fi].push_back({++cnt,sum});
        for(int j=1;j<sz;j++){
            sum+=s[i][j-1].se;
            if(dist[s[i][j-1].fi]+s[i][j-1].se==dist[s[i][j].fi]){
                deg[s[i][j].fi]++;
                pos[s[i][j].fi].push_back({cnt,sum});
            }
            else pos[s[i][j].fi].push_back({++cnt,sum});
        }
    }
    queue<int> q;
    for(int i=1;i<=n;i++) if(deg[i]==0) q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(auto [v,w]:edge[u]){
            if(dist[v]==dist[u]+w){
                deg[v]--;
                if(deg[v]==0) q.push(v);
            }
        }
        for(pii p:pos[u]){
            if(cht[p.fi].x.empty()) continue;
            val[u]=max(val[u],cht[p.fi].query(-2*p.se)+p.se*p.se);
        }
        for(pii p:pos[u]) cht[p.fi].add({p.se,val[u]+p.se*p.se,inf});
    }
    cout << dist[n] << ' ' << val[n] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
