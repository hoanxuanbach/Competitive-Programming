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
const int mod=998244353;
const int maxn=5005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,q,a[maxn],Max[maxn],lt[maxn],rt[maxn],x[maxn],Max2[maxn];
int qs[200005],qd[200005];

void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=q;i++) cin >> qd[i] >> qs[i];
    memset(Max,-1,sizeof(Max));Max[1]=n;
    for(int t=1;t<=q;t++){
        //for(int i=1;i<=n;i++) cout << Max[i] << ' ';
        //cout << '\n';
        int s=qs[t],d=qd[t];
        for(int i=1;i<=n;i++) x[i]=(a[i]>=s),Max2[i]=-1;
        for(int i=1;i<=n;i++){
            if(x[i]) lt[i]=lt[i-1]+1;
            else lt[i]=0;
        }
        lt[0]=0;
        for(int i=1;i<=n;i++){
            if(lt[i]>=d) lt[i]=i;
            else lt[i]=lt[i-1];
        }
        for(int i=n;i>=1;i--){
            if(x[i]) rt[i]=rt[i+1]+1;
            else rt[i]=0;
        }
        rt[n+1]=n+1;
        for(int i=n;i>=1;i--){
            if(rt[i]>=d) rt[i]=i;
            else rt[i]=rt[i+1];
        }
        bool check=false;
        for(int l=1;l<=n;l++){
            if(Max[l]==-1) continue;
            int r=Max[l],l2=rt[l],r2=lt[r];
            if(l2+d<=r+1) Max2[l2+d]=max(Max2[l2+d],r);
            if(r2-d>=l-1) Max2[l]=max(Max2[l],r2-d);
        }
        for(int i=1;i<=n;i++){
            if(Max2[i]>=i-1) check=true;
            swap(Max[i],Max2[i]);
        }
        if(!check){
            cout << t-1 << '\n';
            return;
        }
    }
    cout << q << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}