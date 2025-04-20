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
#define ll long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf = 1e9;
const int mod=998244353;
const int maxn=4005;
const int B=650;
const int maxs=100005;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};

int n,X,Y,U,V;

int sx,sy;
vector<int> cx,cy;
struct rec{
    int x,y,u,v;
}R[maxn];
int a[maxn][maxn],f[maxn][maxn],cnt;
vector<int> edge[maxs];
pii pos[maxs];

void solve(){
    cin >> X >> Y >> U >> V >> n;

    cnt=0;
    cx.clear();
    cy.clear();

    cx.push_back(X);
    cx.push_back(X+1);
    cx.push_back(U);
    cx.push_back(U+1);
    cy.push_back(Y);
    cy.push_back(Y+1);
    cy.push_back(V);
    cy.push_back(V+1);

    for(int i=1;i<=n;i++){
        int x,y,u,v;cin >> x >> y >> u >> v;
        if(x>u) swap(x,u);
        if(y>v) swap(y,v);
        cx.push_back(x);
        cx.push_back(x+1);
        cx.push_back(u);
        cx.push_back(u+1);
        cy.push_back(y);
        cy.push_back(y+1);
        cy.push_back(v);
        cy.push_back(v+1);
        R[i]={x,y,u,v};
    }
    sort(cx.begin(),cx.end());
    sort(cy.begin(),cy.end());
    cx.erase(unique(cx.begin(),cx.end()),cx.end());
    cy.erase(unique(cy.begin(),cy.end()),cy.end());
    sx=(int)cx.size()-1;sy=(int)cy.size()-1;

    X=lower_bound(cx.begin(),cx.end(),X)-cx.begin();
    Y=lower_bound(cy.begin(),cy.end(),Y)-cy.begin();
    U=lower_bound(cx.begin(),cx.end(),U)-cx.begin();
    V=lower_bound(cy.begin(),cy.end(),V)-cy.begin();
    //cout << X << ' ' << Y << ' ' << U << ' ' << V << '\n';

    for(int i=0;i<sx;i++) for(int j=0;j<sy;j++){
        a[i][j]=f[i][j]=0;
    }

    auto add = [&](int x,int y,int u,int v,int val){
        a[x][y]+=val;a[x][v+1]-=val;
        a[u+1][y]-=val;a[u+1][v+1]+=val;
    };
    for(int i=1;i<=n;i++){
        int x=R[i].x,y=R[i].y,u=R[i].u,v=R[i].v;
        x=lower_bound(cx.begin(),cx.end(),x)-cx.begin();
        y=lower_bound(cy.begin(),cy.end(),y)-cy.begin();
        u=lower_bound(cx.begin(),cx.end(),u)-cx.begin();
        v=lower_bound(cy.begin(),cy.end(),v)-cy.begin();
        R[i]={x,y,u,v};
        add(x,y,u,v,i);
        add(x+1,y+1,u-1,v-1,-i);
    }
    for(int i=0;i<sx;i++) for(int j=0;j<sy;j++){
        if(i) a[i][j]+=a[i-1][j];
        if(j) a[i][j]+=a[i][j-1];
        if(i && j) a[i][j]-=a[i-1][j-1];
    }

    if(!a[X][Y]) a[X][Y]=n+1;
    if(!a[U][V]) a[U][V]=n+2;

    for(int i=0;i<sx;i++){
        int p=-1;
        for(int j=0;j<sy;j++){
            if(a[i][j]){
                f[i][j]=++cnt;
                pos[cnt]={i,j};
                edge[cnt].clear();
                //cout << "pos " << cnt << ' ' << i << ' ' << j << '\n';
            }
            if(!a[i][j]) continue;
            if(p==-1){p=j;continue;}
            int id=a[i][j];
            if(id!=a[i][p] || i==R[id].x || i==R[id].u){
                edge[f[i][j]].push_back(f[i][p]);
                //cout << "edge " << f[i][j] << ' ' << f[i][p] << '\n';
            }
            p=j;
        }
        p=-1;
        for(int j=sy-1;j>=0;j--){
            if(!a[i][j]) continue;
            if(p==-1){p=j;continue;}
            int id=a[i][j];
            if(id!=a[i][p] || i==R[id].x || i==R[id].u){
                edge[f[i][j]].push_back(f[i][p]);
                //cout << "edge " << f[i][j] << ' ' << f[i][p] << '\n';
            }
            p=j;
        }
    }
    for(int j=0;j<sy;j++){
        int p=-1;
        for(int i=0;i<sx;i++){
            if(!a[i][j]) continue;
            if(p==-1){p=i;continue;}
            int id=a[i][j];
            if(id!=a[p][j] || j==R[id].y || j==R[id].v) edge[f[i][j]].push_back(f[p][j]);
            p=i;
        }
        p=-1;
        for(int i=sx-1;i>=0;i--){
            if(!a[i][j]) continue;
            if(p==-1){p=i;continue;}
            int id=a[i][j];
            if(id!=a[p][j] || j==R[id].y || j==R[id].v) edge[f[i][j]].push_back(f[p][j]);
            p=i;
        }
    }

    assert(cnt<=100000);
    for(int i=0;i<sx;i++) for(int j=0;j<sy;j++) a[i][j]=inf;

    a[X][Y]=0;
    X=f[X][Y];U=f[U][V];
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    pq.push({0,X});
    while(!pq.empty()){
        auto [d,u]=pq.top();pq.pop();
        auto [x,y]=pos[u];
        //cout << d << ' ' << u << ' ' << x << ' ' << y << '\n';
        if(u==U){
            cout << d << '\n';
            return;
        }
        if(a[x][y]!=d) continue;
        for(int v:edge[u]){
            auto [xv,yv]=pos[v];
            int dv=d+abs(cx[xv]-cx[x])+abs(cy[yv]-cy[y]);
            //cout << "edge " << u << ' ' << v << '\n';
            if(a[xv][yv]>dv){
                pq.push({a[xv][yv]=dv,v});
            }
        }
    }
    cout << "No Path\n";

}


signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
