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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int mod=998244353;
const int maxn=125000;
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

vector<int> cy2;
set<int> ss[maxn];

vector<int> cx,cy;

int pre,nw;

struct ST{
    int n;
    vector<pii> t;
    void build(int N) {  // build the tree
        n=N;t.resize(2*n);
        for(int i=1;i<=n;i++) t[i+n-1]={inf,i};
        for(int i=n-1;i>0;i--) t[i]=max(t[i<<1],t[i<<1|1]);
    }

    void update(int p){  // set value at position p
        for(t[p+=n-1]={nw,p};p>1;p>>=1) t[p>>1]=max(t[p],t[p^1]);
    }

    int query(int val){
        if(t[1].fi>val) return t[1].se;
        else return 0;
    }
};
vector<int> num[2*maxn];
namespace Segtree{
    ST tree[2*maxn];
    int Max[8*maxn],lazy[8*maxn],Min[8*maxn];
    pii ret[8*maxn];

    void reset(int n){
        for(int i=1;i<=n;i++) num[i].clear();
        for(int i=1;i<4*n;i++){
            Max[i]=Min[i]=lazy[i]=0;
            ret[i]={0,0};
        }
    }
    void build(int l,int r,int id){
        //cout << ret[id] << '\n';
        if(l==r){
            sort(num[l].begin(),num[l].end());
            num[l].erase(unique(num[l].begin(),num[l].end()),num[l].end());
            while(!num[l].empty() && (int)num[l].size()<num[l].back()-cy[l-1]+1) num[l].pop_back();
            num[l].shrink_to_fit();
            if((int)num[l].size()<cy[l]-cy[l-1]) ret[id]={inf,cy[l-1]+(int)num[l].size()};
            else{
                tree[l].build((int)num[l].size());
                ret[id]={tree[l].t[1].fi,tree[l].t[1].se+cy[l-1]-1};
            }
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        ret[id]=max(ret[id<<1],ret[id<<1|1]);
    }

    void update_pos(int l,int r,int id,int p,int val){
        //cout << "update_pos " << l << ' ' << r << ' ' << id << ' ' << p << ' ' << val << ' ' << d << ' ' << ret[id] << endl;
        if(l==r){
            if((int)num[l].size()==cy[l]-cy[l-1]){
                tree[l].update(val-cy[l-1]+1);
                ret[id]={tree[l].t[1].fi,tree[l].t[1].se+cy[l-1]-1};
            }
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update_pos(l,mid,id<<1,p,val);
        else update_pos(mid+1,r,id<<1|1,p,val);
        ret[id]=max(ret[id<<1],ret[id<<1|1]);
    }

    void getnew(int id,int val){
        Max[id]+=val;
        Min[id]+=val;
        lazy[id]+=val;
    }
    void pushdown(int id){
        if(lazy[id]==0) return;
        getnew(id<<1,lazy[id]);
        getnew(id<<1|1,lazy[id]);
        lazy[id]=0;
    }
    pii query(int l,int r,int id,int tl,int tr,int val){
        //cout << "query " << l << ' ' << r << ' ' << id << ' ' << tl << ' ' << tr << ' ' << val << ' ' << Max[id] << '\n';
        if(tr<l || r<tl || Min[id]>0) return {0,0};
        if(tl<=l && r<=tr && Max[id]==0) return ret[id];
        if(l==r) return {0,0};
        pushdown(id);
        int mid=(l+r)>>1;
        pii x=query(l,mid,id<<1,tl,tr,val);
        if(x.fi<val) return query(mid+1,r,id<<1|1,tl,tr,val);
        else return x;
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,val);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        Max[id]=max(Max[id<<1],Max[id<<1|1]);
        Min[id]=min(Min[id<<1],Min[id<<1|1]);
    }
}

int n;
pii ans[maxn];
pair<pii,pii> p[maxn];
vector<int> query[maxn],add[maxn];

void cal(int t){
    cx.clear();cy.clear();
    cy.push_back(1);
    for(int i=1;i<=n;i++){
        //cout << i << ' ' << p[i].fi.fi << ' ' << p[i].fi.se << ' ' << p[i].se.fi << ' ' << p[i].se.se << endl;
        if(p[i].fi.fi==p[i].se.fi){
            cx.push_back(p[i].fi.fi);
            cy.push_back(p[i].fi.se);
            cy.push_back(p[i].se.se+1);
        }
        else cy2.push_back(p[i].fi.se);
        //if(p[i].fi.fi==0) cout << i << endl;
        query[i].clear();add[i].clear();ss[i].clear();
    }
    sort(cx.begin(),cx.end());
    sort(cy.begin(),cy.end());
    sort(cy2.begin(),cy2.end());
    cx.erase(unique(cx.begin(),cx.end()),cx.end());
    cy.erase(unique(cy.begin(),cy.end()),cy.end());
    cy2.erase(unique(cy2.begin(),cy2.end()),cy2.end());
    int sz=(int)cy.size()-1;
    if(sz<=0) return;
    Segtree::reset(sz);
    //cout << "###############" << t << endl;
    //for(int a:cx) cout << a << ' ';
    //cout << '\n';
    //for(int a:cy) cout << a << ' ';
    //cout << '\n';
    for(int i=1;i<=n;i++){
        if(p[i].fi.fi==p[i].se.fi){
            int pos=lower_bound(cx.begin(),cx.end(),p[i].fi.fi)-cx.begin()+1;
            query[pos].push_back(i);
        }
        else{
            int pos=lower_bound(cx.begin(),cx.end(),p[i].fi.fi)-cx.begin()+1;
            add[pos].push_back(i);
            pos=lower_bound(cx.begin(),cx.end(),p[i].se.fi+1)-cx.begin()+1;
            add[pos].push_back(-i);

            pos=upper_bound(cy.begin(),cy.end(),p[i].fi.se)-cy.begin();
            //cout << pos << ' ' << p[i].fi.se << '\n';
            num[pos].push_back(p[i].fi.se);
        }
    }
    Segtree::build(1,sz,1);
    for(int i=1;i<=(int)cx.size();i++){
        for(int x:add[i]){
            int pos=upper_bound(cy.begin(),cy.end(),p[abs(x)].fi.se)-cy.begin();
            int pos2=lower_bound(cy2.begin(),cy2.end(),p[abs(x)].fi.se)-cy2.begin()+1;

            pre = ss[pos2].empty()?inf:*ss[pos2].begin();
            if(x<0) ss[pos2].erase(-x);
            else ss[pos2].insert(x);
            nw = ss[pos2].empty()?inf:*ss[pos2].begin();

            if(nw!=pre && pos<=sz) Segtree::update_pos(1,sz,1,pos,p[abs(x)].fi.se);
        }
        for(int x:query[i]){
            int px=lower_bound(cy.begin(),cy.end(),p[x].fi.se)-cy.begin()+1;
            int py=upper_bound(cy.begin(),cy.end(),p[x].se.se)-cy.begin();
            pii d=Segtree::query(1,sz,1,px,py,x);
            Segtree::update(1,sz,1,px,py,1);
            //cout << '*' << i << ' ' << x << ' ' << px << ' ' << py << ' ' << d << '\n';
            if(d.fi>x) ans[x]={p[x].fi.fi,d.se};
            if(t) swap(ans[x].fi,ans[x].se);
        }
        for(int x:query[i]){
            int px=lower_bound(cy.begin(),cy.end(),p[x].fi.se)-cy.begin()+1;
            int py=upper_bound(cy.begin(),cy.end(),p[x].se.se)-cy.begin();
            Segtree::update(1,sz,1,px,py,-1);
        }
    }
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> p[i].fi.fi >> p[i].fi.se >> p[i].se.fi >> p[i].se.se;
        if(p[i].fi.fi>p[i].se.fi) swap(p[i].fi.fi,p[i].se.fi);
        if(p[i].fi.se>p[i].se.se) swap(p[i].fi.se,p[i].se.se);
    }
    for(int t=0;t<2;t++){
        cal(t);
        for(int i=1;i<=n;i++){
            swap(p[i].fi.fi,p[i].fi.se);
            swap(p[i].se.fi,p[i].se.se);
        }
    }
    bool check=true;
    for(int i=1;i<=n;i++){
        //cout << ans[i].fi << ' ' << ans[i].se << '\n';
        if(ans[i]==mpp(0,0)) check=false;
    }
    if(!check) cout << 0 << '\n';
    else{
        cout << n << '\n';
        for(int i=1;i<=n;i++) cout << ans[i].fi << ' ' << ans[i].se << '\n';
    }
}

signed main(){
    //freopen("FLASHMOB.INP","r",stdin);
    //freopen("FLASHMOB.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
