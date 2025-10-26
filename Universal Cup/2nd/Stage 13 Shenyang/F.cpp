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
const int mod=1'000'000'000'000'000'003;
const int maxn=200005;
const int bl=450;
const int maxs=455;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=(__int128)res*a%mod;
        a=(__int128)a*a%mod;n>>=1;
    }
    return res;
}
const int base=1000003;

int n,m,q,a[maxn];

int g[maxn][maxl],lg2[maxn];
int query(int l,int r){
    int p=lg2[r-l+1];
    return __gcd(g[l][p],g[r-(1<<p)+1][p]);
}
void build_sparse(){
    for(int i=2;i<=m;i++) lg2[i]=lg2[i/2]+1;
    for(int i=1;i<18;i++){
        for(int j=1;j<=(m-(1<<i)+1);j++) g[j][i]=__gcd(g[j][i-1],g[j+(1<<(i-1))][i-1]);
    }
}

struct Query{
    int id,x,y;
}qq[maxn];
int pw[maxn],inv[maxn],invb;
bool check[maxn],res[maxn];

struct SQRT{
    int cur[maxn],total[maxs];
    void update(int x,int val){
        total[x/bl]=(total[x/bl]-cur[x]+mod)%mod;
        cur[x]=val;
        total[x/bl]=(total[x/bl]+cur[x])%mod;
    }
    int query(int l,int r){
        int sum=0;
        for(int i=l;i<=r;i++){
            if(i%bl==0 && i+bl-1<=r){
                sum=(sum+total[i/bl])%mod;
                i+=bl-1;
            }
            else sum=(sum+cur[i])%mod;
        }
        return sum;
    }
}f0,fall;

struct SQRT2{
    int pre[maxn],lazy[maxs];
    void build(){
        for(int i=1;i<=n;i++) pre[i]=(pre[i-1]+(__int128)a[i]*pw[i]%mod)%mod;
    }
    void update(int x,int val){
        int d=(__int128)(val-a[x]+mod)*pw[x]%mod;
        a[x]=val;
        for(int i=x;i<=n;i++){
            if(i%bl==0){
                lazy[i/bl]=(lazy[i/bl]+d)%mod;
                i+=bl-1;
            }
            else pre[i]=(pre[i]+d)%mod;
        }
    }
    int query(int l,int r){
        l--;
        int total=(pre[r]+lazy[r/bl]-pre[l]-lazy[l/bl])%mod;
        total=(total+mod)%mod;
        return total;
    }
}f1;

void solve(){
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=m;i++) cin >> g[i][0];
    build_sparse();
    pw[0]=inv[0]=1;
    invb=power(base-1,mod-2);
    for(int i=1;i<=n;i++){
        pw[i]=(__int128)pw[i-1]*base%mod;
        inv[i]=power(pw[i],mod-2);
    }
    for(int i=1;i<=q;i++){
        char c;cin >> c;
        if(c=='Q'){
            int l,r,s,t;cin >> l >> r >> s >> t;
            int d=__gcd(r-l+1,query(s,t));
            qq[i]={d,l,r};
            check[d]=true;
        }
        else{
            int p,v;cin >> p >> v;
            qq[i]={-1,p,v};
        }
    }
    for(int k=1;k<=bl;k++){
        if(!check[k]) continue;
        for(int i=1;i<=n;i++){
            fall.update(i,(__int128)a[i]*pw[i%k]%mod);
            if(i%k==0) f0.update(i/k,a[i]);
        }
        for(int i=1;i<=q;i++){
            if(qq[i].id!=-1 && qq[i].id!=k) continue;
            if(qq[i].id==-1){
                int x=qq[i].x,val=qq[i].y;
                fall.update(x,(__int128)val*pw[x%k]%mod);
                if(x%k==0) f0.update(x/k,val);
            }
            else{
                int l=qq[i].x,r=qq[i].y;
                int total=fall.query(l,r);
                l=(l-1)/k+1;r/=k;
                int S=(__int128)f0.query(l,r)*(pw[k]+mod-1)%mod*invb%mod;
                res[i]=(S==total);
            }
        }
    }

    f1.build();
    for(int i=1;i<=q;i++){
        if(qq[i].id!=-1 && qq[i].id<=bl) continue;
        if(qq[i].id==-1){
            int x=qq[i].x,val=qq[i].y;
            f1.update(x,val);
        }
        else{
            int l=qq[i].x,r=qq[i].y,k=qq[i].id;
            int total=0,S=0;
            while(l<=r){
                total=(total+(__int128)f1.query(l,l+k-1)*inv[l]%mod)%mod;
                S=(S+a[l])%mod;l+=k;
            }
            S=(__int128)S*(pw[k]+mod-1)%mod*invb%mod;
            res[i]=(S==total);
        }
    }

    for(int i=1;i<=q;i++){
        if(qq[i].id!=-1) cout << (res[i]?"Yes":"No") << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
