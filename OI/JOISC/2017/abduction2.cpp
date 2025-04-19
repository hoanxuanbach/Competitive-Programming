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
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
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
struct Sparse{
    int n;
    vector<vector<int>> lt,rt;
    Sparse(){}
    Sparse(vector<int> a){
        n=(int)a.size();
        lt.assign(n,vector<int>(maxl,0));
        rt.assign(n,vector<int>(maxl,0));
        for(int i=0;i<n;i++) lt[i][0]=rt[i][0]=a[i];
        for(int j=1;j<maxl;j++){
            for(int i=0;i<=n-(1<<j);i++) rt[i][j]=max(rt[i][j-1],rt[i+(1<<(j-1))][j-1]);
            for(int i=(1<<j)-1;i<n;i++) lt[i][j]=max(lt[i][j-1],lt[i-(1<<(j-1))][j-1]);
        }
    }
    int get_lt(int p,int x){
        for(int i=maxl-1;i>=0;i--){
            if(p<(1<<i)-1) continue;
            if(lt[p][i]<x) p-=(1<<i);
        }
        return p;
    }
    int get_rt(int p,int x){
        for(int i=maxl-1;i>=0;i--){
            if(p>n-(1<<i)) continue;
            if(rt[p][i]<x) p+=(1<<i);
        }
        return p;
    }
}sx,sy;
int n,m,q;
vector<int> a,b;
unordered_map<int,int> mp[2][maxn];
int query(int x,int y,int t){
    if(x<0 || x>=n || y<0 || y>=m) return 0;
    auto it=mp[t][x].find(y);
    if(it!=mp[t][x].end()) return (long long)(it->second);
    int ans=0;
    if(t==0){
        int lt=sx.get_lt(x-1,b[y]),rt=sx.get_rt(x+1,b[y]);
        //cout << x << ' ' << y << ' ' << t << ' ' << lt << ' ' << rt << '\n';
        ans=max(ans,(min(rt,n-1)-x)+query(rt,y,1));
        ans=max(ans,(x-max(lt,0LL))+query(lt,y,1));
    }
    else{
        int lt=sy.get_lt(y-1,a[x]),rt=sy.get_rt(y+1,a[x]);
        //cout << x << ' ' << y << ' ' << t << ' ' << lt << ' ' << rt << '\n';
        ans=max(ans,(min(rt,m-1)-y)+query(x,rt,0));
        ans=max(ans,(y-max(lt,0LL))+query(x,lt,0));
    }
    return (long long)(mp[t][x][y]=ans);
}
void solve(){
    cin >> n >> m >> q;
    a.resize(n);b.resize(m);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<m;i++) cin >> b[i];
    sx=Sparse(a);
    sy=Sparse(b);
    for(int i=0;i<q;i++){
        int x,y;cin >> x >> y;x--;y--;
        cout << max(query(x,y,0),query(x,y,1)) << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
