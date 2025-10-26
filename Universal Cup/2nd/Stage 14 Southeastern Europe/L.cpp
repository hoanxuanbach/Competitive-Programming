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

int n,m,a[maxn],cc[maxn];

void solve(){
    cin >> n >> m;
    int k=n,cnt=m,sum=0;
    for(int i=0;i<m;i++){
        cin >> a[i];
        cc[a[i]]++;
        sum+=a[i];
    }
    for(int i=0;i<=n;i++){
        if(sum<=i*(n-i)){k=i;break;}
        cnt-=cc[i];sum-=cnt;
    }
    vector<vector<char>> res(n,vector<char>(m,'.'));
    vector<int> cur;
    for(int i=1;i<=k;i++) cur.push_back(n-i);
    for(int i=0;i<m;i++){
        int x=max(a[i],k)-k,lst=0;
        for(int j=(int)cur.size()-1;j>=0;j--){
            int d=min(x,cur[j]-lst);
            x-=d;cur[j]-=d;
            for(int t=cur[j];t<=cur[j]+d;t++) res[t][i]='#';
            lst=cur[j]+d+1;
        }
        x=k-min(k,a[i]);
        for(int j=0;j<n;j++) if(x && res[j][i]=='#') res[j][i]='.',x--;
    }
    cout << k << '\n';
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cout << res[i][j];
        cout << '\n';
    }
    for(int i=1;i<=n;i++) cc[i]=0;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
