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
const int maxn=300005;
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
const int base=131;

int n,a[maxn],pre[maxn][2],sum[maxn];

int total[maxn];
void update(int l,int r,int val){
    total[l]+=val;
    total[r+1]-=val;
}

int lt[maxn],rt[maxn],res[maxn];

int cal(int l,int r,int p,int m1,int m2){
    if(m1==-1) return pre[r][l&1]-pre[l-1][l&1];
    if(m2==-1) return pre[r][r&1]-pre[l-1][r&1];
    if(a[m1]<a[m2]){
        int t=((r-m1)^m1)&1;
        return pre[m1][t]-pre[l-1][t]+cal(m1+1,r,p,rt[m1],m2);
    }
    else{
        int t=((m2-l)^m2)&1;
        return pre[r][t]-pre[m2-1][t]+cal(l,m2-1,p,m1,lt[m2]);
    }
}

void dnc(int l,int r,int p){
    if(lt[p]!=-1) dnc(l,p-1,lt[p]);
    if(rt[p]!=-1) dnc(p+1,r,rt[p]);
    res[p]=cal(l,r,p,lt[p],rt[p]);
    if(l<p){
        int rv=pre[r][p&1]-pre[p-1][p&1];
        if((p-l)&1) update(l,p-1,sum[r]-sum[p-1]-rv);
        else update(l,p-1,rv);
    }
    if(p<r){
        int lv=pre[p][p&1]-pre[l-1][p&1];
        if((r-p)&1) update(p+1,r,sum[p]-sum[l-1]-lv);
        else  update(p+1,r,lv);
    }
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    int pos=min_element(a+1,a+n+1)-a;
    rotate(a+1,a+pos+1,a+n+1);

    n--;
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+a[i];
        for(int j=0;j<=1;j++) pre[i][j]=pre[i-1][j];
        pre[i][i&1]+=a[i];
    }
    vector<int> v;
    for(int i=1;i<=n;i++){
        while(!v.empty() && a[v.back()]>a[i]) v.pop_back();
        lt[i]=(v.empty()?1:v.back()+1);
        v.push_back(i);
    }
    v.clear();
    for(int i=n;i>=1;i--){
        while(!v.empty() && a[v.back()]>a[i]) v.pop_back();
        rt[i]=(v.empty()?n:v.back()-1);
        v.push_back(i);
    }
    map<pii,int> mp;
    for(int i=1;i<=n;i++) mp[{lt[i],rt[i]}]=i;
    for(int i=1;i<=n;i++){
        int l=lt[i],r=rt[i];
        lt[i]=(l<i?mp[{l,i-1}]:-1);
        rt[i]=(i<r?mp[{i+1,r}]:-1);
    }
    dnc(1,n,mp[{1,n}]);
    n++;
    for(int i=1;i<n;i++){
        total[i]+=total[i-1];
        res[i]+=total[i];
        if(n&1) res[i]+=a[n];
    }
    {
        res[n]=a[n];
        int l=1,r=n-1;
        for(int i=2;i<=n;i++){
            if(i&1) res[n]+=max(a[l],a[r]);
            if(a[l]>a[r]) l++;
            else r--;
        }
    }
    rotate(res+1,res+n-pos+1,res+n+1);
    for(int i=1;i<=n;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
