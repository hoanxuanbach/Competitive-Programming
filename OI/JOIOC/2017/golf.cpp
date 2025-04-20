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
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=131;

struct Rec{
    int x,y,u,v;
}rec[maxn];

int sx,sy,tx,ty,n;
vector<int> cx,cy;

vector<piii> cur;
queue<pair<Rec,int>> q;

struct Segtree{
    set<piii> ss[4*maxn];
    void update(int l,int r,int id,int tl,int tr,int x){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            if(x<0) ss[id].erase({-x,{tl,tr}});
            else ss[id].insert({x,{tl,tr}});
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,x);update(mid+1,r,id<<1|1,tl,tr,x);
    }
    void query(int l,int r,int id,int p,int tl,int tr){
        auto it=ss[id].lower_bound(mpp(tl,mpp(0,0)));
        while(it!=ss[id].end() && it->fi<=tr){
            cur.push_back(*it);
            it=ss[id].erase(it);
        }
        if(l==r) return;
        int mid=(l+r)>>1;
        if(p<=mid) query(l,mid,id<<1,p,tl,tr);
        else query(mid+1,r,id<<1|1,p,tl,tr);
    }
}Tx,Ty;

vector<pii> p[maxn];

void solve(){
    cin >> sx >> sy >> tx >> ty;
    cx.push_back(sx);cx.push_back(tx);
    cy.push_back(sy);cy.push_back(ty);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> rec[i].x >> rec[i].u >> rec[i].y >> rec[i].v;
        cx.push_back(rec[i].x);cx.push_back(rec[i].u);
        cy.push_back(rec[i].y);cy.push_back(rec[i].v);
    }
    sort(cx.begin(),cx.end());
    cx.erase(unique(cx.begin(),cx.end()),cx.end());
    sort(cy.begin(),cy.end());
    cy.erase(unique(cy.begin(),cy.end()),cy.end());


    auto get = [&](vector<int> &c,int x){
        return lower_bound(c.begin(),c.end(),x)-c.begin()+1;
    };

    sx=get(cx,sx);tx=get(cx,tx);
    sy=get(cy,sy);ty=get(cy,ty);
    //cout << sx << ' ' << sy << '\n';
    //cout << tx << ' ' << ty << '\n';
    for(int i=1;i<=n;i++){
        rec[i].x=get(cx,rec[i].x);
        rec[i].y=get(cy,rec[i].y);
        rec[i].u=get(cx,rec[i].u);
        rec[i].v=get(cy,rec[i].v);
        //cout << rec[i].x << ' ' << rec[i].y << ' ' << rec[i].u << ' ' << rec[i].v << '\n';
    }
    //cout << '\n';
    {
        p[sx].push_back({sy,0});
        p[tx].push_back({ty,0});
        for(int i=1;i<=n;i++){
            auto [x,y,u,v]=rec[i];
            p[x].push_back({y,0});
            p[u].push_back({y,0});

            p[x+1].push_back({y,i});
            p[u].push_back({y,-i});
            p[x+1].push_back({v,i});
            p[u].push_back({v,-i});
        }

        set<pii> s;
        for(int i=1;i<=(int)cx.size();i++){
            for(auto [y,id]:p[i]){
                if(!id) continue;
                if(id>0) s.insert({y,id});
                else s.erase({y,-id});
            }
            for(auto [y,id]:p[i]){
                if(id) continue;
                int l=1,r=(int)cy.size();
                auto it=s.lower_bound(mpp(y,0));
                if(it!=s.end()) r=it->fi;
                if(it!=s.begin()){
                    it--;
                    l=it->fi;
                }
                //cout << i << ' ' << l << ' ' << i <<  ' ' << r << '\n';
                if(i==sx && l<=sy && sy<=r) q.push({{i,l,i,r},1});
                else Ty.update(1,(int)cy.size(),1,l,r,i);
            }
        }
    }

    {
        for(int i=1;i<=(int)cy.size();i++) p[i].clear();
        p[sy].push_back({sx,0});
        p[ty].push_back({tx,0});
        for(int i=1;i<=n;i++){
            auto [x,y,u,v]=rec[i];
            p[y].push_back({x,0});
            p[v].push_back({x,0});

            p[y+1].push_back({x,i});
            p[v].push_back({x,-i});
            p[y+1].push_back({u,i});
            p[v].push_back({u,-i});
        }

        set<pii> s;
        for(int i=1;i<=(int)cy.size();i++){
            for(auto [x,id]:p[i]){
                if(!id) continue;
                if(id>0) s.insert({x,id});
                else s.erase({x,-id});
            }
            for(auto [x,id]:p[i]){
                if(id) continue;
                int l=1,r=(int)cx.size();
                auto it=s.lower_bound(mpp(x,0));
                if(it!=s.end()) r=it->fi;
                if(it!=s.begin()){
                    it--;
                    l=it->fi;
                }
                //cout << l << ' ' << i << ' ' << r <<  ' ' << i << '\n';
                if(l<=sx && sx<=r && i==sy) q.push({{l,i,r,i},1});
                else Tx.update(1,(int)cx.size(),1,l,r,i);
            }
        }
    }

    while(!q.empty()){
        auto [c,d]=q.front();q.pop();
        //cout << "* " << c.x << ' ' << c.y << ' ' << c.u << ' ' << c.v << ' ' << d << '\n';
        if(c.x<=tx && c.y<=ty && tx<=c.u && ty<=c.v){
            cout << d << '\n';
            return;
        }
        cur.clear();
        if(c.x==c.u){
            Tx.query(1,(int)cx.size(),1,c.x,c.y,c.v);
            for(auto cc:cur){
                Tx.update(1,(int)cx.size(),1,cc.se.fi,cc.se.se,-cc.fi);
                q.push({{cc.se.fi,cc.fi,cc.se.se,cc.fi},d+1});
            }
        }
        else{
            Ty.query(1,(int)cy.size(),1,c.y,c.x,c.u);
            for(auto cc:cur){
                Ty.update(1,(int)cy.size(),1,cc.se.fi,cc.se.se,-cc.fi);
                q.push({{cc.fi,cc.se.fi,cc.fi,cc.se.se},d+1});
            }
        }
    }
    cout << -1 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
