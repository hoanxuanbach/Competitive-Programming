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
const int maxn=100015;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
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
const int base=101;

int sx,sy;
vector<int> cx,cy;
vector<int> qq[2*maxn];
int cc[2*maxn];

namespace DSU{
    int cnt,par[maxn];
    void init(int n){
        cnt=n;
        for(int i=1;i<=n;i++) par[i]=i;
    }
    int findpar(int u){
        if(u!=par[u]) return par[u]=findpar(par[u]);
        return u;
    }
    void unions(int u,int v){
        if(!u || !v) return;
        u=findpar(u);v=findpar(v);
        if(u==v) return;
        par[v]=u;cnt--;
    }
};
namespace BIT{
    int bit[2*maxn],sz;
    void init(int n){
        sz=n;
        for(int i=1;i<=n;i++) bit[i]=0;
    }
    void update(int x,int val){
        for(int i=x;i<=sz;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}

namespace Segtree{
    int tree[8*maxn],lazy[8*maxn];
    void pushdown(int id){
        if(!lazy[id]) return;
        if(tree[id<<1]>=1){
            tree[id<<1]=lazy[id<<1]=lazy[id];
        }
        if(tree[id<<1|1]>=1){
            tree[id<<1|1]=lazy[id<<1|1]=lazy[id];
        }
        lazy[id]=0;
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr && tree[id]!=-1){
            DSU::unions(val,tree[id]);
            if(tree[id]>=1) tree[id]=lazy[id]=val;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        int a=tree[id<<1],b=tree[id<<1|1];
        if(a>b) swap(a,b);
        if(a>0){
            if(a==b) tree[id]=a;
            else tree[id]=-1;
        }
        else if(a==0) tree[id]=b;
        else tree[id]=-1;
    }
    void update_pos(int l,int r,int id,int p,int val){
        if(l==r){
            tree[id]=val;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(p<=mid) update_pos(l,mid,id<<1,p,val);
        else update_pos(mid+1,r,id<<1|1,p,val);
        int a=tree[id<<1],b=tree[id<<1|1];
        if(a>b) swap(a,b);
        if(a>0){
            if(a==b) tree[id]=a;
            else tree[id]=-1;
        }
        else if(a==0) tree[id]=b;
        else tree[id]=-1;
    }

}

int H,W,N,n;
struct line{
    int x,y,u,v;
}l[maxn];

void solve(){
    cin >> H >> W >> N;
    for(int i=1;i<=N;i++){
        int x,y,u,v;cin >> x >> y >> u >> v;
        if(x!=u || y!=v) l[++n]={x,y,u,v};
    }
    l[++n]={0,0,H,0};
    l[++n]={0,0,0,W};
    l[++n]={H,0,H,W};
    l[++n]={0,W,H,W};

    for(int i=1;i<=n;i++){
        cx.push_back(l[i].x);
        cx.push_back(l[i].u+1);
        cy.push_back(l[i].y);
        cy.push_back(l[i].v+1);
    }
    sort(cx.begin(),cx.end());
    sort(cy.begin(),cy.end());
    cx.erase(unique(cx.begin(),cx.end()),cx.end());
    cy.erase(unique(cy.begin(),cy.end()),cy.end());
    sx=(int)cx.size();sy=(int)cy.size();

    int ans=0;
    for(int i=1;i<=n;i++){
        l[i].x=lower_bound(cx.begin(),cx.end(),l[i].x)-cx.begin()+1;
        l[i].u=lower_bound(cx.begin(),cx.end(),l[i].u+1)-cx.begin();
        l[i].y=lower_bound(cy.begin(),cy.end(),l[i].y)-cy.begin()+1;
        l[i].v=lower_bound(cy.begin(),cy.end(),l[i].v+1)-cy.begin();

        if(l[i].x==l[i].u) qq[l[i].x].push_back(i);
        else{
            ans--;
            //cout << '*' << i << '\n';
            qq[l[i].x].push_back(i);
            qq[l[i].u+1].push_back(-i);
        }
    }
    //cout << ans << '\n';
    DSU::init(n);
    BIT::init(sy);
    for(int i=1;i<=sx;i++){
        sort(qq[i].begin(),qq[i].end());
        for(int id:qq[i]){
            int t=abs(id);
            if(l[t].x!=l[t].u){
                cc[l[t].y]^=1;
                //cout << "change " << id << '\n';
                if(id>0) Segtree::update_pos(1,sy,1,l[t].y,t);
                else Segtree::update_pos(1,sy,1,l[t].y,0);
                BIT::update(l[t].y,(id<0?-1:1));
            }
        }
        for(int id:qq[i]){
            int t=abs(id);
            if(l[t].x==l[t].u){
                //cout << '*' << t << '\n';
                Segtree::update(1,sy,1,l[t].y,l[t].v,t);
                ans+=BIT::query(l[t].v-1)-BIT::query(l[t].y)+1;
                //cout << t << ' ' << BIT::query(l[t].v-1)-BIT::query(l[t].y) << '\n';
                if(!cc[l[t].v]){
                    ans--;
                    //cout << "stupid\n";
                }
                if(!cc[l[t].y]){
                    ans--;
                    //cout << "stupid\n";
                }
            }
        }
    }
    //cout << ans << '\n';
    //cout << DSU::cnt << '\n';
    ans+=DSU::cnt;
    cout << ans << '\n';
}

signed main(){
    //freopen("5.in","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
