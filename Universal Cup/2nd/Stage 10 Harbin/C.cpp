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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=1e12+169;
const int maxn=150005;
const int bl=1500;
const int maxs=405;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=131;

struct query{
    int l,r,id;
    friend bool operator<(query a,query b){
        if((a.l/bl)!=(b.l/bl)) return (a.l/bl)<(b.l/bl);
        else{
            if((a.l/bl)&1) return a.r>b.r;
            else return a.r<b.r;
        }
    }
}qq[maxn];

int n,m;
char s[maxn],t[maxn];
int w[maxn],pre[maxn],kmp[maxn],par[maxn][maxl],dep[maxn];
int res[maxn];

int hs[maxn],ht[maxn],pw[maxn];
int lt[maxn],rt[maxn];

void solve(){
    cin >> n >> m;pw[0]=1;
    for(int i=1;i<=n;i++){
        cin >> s[i];
        hs[i]=((__int128)hs[i-1]*base%mod+s[i]-'a'+1)%mod;
        pw[i]=(__int128)pw[i-1]*base%mod;
    }
    for(int i=1;i<=n;i++){
        cin >> t[i];
        ht[i]=((__int128)ht[i-1]*base%mod+t[i]-'a'+1)%mod;
    }
    auto get_hs = [&](int l,int r){
        return (hs[r]-(__int128)hs[l-1]*pw[r-l+1]%mod+mod)%mod;
    };
    auto get_ht = [&](int l,int r){
        return (ht[r]-(__int128)ht[l-1]*pw[r-l+1]%mod+mod)%mod;
    };
    for(int i=1;i<=n;i++){
        cin >> w[i];
        pre[i]=pre[i-1]+w[i];
    }
    kmp[0]=-1;
    kmp[1]=0;dep[1]=w[1];
    for(int i=2;i<=n;i++){
        int j=kmp[i-1];
        while(j>=0 && s[j+1]!=s[i]) j=kmp[j];
        kmp[i]=par[i][0]=j+1;
        dep[i]=dep[j+1]+w[i];
        for(int k=1;k<18;k++) par[i][k]=par[par[i][k-1]][k-1];
    }
    int cur=0;
    for(int i=1;i<=n;i++){
        while(cur>=0 && s[cur+1]!=t[i]) cur=kmp[cur];
        rt[i]=++cur;
        int l=1,r=n-i+1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(get_hs(1,mid)==get_ht(i,i+mid-1)) lt[i]=mid,l=mid+1;
            else r=mid-1;
        }
        //cout << lt[i] << ' ' << rt[i] << '\n';
    }
    for(int i=1;i<=m;i++){
        cin >> qq[i].l >> qq[i].r;
        qq[i].id=i;
    }
    sort(qq+1,qq+m+1);
    int ans=0;
    auto add_lt = [&](int l,int r){
        int k=min(r-l+1,lt[l]);
        return pre[k];
    };
    auto add_rt = [&](int l,int r){
        int len=r-l+1;r=rt[r];
        for(int i=17;i>=0;i--) if(par[r][i]>len) r=par[r][i];
        if(r>len) r=par[r][0];
        return dep[r];
    };
    for(int i=1,l=1,r=0;i<=m;i++){
        while(l>qq[i].l) ans+=add_lt(--l,r);
        while(r<qq[i].r) ans+=add_rt(l,++r);
        while(l<qq[i].l) ans-=add_lt(l++,r);
        while(r>qq[i].r) ans-=add_rt(l,r--);
        res[qq[i].id]=ans;
    }
    for(int i=1;i<=m;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
