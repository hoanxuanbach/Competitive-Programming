#include<bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
*/
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define i128 __int128
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
const int maxn=100005;
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

vector<int> inv={1,(mod+1)/2,(mod+1)/3};

struct node{
    int S=0;
    array<int,3> X={0,0,0};
    node(int x=-1){
        if(x!=-1) X[0]=x,S=1;
    }
    void add(int d){
        //cout << "add " << S << ' ' << X[0] << ' ' << X[1] << ' ' << X[2] << ' ' << d << '\n';
        auto f = [&](int x,int k){
            x=(x+mod)%mod;
            int res=inv[k];
            for(int i=0;i<=k;i++) res=res*d%mod*(x+mod-i)%mod;
            return res;
        };
        for(int i=2;i>=0;i--){
            for(int j=i;j>=0;j--) (X[i]+=(j?X[j-1]:1)*f(S-j,i-j))%=mod;
        }
        //cout << X[0] << ' ' << X[1] << ' ' << X[2] << '\n';
    }
    friend node operator+(node a,node b){
        node c;
        for(int i=0;i<=2;i++){
            (c.X[i]+=a.X[i]+b.X[i])%=mod;
            for(int j=0;j<=1-i;j++) (c.X[i+j+1]+=a.X[i]*b.X[j])%=mod;
        }
        c.S=(a.S+b.S)%mod;
        //cout << "sum " << a.S << ' ' << a.X[0] << ' ' << a.X[1] << ' ' << a.X[2] << ' ' << b.S << ' ' << b.X[0] << ' ' << b.X[1] << ' ' << b.X[2] << '\n';
        //cout << c.S << ' ' << c.X[0] << ' ' << c.X[1] << ' ' << c.X[2] << '\n';
        return c;
    }  
}tree[4*maxn];
int lazy[4*maxn];

int n,q;
node f[105][2];
vector<int> a;
vector<i128> pos;

node get_lt(i128 L,int k){
    if(k==-1) return f[0][0];
    int lb=(L>>k&1);
    node res=get_lt(L,k-1);
    if(!lb) res=res+f[k][1];
    else res.add(a[k]);
    //cout << "get_lt " << (int)L << ' ' << k << ' ' << res.S << ' ' << res.X[0] << ' ' << res.X[1] << ' ' << res.X[2] << '\n';
    return res;
}
node get_rt(i128 R,int k){
    if(k==-1) return f[0][0];
    int rb=(R>>k&1);
    node res=get_rt(R,k-1);
    if(rb){
        res.add(a[k]);
        res=f[k][0]+res;
    }
    //cout << "get_rt " << (int)R << ' ' << k << ' ' << res.S << ' ' << res.X[0] << ' ' << res.X[1] << ' ' << res.X[2] << '\n';
    return res;
}
node get(i128 L,i128 R,int k=n-1,int T=0){
    if(k==-1) return node(T);
    int lb=(L>>k&1), rb=(R>>k&1);
    if(lb==rb) return get(L,R,k-1,(T+lb*a[k])%mod);
    node lt=get_lt(L,k-1),rt=get_rt(R,k-1);
    rt.add(a[k]);lt=lt+rt;lt.add(T);
    //cout << "get " << (int)L << ' ' << (int)R << ' ' << k << ' ' << lt.S << ' ' << lt.X[0] << ' ' << lt.X[1] << ' ' << lt.X[2] << '\n';
    return lt;
}

void build(int l,int r,int id){
    if(l==r){
        tree[id]=get(pos[l-1],pos[l]-1);
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

void getnew(int id,int x){
    lazy[id]=(lazy[id]+x)%mod;
    tree[id].add(x);
}
void pushdown(int id){
    if(!lazy[id]) return;
    getnew(id<<1,lazy[id]);
    getnew(id<<1|1,lazy[id]);
    lazy[id]=0;
}
node query(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return node();
    if(tl<=l && r<=tr) return tree[id];
    pushdown(id);
    int mid=(l+r)>>1;
    return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
}
void update(int l,int r,int id,int tl,int tr,int x){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        getnew(id,x);
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,x);update(mid+1,r,id<<1|1,tl,tr,x);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

void solve(){
    for(int i=1;i<=2;i++) (inv[i]*=inv[i-1])%=mod;
    
    cin >> n >> q;
    a.assign(n,0);
    for(int i=0;i<n;i++) cin >> a[i];
    vector<i128> l(q),r(q);
    
    vector<int> x(q,-1);
    for(int i=0;i<q;i++){
        int op;string L,R;
        cin >> op >> L >> R;
        
        i128 cur=1;
        for(int j=n-1;j>=0;j--){
            if(L[j]=='1') l[i]+=cur;
            if(R[j]=='1') r[i]+=cur;
            cur<<=1;
        }
        if(op==1) cin >> x[i];
        pos.push_back(l[i]);
        pos.push_back(++r[i]);
    }
    sort(pos.begin(),pos.end());
    pos.erase(unique(pos.begin(),pos.end()),pos.end());
    int sz=(int)pos.size()-1;

    f[0][0]=node(0);
    f[0][1]=node(a[0]);
    for(int i=1;i<n;i++){
        f[i][0]=f[i-1][0]+f[i-1][1];
        f[i][1]=f[i][0];f[i][1].add(a[i]);
    }
    /*
    for(int i=0;i<n;i++){
        for(int j=0;j<=1;j++) cout << "f " << i << ' ' << j << ' ' << f[i][j].S << ' ' << f[i][j].X[0] << ' ' << f[i][j].X[1] << ' ' << f[i][j].X[2] << '\n';
    }
    */
    build(1,sz,1);
    for(int i=0;i<q;i++){
        int L=lower_bound(pos.begin(),pos.end(),l[i])-pos.begin()+1;
        int R=lower_bound(pos.begin(),pos.end(),r[i])-pos.begin();
        if(x[i]==-1) cout << query(1,sz,1,L,R).X[2] << '\n';
        else update(1,sz,1,L,R,x[i]);
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
/*
3 3
1 2 4
2 000 111
1 010 101 1
2 000 111

2 2
1 1
2 00 10
2 00 11
*/