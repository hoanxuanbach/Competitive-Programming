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
const int maxn=300005;
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
const int base=101;

int n,x[maxn],y[maxn],r[maxn],res[maxn],B;
map<pii,vector<int>> mp;
set<int> cc;

void build(){
    mp.clear();
    for(int i:cc) mp[{x[i]/B,y[i]/B}].push_back(i);
}

bool intersect(int i,int j){
    return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])<=(r[i]+r[j])*(r[i]+r[j]);
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> x[i] >> y[i] >> r[i];
        cc.insert(i);
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[&](int a,int b){
        if(r[a]==r[b]) return a<b;
        return r[a]>r[b];
    });
    for(int i:ord){
        if(res[i]) continue;
        if(!B || r[i]*2<=B){
            B=r[i];
            build();
        }
        for(int X=x[i]/B-2;X<=x[i]/B+2;X++) for(int Y=y[i]/B-2;Y<=y[i]/B+2;Y++){
            auto it=mp.find({X,Y});
            if(it!=mp.end()){
                for(int j:it->se) if(!res[j] && intersect(i,j)){
                    res[j]=i;
                    cc.erase(j);
                }
            }
        }
    }
    for(int i=1;i<=n;i++) cout << res[i] << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
