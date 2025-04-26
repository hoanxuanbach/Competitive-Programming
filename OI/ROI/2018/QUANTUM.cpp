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
- insert(x)
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
#define fi first
#define se second
const int inf=1e9;
const int mod=1e9+7;
const int maxn=10025;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=10000;
const int root=3;
const int base=101;

int n,m,k,pw[maxn],Max=10020;
vector<pii> edge[maxn];

struct node{
    int sum=0,h=0,p0=0;
    node *cl=nullptr,*cr=nullptr;
};
node *f0,*f1;
void pull(node *res){
    res->sum=res->cl->sum+res->cr->sum;
    res->h=(res->cl->h+1LL*pw[res->cl->sum]*res->cr->h%mod)%mod;
    res->p0=(res->cl->p0?res->cl->p0:(res->cr->p0?res->cl->sum+res->cr->p0:0));
}
int cmp(node *t1,node *t2,int l=0,int r=Max){
    if(l==r) return t1->h-t2->h;
    int mid=(l+r)>>1;
    if(t1->cr->h==t2->cr->h) return cmp(t1->cl,t2->cl,l,mid);
    else return cmp(t1->cr,t2->cr,mid+1,r);
}
void build(node *t,int val,int l=0,int r=Max){
    if(l==r){
        t->sum=1,t->h=val,t->p0=!val;
        return;
    }
    int mid=(l+r)>>1;
    t->cl=new node();t->cr=new node();
    build(t->cl,val,l,mid);build(t->cr,val,mid+1,r);
    pull(t);
}
int query0(node *t,int p,int l=0,int r=Max){
    if(l==r) return (t->p0?p:-1);
    int mid=(l+r)>>1;
    if(p<=mid){
        int p0=query0(t->cl,p,l,mid);
        return (p0>=0?p0:(t->cr->p0?mid+t->cr->p0:-1));
    }
    else return query0(t->cr,p,mid+1,r);
}
node* update(node *t,int tl,int tr,node *c,int l=0,int r=Max){
    if(tr<l || r<tl) return t;
    if(tl<=l && r<=tr) return c;
    int mid=(l+r)>>1;
    node *res=new node();
    res->cl=update(t->cl,tl,tr,c->cl,l,mid);
    res->cr=update(t->cr,tl,tr,c->cr,mid+1,r);
    pull(res);
    return res;
}
struct ds{
    int u;node *d;
    friend bool operator<(ds a,ds b){
        int x=cmp(a.d,b.d);
        return (x?x>0:a.u>b.u);
    }
};
node *dist[maxn];
int trace[maxn],check[maxn];

int dx[]={-1,-1,1,1},
    dy[]={-1,1,-1,1};

int x[maxn],y[maxn],dd[maxn][4];
vector<pii> xx[maxn],yy[maxn];
set<pii> sx[maxn],sy[maxn];

void the_classic_problem(){
    int s=1,t=k;
    f0=new node();f1=new node();
    build(f0,0);build(f1,1);
    for(int i=1;i<=k;i++) dist[i]=f1;
    priority_queue<ds> pq;
    dist[s]=f0;pq.push({s,f0});

    while(!pq.empty()){
        auto [u,d]=pq.top();pq.pop();
        //cout << u << endl;
        if(u>k){
            int t=(u+3-k)%4;u=(u+3-k)/4;
            int xl=x[u]+dx[t],yl=y[u]+dy[t],xt=x[u]+dx[t]*dd[u][t],yt=y[u]+dy[t]*dd[u][t];
            if(xt>0 && xt<=maxa){
                auto it=sx[xt].lower_bound({min(yl,yt),0});
                while(it!=sx[xt].end()){
                    if(it->fi>max(yl,yt)) break;
                    if(!check[it->se]){
                        check[it->se]=1;
                        trace[it->se]=u;
                        dist[it->se]=d;
                        pq.push({it->se,d});
                    }
                    it=sx[xt].erase(it);
                }
            }
            if(yt>0 && yt<=maxa){
                auto it=sy[yt].lower_bound({min(xl,xt),0});
                while(it!=sy[yt].end()){
                    if(it->fi>max(xl,xt)) break;
                    if(!check[it->se]){
                        check[it->se]=1;
                        trace[it->se]=u;
                        dist[it->se]=d;
                        pq.push({it->se,d});
                    }
                    it=sy[yt].erase(it);
                }
            }
        }
        else{
            if(check[u]==2) continue;
            check[u]=2;
            if(u==t){
                vector<int> path;
                while(u) path.push_back(u),u=trace[u];
                cout << (int)path.size() << '\n';
                while(!path.empty()){cout << path.back() << ' ';path.pop_back();}
                return;
            }
            for(auto [v,w]:edge[u]){
                int pos=query0(d,w);
                node *nd=update(d,pos,pos,f1);
                if(w<pos) nd=update(nd,w,pos-1,f0);
                if(v<=k){
                    if(!check[v] && cmp(nd,dist[v])<0){
                        dist[v]=nd;trace[v]=u;
                        pq.push({v,nd});
                    }
                }
                else pq.push({v,nd});
            }
        }
    }
}

void solve(){
    pw[0]=1;
    for(int i=1;i<=Max;i++) pw[i]=pw[i-1]*2%mod;
    cin >> n >> m >> k;
    //int cnt=0;
    for(int i=1;i<=k;i++){
        cin >> x[i] >> y[i];
        xx[x[i]].push_back({y[i],i});
        yy[y[i]].push_back({x[i],i});
        sx[x[i]].insert({y[i],i});
        sy[y[i]].insert({x[i],i});
    }
    for(int i=1;i<=maxa;i++){
        sort(xx[i].begin(),xx[i].end());
        sort(yy[i].begin(),yy[i].end());
        for(int j=1;j<(int)xx[i].size();j++){
            edge[xx[i][j].se].push_back({xx[i][j-1].se,xx[i][j].fi-xx[i][j-1].fi});
            edge[xx[i][j-1].se].push_back({xx[i][j].se,xx[i][j].fi-xx[i][j-1].fi});
        }
        for(int j=1;j<(int)yy[i].size();j++){
            edge[yy[i][j].se].push_back({yy[i][j-1].se,yy[i][j].fi-yy[i][j-1].fi});
            edge[yy[i][j-1].se].push_back({yy[i][j].se,yy[i][j].fi-yy[i][j-1].fi});
        }
    }
    for(int i=1;i<=k;i++){
        for(int j=0;j<4;j++) dd[i][j]=inf;
        for(int j=1;j<=k;j++){
            if(j==i || x[i]==x[j] || y[i]==y[j]) continue;
            int t=((x[j]>x[i])<<1)|(y[j]>y[i]);
            dd[i][t]=min(dd[i][t],max(abs(x[i]-x[j]),abs(y[i]-y[j])));
        }
        for(int j=0;j<4;j++){
            if(dd[i][j]==inf) continue;
            //cout << i << ' ' << j << ' ' << dd[i][j] << endl;
            edge[i].push_back({k+i*4+j-3,dd[i][j]});
        }
    }
    the_classic_problem();
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
