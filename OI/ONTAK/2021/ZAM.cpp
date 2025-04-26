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
#define piii pair<long long,pii>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

//Query
int q,pa[maxn],xa[maxn],ya[maxn],pb[maxn],xb[maxn],yb[maxn];

//Tree
int n,cnt,cx[maxn],par[maxn][maxl],dep[maxn];
pii range[maxn],Range[maxn][maxl];
int sx[maxn][maxl];
piii cost[maxn][2][maxl];

vector<pii> edge[maxn];

void dfs(int u,int p){
    par[u][0]=p;dep[u]=dep[p]+1;
    for(int i=1;i<18;i++) par[u][i]=par[par[u][i-1]][i-1];
    for(auto [v,x]:edge[u]){
        if(v==p) continue;
        cx[v]=x;dfs(v,u);
    }
    range[u].fi=max(range[u].fi,range[p].fi);
    range[u].se=min(range[u].se,range[p].se);
    Range[u][0]=range[u];
    sx[u][0]=abs(cx[u]-cx[p]);
    //cout << u << ' ' << p << ' ' << range[u].fi << ' ' << range[u].se << '\n';
}

int lca(int u,int v){
    if(dep[u]>dep[v]) swap(u,v);
    for(int i=0;i<18;i++){
        if((dep[v]-dep[u])&(1<<i)) v=par[v][i];
    }
    if(u==v) return u;
    for(int i=17;i>=0;i--){
        if(par[u][i]!=par[v][i]){
            u=par[u][i];
            v=par[v][i];
        }
    }
    return par[u][0];
}

pii f(int u,int t,int a){
    int res=0;
    for(int i=17;i>=0;i--){
        piii nxt=cost[u][t][i];
        if(dep[nxt.se.fi]>dep[a]){
            res+=nxt.fi;
            u=nxt.se.fi;
            t=nxt.se.se;
        }
    }
    if(t==0) return {res,range[u].fi};
    else return {res,range[u].se};
}

piii jmp(int x,int y,int u,int a){
    if(u==a) return {0LL,{x,y}};
    int res=abs(x-cx[u]);

    int v=u;
    for(int i=0;i<18;i++){
        if((dep[v]-dep[a]-1)&(1<<i)){
            res+=sx[v][i];
            v=par[v][i];
        }
    }
    x=cx[v];

    for(int i=17;i>=0;i--){
        if(Range[u][i].fi<=y && y<=Range[u][i].se) u=par[u][i];
    }
    if(dep[u]>dep[a]){
        int t=0;
        if(y>range[u].se) t=1,res+=y-range[u].se;
        else res+=range[u].fi-y;
        pii nxt=f(u,t,a);
        res+=nxt.fi;y=nxt.se;
    }
    return {res,{x,y}};
}

void cal_query(){
    range[0]=Range[0][0]={0,-1};
    dfs(1,0);
    for(int j=1;j<18;j++){
        for(int i=0;i<=n;i++){
            Range[i][j].fi=max(Range[i][j-1].fi,Range[par[i][j-1]][j-1].fi);
            Range[i][j].se=min(Range[i][j-1].se,Range[par[i][j-1]][j-1].se);
            sx[i][j]=sx[i][j-1]+sx[par[i][j-1]][j-1];
        }
    }
    for(int i=1;i<=n;i++){
        int x=range[i].fi,p=i;
        for(int j=17;j>=0;j--){
            if(Range[p][j].fi<=x && x<=Range[p][j].se) p=par[p][j];
        }
        cost[i][0][0].se.fi=p;
        if(x<range[p].fi){
            cost[i][0][0].se.se=0;
            cost[i][0][0].fi=range[p].fi-x;
        }
        else{
            cost[i][0][0].se.se=1;
            cost[i][0][0].fi=x-range[p].se;
        }

        x=range[i].se;p=i;
        for(int j=17;j>=0;j--){
            if(Range[p][j].fi<=x && x<=Range[p][j].se) p=par[p][j];
        }
        cost[i][1][0].se.fi=p;
        if(x<range[p].fi){
            cost[i][1][0].se.se=0;
            cost[i][1][0].fi=range[p].fi-x;
        }
        else{
            cost[i][1][0].se.se=1;
            cost[i][1][0].fi=x-range[p].se;
        }
    }
    for(int j=1;j<18;j++){
        for(int i=1;i<=n;i++){
            piii c0=cost[i][0][j-1],c1=cost[i][1][j-1];
            cost[i][0][j]=cost[c0.se.fi][c0.se.se][j-1];
            cost[i][0][j].fi+=c0.fi;
            cost[i][1][j]=cost[c1.se.fi][c1.se.se][j-1];
            cost[i][1][j].fi+=c1.fi;
        }
    }
    for(int i=1;i<=q;i++){
        //cout << pa[i] << ' ' << pb[i] << '\n';
        assert(pa[i] && pb[i]);
        int anc=lca(pa[i],pb[i]);
        //cout << anc << '\n';
        piii u=jmp(xa[i],ya[i],pa[i],anc);
        piii v=jmp(xb[i],yb[i],pb[i],anc);
        //cout << u.fi << ' ' << u.se.fi << ' ' << u.se.se << ' ' << v.fi << ' ' << v.se.fi << ' ' << v.se.se << '\n';
        cout << u.fi+v.fi+abs(u.se.fi-v.se.fi)+abs(u.se.se-v.se.se) << '\n';
    }
}

