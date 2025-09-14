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
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
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
int h[maxn],cnt=0;
map<int,int> mp;
void add(int x){
    mp[x]++;
    if(mp[x]==2) cnt++;
}
void del(int x){
    if(mp[x]==2) cnt--;
    mp[x]--;
}
struct SA{
    string s;
    set<int> ss;
    int p[maxn],r[maxn],c[maxn],r2[maxn],cnt[maxn],cn[maxn],lcp[maxn],n;
    vector<pii> v[maxn];
    int par[maxn],f[maxn];
    void suffix_array(){
        int v=128;
        for(int i=0;i<n;i++) cnt[s[i]]++;
        for(int i=1;i<v;i++) cnt[i]+=cnt[i-1];
        for(int i=0;i<n;i++) c[--cnt[s[i]]]=i;
        r[c[0]]=0;v=1;
        for(int i=1;i<n;i++){
            if(s[c[i]]!=s[c[i-1]]) v++;
            r[c[i]]=v-1;
        }
        for(int len=2;len<=2*n;len<<=1){
            for(int i=0;i<n;i++) cn[i]=(c[i]+n-len/2)%n;
            for(int i=0;i<v;i++) cnt[i]=0;
            for(int i=0;i<n;i++) cnt[r[i]]++;
            for(int i=1;i<v;i++) cnt[i]+=cnt[i-1];
            for(int i=n-1;i>=0;i--) c[--cnt[r[cn[i]]]]=cn[i];
            r2[c[0]]=0;v=1;
            for(int i=1;i<n;i++){
                pii cur={r[c[i]],r[(c[i]+len/2)%n]};
                pii pre={r[c[i-1]],r[(c[i-1]+len/2)%n]};
                if(cur!=pre) v++;
                r2[c[i]]=v-1;
            }
            for(int i=0;i<n;i++) r[i]=r2[i];
        }
    }
    void cal_lcp(){
        for(int i=1;i<n;i++) p[c[i]]=i;
        int k=0;
        for(int i=0;i<n;i++){
            int u=p[i];
            if(u==n-1){lcp[u]=k=0;continue;}
            int j=c[u+1];
            while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
            lcp[u]=k;
            if(k) k--;
        }
    }
    int findpar(int u){
        if(u!=par[u]) return par[u]=findpar(par[u]);
        return u;
    }
    void unions(int u,int v){
        u=findpar(u);v=findpar(v);
        if(u==v){
            add(f[u]);
            return;
        }
        if(r[u]<r[v]) swap(u,v);
        del(f[u]);del(f[v]);
        par[v]=u;r[u]+=r[v];f[u]^=f[v];
        add(f[u]);
        return;
    }
    void update(int x){
        for(pii a:v[x]) unions(a.fi,a.se);
    }
    void solve(){
        s+='$';n=(int)s.length();
        suffix_array();
        cal_lcp();
        for(int i=1;i<n;i++){
            f[i]=h[c[i]];par[i]=i;r[i]=1;
            v[n-c[i]-1].push_back({i,i});
            v[lcp[i]].push_back({i,i+1});
        }
    }
}s,t;
void solve(){
    int n;cin >> n;
    for(int i=0;i<n;i++) h[i]=rng();
    cin >> s.s >> t.s;
    s.solve();t.solve();
    int num=0,sum=0;
    for(int i=n;i>=1;i--){
        s.update(i);t.update(i);
        num+=cnt;sum+=cnt*i;
    }
    cout << num << ' ' << sum << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
