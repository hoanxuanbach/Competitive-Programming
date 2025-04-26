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
const int maxn=500005;
const int B=650;
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

struct line{
    int a,b,p;
    bool operator<(line l){return a>l.a;}
    bool operator<(int k){return p<k;}
};
struct cvht{
    int k=0;
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
        if(x.empty()) return inf;
        while(k<(int)x.size() && v>x[k].p) k++;
        return v*x[k].a+x[k].b;
    }
}cht[4*maxn];

int n,p[maxn],x[maxn],c[maxn];
vector<int> edge[maxn],del[maxn];
int L[maxn],R[maxn],T,pos[maxn];
int m,res[maxn],S[maxn],X[maxn];

void dfs(int u){
    L[u]=++T;
    for(int v:edge[u]) dfs(v);
    R[u]=T;
    //cout << u << ' ' << L[u] << ' ' << R[u] << '\n';
}

void update(int l,int r,int id,int tl,int tr,int i){
    //if(id==1) cout << tl << ' ' << tr << ' ' << i << '\n';
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        cht[id].add({-2*x[i],x[i]*x[i]+c[i],inf});
        return;
    }
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,i);update(mid+1,r,id<<1|1,tl,tr,i);
}
int query(int l,int r,int id,int p,int val){
    int res=val*val+cht[id].query(val);
    if(l==r) return res;
    int mid=(l+r)>>1;
    if(p<=mid) res=min(res,query(l,mid,id<<1,p,val));
    else res=min(res,query(mid+1,r,id<<1|1,p,val));
    return res;
}

void solve(){
    cin >> n >> m >> c[0];
    for(int i=1;i<n;i++){
        int op,fr;cin >> op >> fr;
        edge[fr].push_back(i);
        //cout << "*" << fr << ' ' << i << '\n';
        if(!op){
            cin >> p[i] >> x[i] >> fr >> fr >> c[i];
            pos[p[i]]=i;
        }
        else{
            cin >> p[i],c[i]=-1;
            del[pos[p[i]]].push_back(i);
        }
    }
    dfs(0);
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[](int a,int b){
        return x[a]<x[b];
    });
    for(int i:ord){
        if(c[i]==-1) continue;
        sort(del[i].begin(),del[i].end(),[](int a,int b){
            return L[a]<L[b];
        });
        int l=L[i];
        for(int j:del[i]){
            if(l<L[j]) update(1,n,1,l,L[j]-1,i);
            l=R[j]+1;
        }
        if(l<=R[i]) update(1,n,1,l,R[i],i);
    }
    for(int i=1;i<=m;i++) cin >> S[i] >> X[i];
    ord.assign(m,0);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[](int a,int b){
        return X[a]<X[b];
    });
    for(int i:ord) res[i]=query(1,n,1,L[S[i]],X[i]);
    for(int i=1;i<=m;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
