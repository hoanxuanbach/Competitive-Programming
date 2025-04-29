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
const int base=101;

int n,a[maxn],p[maxn];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++){int x;cin >> x;p[x]=i;}
    for(int i=1;i<=n;i++) a[i]=p[a[i]];
    string res;
    deque<int> dq;
    int cnt=0;
    for(int i=1;i<=n;i++){
        dq.push_back(a[i]);
        if(i>=1) cnt+=a[i]>a[i%n+1];
    }
    while(cnt>1){
        if(dq[0]<dq[1] || dq.front()==n){
            dq.push_back(dq[0]);
            dq.pop_front();
            res+='1';
        }
        else{
            cnt--;
            if(dq.back()>dq[0]) cnt--;
            if(dq[1]>dq[2]) cnt--;
            if(dq[0]>dq[2]) cnt++;
            if(dq.back()>dq[1]) cnt++;
            swap(dq[0],dq[1]);
            dq.push_back(dq[0]);
            dq.pop_front();
            res+='2';
        }
    }
    while(dq.front()!=1){
        res+='1';
        dq.push_back(dq[0]);
        dq.pop_front();
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
