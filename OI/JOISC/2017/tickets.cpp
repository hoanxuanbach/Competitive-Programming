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

int n,m,A[maxn],S[maxn];
vector<pii> v[maxn];

void solve(){
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int a,b,c;cin >> a >> b >> c;
        if(a>b) swap(a,b);
        A[a]+=c;A[b]-=c;
        v[a].push_back({b,c});
    }
    for(int i=1;i<=n;i++) A[i]+=A[i-1];
    int pos=max_element(A+1,A+n+1)-A,mx=A[pos];
    //cout << pos << ' ' << mx << '\n';

    auto cal = [&](int N,int m){
        for(int i=1;i<=n;i++) S[i]=0;
        priority_queue<pii> pq;
        int cur=0;
        for(int i=1;i<=pos;i++){
            int X=(A[i]+N-m+1)/2;
            for(auto x:v[i]) if(x.fi>pos) pq.push(x);
            while(cur<X){
                if(pq.empty()) return false;
                pii x=pq.top();pq.pop();
                if(cur+x.se<=X){
                    cur+=x.se;
                    S[x.fi]+=x.se;
                }
                else{
                    S[x.fi]+=(X-cur);
                    x.se-=(X-cur);
                    pq.push(x);cur=X;
                }
            }
        }
        for(int i=pos+1;i<=n;i++){
            cur-=S[i];
            if(A[i]-cur+N-cur>m) return false;
        }
        return true;
    };
    auto check = [&](int m){
        for(int N=mx-m;N<=mx-m+1;N++){
            if(cal(N,m)) return true;
        }
        return false;
    };
    int l=1,r=mx,res=mx;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    cout << res << '\n';
}

signed main(){
    //freopen("05-04.in","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
