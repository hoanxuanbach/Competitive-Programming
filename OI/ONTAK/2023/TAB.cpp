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
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int mod=998244353;
const int maxn=1000005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;
const int Sq=1000;

int n,q,a[maxn],p[maxn],s[maxn];
int total[maxn],num[maxn],check[maxn];
vector<int> cc[maxn];


void solve(){
    cin >> n >> q;
    int S=0;
    for(int i=1;i<=n;i++) cin >> a[i],S+=a[i];
    vector<int> pm,dd,d2;
    dd.push_back(1);
    for(int i=2;i<=n;i++){
        if(!p[i]){
            if(i>Sq) pm.push_back(i);
            for(int j=i;j<=n;j+=i) p[j]=i;
        }
        int d=i,Max=0,mul=1;
        while(d>1){
            int j=p[d];
            Max=max(Max,j);mul*=j;
            while(d%j==0) d/=j;
        }
        if(mul!=i) a[mul]+=a[i];
        else if(Max<=Sq){
            if(i<=Sq) dd.push_back(i);
            else d2.push_back(i);
        }
    }
    for(int x:d2){
        int a=x;
        while(a>1){
            int j=p[a];
            cc[j].push_back(x);
            while(a%j==0) a/=j;
        }
    }
    for(int x:dd){
        s[x]=a[x];
        for(int y:pm){
            if(x*y>n) break;
            s[x]+=a[x*y];
        }
    }
    int sum=0;
    for(int i=1;i<=q;i++){
        int d;cin >> d;
        if(d>Sq){
            check[d]^=1;
            for(int x:dd){
                if(d*x>n) break;
                total[x]+=(check[d]?a[x*d]:-a[x*d]);
                if(!num[x]) sum+=(check[d]?a[x*d]:-a[x*d]);
            }
        }
        else{
            check[d]^=1;
            for(int x:dd){
                if(x%d!=0) continue;
                if(!num[x]) sum+=s[x]-total[x];
                num[x]+=(check[d]?1:-1);
                if(!num[x]) sum+=total[x]-s[x];
            }
            for(int x:cc[d]){
                if(!num[x]) sum+=a[x];
                num[x]+=(check[d]?1:-1);
                if(!num[x]) sum-=a[x];
            }
        }
        cout << S-sum << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
