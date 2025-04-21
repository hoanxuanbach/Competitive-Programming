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
const long long inf=1e18;
const int mod=998244353;
const int maxn=800005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
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

int n,m,l[maxn],r[maxn];
int nxt[maxn][maxl];
vector<int> com;

void solve(){
    cin >> n >> m;
    com.push_back(0);
    for(int i=1;i<=n;i++){
        cin >> l[i] >> r[i];
        com.push_back(l[i]);
        com.push_back(r[i]);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    m=(int)com.size();
    for(int i=0;i<2*m;i++) nxt[i][0]=i;
    //cout << m << '\n';
    for(int i=1;i<=n;i++){
        l[i]=lower_bound(com.begin(),com.end(),l[i])-com.begin();
        r[i]=lower_bound(com.begin(),com.end(),r[i])-com.begin();
        if(l[i]>r[i]){
            nxt[l[i]][0]=max(nxt[l[i]][0],m+r[i]);
        }
        else{
            nxt[l[i]][0]=max(nxt[l[i]][0],r[i]);
            nxt[m+l[i]][0]=max(nxt[m+l[i]][0],m+r[i]);
        }
        //cout << l[i] << ' ' << r[i] << '\n';
    }
    for(int i=1;i<2*m;i++) nxt[i][0]=max(nxt[i][0],nxt[i-1][0]);
    for(int i=1;i<20;i++){
        for(int j=0;j<2*m;j++) nxt[j][i]=nxt[nxt[j][i-1]][i-1];
    }
    int res=inf;
    for(int i=0;i<m;i++){
        int cnt=0,u=i;
        for(int j=19;j>=0;j--){
            if(nxt[u][j]<i+m) cnt+=(1<<j),u=nxt[u][j];
        }
        cnt++;u=nxt[u][0];
        //cout << i << ' ' << u << ' ' << cnt << '\n';
        if(u>=i+m) res=min(res,cnt);
    }
    cout << (res==inf?-1:res) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

