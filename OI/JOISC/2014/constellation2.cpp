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
const int maxn=3005;
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

double PI = acos(-1.0);

struct vec{
    int x=0,y=0,c=0;
    double d;
    vec(int x=0,int y=0,int c=0):x(x),y(y),c(c){
        d=atan2(y,x);
    }
    bool operator<(vec a){
        return d<a.d;
    }
}P[2*maxn];

int n,X[maxn],Y[maxn],C[maxn];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> X[i] >> Y[i] >> C[i],C[i];
    int ans=0;
    for(int t=1;t<=n;t++){
        for(int i=1;i<t;i++) P[i]=vec(X[i]-X[t],Y[i]-Y[t],C[i]);
        for(int i=t+1;i<=n;i++) P[i-1]=vec(X[i]-X[t],Y[i]-Y[t],C[i]);
        sort(P+1,P+n);
         vector<int> A(3,0),B(3,0);
         for(int i=1;i<n;i++){
            A[P[i].c]++;
            P[i+n-1]=P[i];
            P[i+n-1].d+=2*PI;
         }
         int res=1;
         for(int i=1,j=1;i<n;i++){
            while(P[i].d+PI>P[j].d) B[P[j++].c]++;
            int res=1;
            for(int k=0;k<3;k++){
                if(k!=C[t]) res*=(A[k]-B[k]);
                if(k!=P[i].c) res*=B[k];
            }
            ans+=res;
            B[P[i].c]--;
         }
    }
    cout << ans/2 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
