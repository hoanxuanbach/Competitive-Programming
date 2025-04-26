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
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2")
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define ll long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int mod=998244353;
const int maxn=1000005;
const int B=650;
const int maxs=655;
const int maxm=100005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,m,t;
int L[maxn],R[maxn],num[maxn],T;
vector<int> edge[maxn];
vector<int> pos[maxn];
int X[maxm],Y[maxm];

void pre_dfs(int u){
    L[u]=++T;
    for(int v:edge[u]) pre_dfs(v);
    R[u]=T;num[u]=R[u]-L[u]+1;
}

int par[maxm],cnt;
long long total=0;
int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
bool unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return false;
    return cnt++,par[v]=u,true;
}

struct node{
    pii a={inf,-1},b={inf,-1};
    node(){};
    void add(pii x){
        if(x.fi<a.fi){
            if(x.se!=a.se) b=a;
            a=x;
        }
        else if(x.fi<b.fi && x.se!=a.se) b=x;
    }
};

void merge(node &res,node &a,node &b){
    res=a;
    res.add(b.a);
    res.add(b.b);
}

pii Min[maxm];
void Add(int id,int val,int cc){
    if(findpar(cc)!=findpar(id)) Min[id]=min(Min[id],{val,cc});
}

namespace S1{
    int C[maxn],S;
    void reset(){
        S=0;
        for(int i=0;i<=n;i++) C[i]=0;
    }
    void addnum(int x){
        C[x]=1;
    }
    void compress(){
        for(int i=1;i<=n;i++) C[i]+=C[i-1];
        S=C[n];
    }

    node res;
    node tree[4*maxm];
    void build(int l=1,int r=S,int id=1){
        tree[id]=node();
        if(l==r) return;
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    }
    void update(int l,int r,int id,int p,pii val){
        tree[id].add(val);
        if(l==r) return;
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,val);
        else update(mid+1,r,id<<1|1,p,val);
    }
    void update(int p,pii val){
        if(C[p]) update(1,S,1,C[p],val);
    }

    void query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr) return merge(res,res,tree[id]);
        int mid=(l+r)>>1;
        query(l,mid,id<<1,tl,tr);query(mid+1,r,id<<1|1,tl,tr);
    }
    node query(int l,int r){
        res=node();
        if(C[l-1]<C[r]) query(1,S,1,C[l-1]+1,C[r]);
        return res;
    }
}

namespace S2{
    int C[maxn],S;
    void reset(){
        S=0;
        for(int i=0;i<=n;i++) C[i]=0;
    }
    void addnum(int x){
        C[x]=1;
    }
    void compress(){
        for(int i=1;i<=n;i++) C[i]+=C[i-1];
        S=C[n];
    }

    node res;
    vector<node> tree[4*maxm],tree2[4*maxm];
    void build(int l=1,int r=S,int id=1){
        tree[id]=tree2[id]={node()};
        if(l==r) return;
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    }

    void update(int l,int r,int id,int p,pii val){
        if(val.se!=-1){
            tree[id].emplace_back(tree[id].back());
            tree[id].back().add(val);
        }
        else tree[id].pop_back();
        if(l==r) return;
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,val);
        else update(mid+1,r,id<<1|1,p,val);
    }
    void update(int p,pii val){
        if(C[p]) update(1,S,1,C[p],val);
    }

    void query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr) return merge(res,res,tree[id].back());
        int mid=(l+r)>>1;
        query(l,mid,id<<1,tl,tr);query(mid+1,r,id<<1|1,tl,tr);
    }
    node query(int l,int r){
        res=node();
        if(C[l-1]<C[r]) query(1,S,1,C[l-1]+1,C[r]);
        return res;
    }

    void update(int l,int r,int id,int tl,int tr,pii val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            if(val.se!=-1){
                tree2[id].emplace_back(tree2[id].back());
                tree2[id].back().add(val);
            }
            else tree2[id].pop_back();
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
    }
    void update(int l,int r,pii val){
        if(C[l-1]<C[r]) update(1,S,1,C[l-1]+1,C[r],val);
    }

    void query(int l,int r,int id,int p){
        merge(res,res,tree2[id].back());
        if(l==r) return;
        int mid=(l+r)>>1;
        if(p<=mid) return query(l,mid,id<<1,p);
        else return query(mid+1,r,id<<1|1,p);
    }
    node query(int p){
        res=node();
        if(C[p]) query(1,S,1,C[p]);
        return res;
    }
}

void dfs(int u,node cc){
    for(int id:pos[u]){
        int v=Y[id];
        cc.add({num[u]+num[v],findpar(id)});
        S2::update(L[v],{num[u]-num[v],findpar(id)});
        if(!t) S2::update(L[v],R[v],{num[u]+num[v],findpar(id)});
    }
    for(int id:pos[u]){
        int v=Y[id];
        Add(id,cc.a.fi-num[u]+num[v],cc.a.se);
        Add(id,cc.b.fi-num[u]+num[v],cc.b.se);

        node cur=S2::query(L[v],R[v]);
        Add(id,cur.a.fi-num[u]+num[v],cur.a.se);
        Add(id,cur.b.fi-num[u]+num[v],cur.b.se);

        if(!t){
            cur=S2::query(L[v]);
            Add(id,cur.a.fi-num[u]-num[v],cur.a.se);
            Add(id,cur.b.fi-num[u]-num[v],cur.b.se);
        }
    }
    for(int v:edge[u]) dfs(v,cc);
    for(int id:pos[u]){
        int v=Y[id];
        S2::update(L[v],{-1,-1});
        S1::update(L[u],{-num[u]+num[v],findpar(id)});
        if(!t) S2::update(L[v],R[v],{-1,-1});
    }
    node cur=S1::query(L[u],R[u]);
    for(int id:pos[u]){
        int v=Y[id];
        Add(id,cur.a.fi+num[u]+num[v],cur.a.se);
        Add(id,cur.b.fi+num[u]+num[v],cur.b.se);
    }
}