//Transform the castle to a tree
map<int,vector<pii>> mp;
map<int,int> cur;

void solve(){
    cin >> n;
    vector<pii> p(n);
    for(int i=0;i<n;i++) cin >> p[i].fi >> p[i].se;
    for(int i=0;i<n;i++){
        if(p[i].fi==p[(i+1)%n].fi){
            int l=min(p[i].se,p[(i+1)%n].se);
            int r=max(p[i].se,p[(i+1)%n].se);
            mp[p[i].fi].push_back({l,r});
        }
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        cin >> xa[i] >> ya[i] >> xb[i] >> yb[i];
        mp[xa[i]].push_back({ya[i],-i*2});
        mp[xb[i]].push_back({yb[i],-i*2-1});
    }
    for(auto &[X,cc]:mp){
        set<int> s;
        vector<int> pos;
        //cout << '*' << X << '\n';
        for(pii x:cc){
            if(x.se<0){
                x.se=-x.se;
                auto it=cur.lower_bound(x.fi);
                if(it==cur.end()) continue;
                if(range[it->se].fi==it->fi && it->fi!=x.fi) continue;
                if(x.se&1) pb[x.se/2]=it->se;
                else pa[x.se/2]=it->se;
                continue;
            }
            //cout << x.fi << ' ' << x.se << '\n';
            auto fit=cur.find(x.fi),sit=cur.find(x.se);
            if(fit==cur.end()) s.insert(x.fi);
            else{
                pos.push_back(x.fi);
                s.insert(range[fit->se].fi);
                s.insert(range[fit->se].se);
            }

            if(sit==cur.end()) s.insert(x.se);
            else{
                pos.push_back(x.se);
                s.insert(range[sit->se].fi);
                s.insert(range[sit->se].se);
            }

            if(fit==cur.end() && sit==cur.end()){
                auto it=cur.lower_bound(x.fi);
                if(it!=cur.end() && range[it->se].se==it->fi){
                    s.insert(range[it->se].fi);
                    s.insert(range[it->se].se);
                }
            }
        }
        for(int x:pos) s.erase(x);
        auto add = [&](int l,int r){
            range[++cnt]={l,r};
            auto it=cur.lower_bound(l);
            int pre=-1;
            while(it!=cur.end() && range[it->se].fi<=r){
                int v=it->se;
                if(v!=pre){
                    edge[cnt].push_back({v,X});
                    edge[v].push_back({cnt,X});
                }
                pre=v;it++;
            }
        };
        auto del = [&](int id){
            while(true){
                auto it=cur.lower_bound(range[id].fi);
                if(it==cur.end() || range[it->se].fi>range[id].se) break;
                int v=it->se;
                cur.erase(range[v].fi);
                cur.erase(range[v].se);
            }
            cur[range[id].fi]=id;
            cur[range[id].se]=id;
        };
        int pre=-1,pre_cnt=cnt;
        for(int x:s){
            if(pre!=-1){
                add(pre,x);
                pre=-1;
            }
            else pre=x;
        }
        for(int i=pre_cnt+1;i<=cnt;i++) del(i);
        for(int x:pos) cur.erase(x);
        //cout << "cur\n";
        //for(pii x:cur) cout << x.fi << ' ';
        //cout << '\n';
        for(pii x:cc){
            if(x.se>=0) continue;
            x.se=-x.se;
            auto it=cur.lower_bound(x.fi);
            if(it==cur.end()) continue;
            if(range[it->se].fi==it->fi && it->fi!=x.fi) continue;
            if(x.se&1) pb[x.se/2]=it->se;
            else pa[x.se/2]=it->se;
        }
    }
    /*
    for(int i=1;i<=cnt;i++){
        cout << range[i].fi << ' ' << range[i].se << '\n';
    }
    */
    cal_query();
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
/*
12
4 2
6 2
6 3
7 3
7 2
9 2
9 3
8 3
8 4
5 4
5 3
4 3
0
*/
