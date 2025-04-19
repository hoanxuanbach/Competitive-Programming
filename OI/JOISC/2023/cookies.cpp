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
const int maxn=15005;
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
void solve(){
    int n,S=0;cin >> n;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i];
    vector<int> sa=a;
    sort(sa.begin(),sa.end());
    for(int x:sa) S+=x;
    int cur=0,sum=0;
    vector<int> c(S+1,0);
    for(int i=1;i<=S;i++){
        while(cur<n && sa[cur]<=i) sum+=sa[cur++];
        c[i]=sum+(n-cur)*i;
    }
    int m;cin >> m;
    vector<int> b(m+1);
    for(int i=0;i<m;i++) cin >> b[m-i];
    vector<vector<bitset<maxn>>> dp(m+1);
    bitset<maxn> all;all.set();
    for(int i=0;i<=m;i++) dp[i].resize((i==0?0:S/b[i])+1);
    dp[0][0][0]=1;
    for(int i=1;i<=m;i++){
        int x=b[i];
        for(int j=0;j<(int)dp[i-1].size();j++) dp[i][j]=dp[i-1][j];
        for(int j=1;j<=S/x;j++){
            dp[i][j]|=dp[i][j-1]<<x;
            dp[i][j]&=(all>>(maxn-c[j]-1));
        }
    }
    int box=-1;
    for(int i=S/b[m];i>=0;i--){
        if(dp[m][i][S]) box=i;
    }
    if(box==-1){
        cout << -1 << '\n';
        return;
    }
    vector<int> boxes;
    int cx=m,cy=box,cz=S;
    while(cx && cy && cz){
        if(cz>=b[cx] && dp[cx][cy-1][cz-b[cx]]){
            boxes.push_back(b[cx]);
            cz-=b[cx];cy--;
        }
        else cx--;
    }
    vector<vector<int>> v(box);
    priority_queue<pii> pq;
    for(int i=0;i<box;i++) pq.push({boxes[i],i});
    for(int i=0;i<n;i++){
        vector<pii> nxt;
        for(int j=1;j<=a[i];j++){
            pii x=pq.top();pq.pop();
            v[x.se].push_back(i+1);
            if(x.fi>1) nxt.push_back({x.fi-1,x.se});
        }
        for(pii x:nxt) pq.push(x);
    }
    cout << box << '\n';
    for(auto x:v){
        cout << (int)x.size() << ' ';
        for(int d:x) cout << d << ' ';
        cout << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
