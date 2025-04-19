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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
const int root=3;
/*
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
*/
const int base=101;

void solve(){
    int n;cin >> n;n*=2;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++) cin >> b[i];
    vector<vector<pii>> rn(n,vector<pii>(2,mpp(-1,-1)));
    auto add = [&](pii a,pii b){
        if(a==mpp(-1,-1)) return b;
        else if(b==mpp(-1,-1)) return a;
        else return mpp(min(a.fi,b.fi),max(a.se,b.se));
    };
    rn[0][0]={0,0};rn[0][1]={1,1};
    for(int i=1;i<n;i++){
        if(a[i-1]<=a[i]) rn[i][0]=add(rn[i][0],rn[i-1][0]);
        if(a[i-1]<=b[i]) rn[i][1]=add(rn[i][1],rn[i-1][0]);
        if(b[i-1]<=a[i]) rn[i][0]=add(rn[i][0],rn[i-1][1]);
        if(b[i-1]<=b[i]) rn[i][1]=add(rn[i][1],rn[i-1][1]);
        if(rn[i][1]!=mpp(-1,-1)) rn[i][1].fi++,rn[i][1].se++;
    }
    int c=0,cur=n/2;
    while(c<=1 && (rn[n-1][c].se<n/2 || rn[n-1][c].fi>n/2)) c++;
    if(c==2){
        cout << -1 << '\n';
        return;
    }
    string ans;
    for(int i=n-1;i>=0;i--){
        ans+=char('A'+c);cur-=c;
        if(i==0) break;
        if(rn[i-1][0].fi<=cur && cur<=rn[i-1][0].se && a[i-1]<=(c?b[i]:a[i])) c=0;
        else c=1;
    }
    reverse(ans.begin(),ans.end());
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