namespace S3{
    int C[maxn],S;
    void reset(){
        S=0;
        for(int i=0;i<=n;i++) C[i]=0;
    }
    void addnum(int x){
        C[x]=1;
    }
    void compress(){
        for(int i=1;i<=n;i++) C[i]+=C[i-1];
        S=C[n];
    }

    vector<int> query[4*maxm],val[4*maxm];
    void update(int l,int r,int id,int tl,int tr,int x){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            query[id].push_back(x);
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,x);update(mid+1,r,id<<1|1,tl,tr,x);
    }
    void update(int l,int r,int x){
        if(C[l-1]<C[r]) update(1,S,1,C[l-1]+1,C[r],x);
    }
    void add(int l,int r,int id,int p,int x){
        val[id].push_back(x);
        if(l==r) return;
        int mid=(l+r)>>1;
        if(p<=mid) add(l,mid,id<<1,p,x);
        else add(mid+1,r,id<<1|1,p,x);
    }
    void add(int p,int x){
        if(C[p]) add(1,S,1,C[p],x);
    }
    void build(){
        for(int i=1;i<=4*S;i++){
            if(val[i].empty()) continue;
            vector<pair<int,node>> cur;
            int j=0;
            for(int id:query[i]){
                while(j<(int)val[i].size() && L[Y[val[i][j]]]<=R[Y[id]]){
                    int p=val[i][j++];
                    node cc=node();
                    cc.add({-num[X[p]]-num[Y[p]],findpar(p)});
                    cur.push_back({L[Y[p]],cc});
                }
                while((int)cur.size()>=2 && cur.end()[-2].fi>=L[Y[id]]){
                    node cc=cur.back().se;cur.pop_back();
                    merge(cur.back().se,cur.back().se,cc);
                }
                node cc;
                if(!cur.empty() && cur.back().fi>=L[Y[id]]) cc=cur.back().se;
                else cc=node();
                int u=X[id],v=Y[id];
                Add(id,cc.a.fi+num[u]+num[v],cc.a.se);
                Add(id,cc.b.fi+num[u]+num[v],cc.b.se);
            }
        }
    }
}

void print(){
    for(int i=1;i<=m;i++){
        cout << i << ' ' << Min[i].fi << ' ' << Min[i].se << '\n';
    }
    cout << '\n';
}

void cal(){
    S1::reset();
    S2::reset();
    for(int i=1;i<=n;i++) pos[i].clear();
    for(int i=1;i<=m;i++){
        pos[X[i]].push_back(i);
        S1::addnum(L[X[i]]);
        S2::addnum(L[Y[i]]);
    }
    S1::compress();
    S2::compress();
    S1::build();
    S2::build();
    dfs(1,node());
    //print();
    if(!t){
        node cur=node();
        for(int i=1;i<=m;i++) cur.add({num[X[i]]+num[Y[i]],findpar(i)});
        for(int i=1;i<=m;i++){
            Add(i,num[X[i]]+num[Y[i]]+cur.a.fi,cur.a.se);
            Add(i,num[X[i]]+num[Y[i]]+cur.b.fi,cur.b.se);
        }
        //print();
        S3::build();
    }
    //print();
}

void solve(){
    cin >> n >> m;
    for(int i=2;i<=n;i++){
        int p;cin >> p;
        edge[p].push_back(i);
    }
    pre_dfs(1);
    for(int i=1;i<=m;i++){
        cin >> X[i] >> Y[i];
        par[i]=i;
    }

    for(int i=1;i<=m;i++) S3::addnum(L[X[i]]);
    S3::compress();
    vector<int> ord(m);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[](int a,int b){
        return L[Y[a]]<L[Y[b]];
    });
    for(int id:ord) S3::add(L[X[id]],id);
    sort(ord.begin(),ord.end(),[](int a,int b){
        if(R[Y[a]]!=R[Y[b]]) return R[Y[a]]<R[Y[b]];
        else return L[Y[a]]>L[Y[b]];
    });
    for(int id:ord) S3::update(L[X[id]],R[X[id]],id);

    while(cnt!=m-1){
        //cout << "********************************\n";
        for(int i=1;i<=m;i++) Min[i]={inf,-1};
        cal();t^=1;
        for(int i=1;i<=m;i++) swap(X[i],Y[i]);
        cal();t^=1;
        for(int i=1;i<=m;i++) swap(X[i],Y[i]);

        //print();
        for(int i=1;i<=m;i++){
            if(findpar(i)==i) continue;
            int p=findpar(i);
            Min[p]=min(Min[p],Min[i]);
        }
        for(int i=1;i<=m;i++){
            if(findpar(i)!=i) continue;
            if(unions(i,Min[i].se)){
                //cout << i << ' ' << add.se << ' ' << add.fi << '\n';
                total+=Min[i].fi;
            }
        }
    }
    cout << total << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
