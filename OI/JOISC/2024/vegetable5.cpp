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
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int mod=998244353;
const int maxn=300005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

void solve(){
    int N;cin >> N;
    vector<int> A(2*N),B(N),C(N);
    for(int i=0;i<2*N;i++) cin >> A[i];
    for(int i=0;i<N;i++) cin >> B[i];
    for(int i=0;i<N;i++) cin >> C[i];
    sort(B.begin(),B.end());
    sort(C.begin(),C.end());

    vector<int> A2=A,B2=B,C2=C;
    for(int i=0;i<2*N;i++) A2[i]=-A[i];
    for(int i=0;i<N;i++) B2[i]=-B2[i],C2[i]=-C2[i];
    rotate(A2.begin(),A2.begin()+N,A2.end());
    reverse(B2.begin(),B2.end());
    reverse(C2.begin(),C2.end());

    auto check = [&](int d){
        auto get = [&](vector<int> &a,vector<int> &b){
            vector<int> cnt(N+1);
            {
                int pl=0,pr=0,sr=2*N;
                for(int i=0;i<N;i++){
                    while(pl<N && b[pl]<a[i]-d) pl++;
                    while(pr<N && b[pr]<=a[i]+d) pr++;
                    while(sr>N && a[sr-1]<a[i]) sr--;
                    int val=N+i-sr;
                    if(pr<=val) continue;
                    int l=max(0,i-pr+1);
                    int r=(pl<=val?i+1:i-pl+1);
                    if(l<r) cnt[l]++,cnt[r]--;
                }
            }
            {
                int pl=0,pr=0,sr=0;
                for(int i=2*N-1;i>=N;i--){
                    while(pl<N && b[pl]<a[i]-d) pl++;
                    while(pr<N && b[pr]<=a[i]+d) pr++;
                    while(sr<N && a[sr]<=a[i]) sr++;
                    int val=sr-(i-N+1);
                    if(pr<=val) continue;
                    int r=min(N,i-N+pr+1);
                    int l=(pl<=val?i-N+1:i-N+1+pl);
                    if(l<r) cnt[l]++,cnt[r]--;
                }
            }
            for(int i=1;i<=N;i++) cnt[i]+=cnt[i-1];
            for(int i=0;i<N;i++) cnt[i]=(cnt[i]==N);
            return cnt;
        };
        vector<int> X=get(A,B),Y=get(A,C);
        vector<int> X2=get(A2,B2),Y2=get(A2,C2);
        for(int i=0;i<N;i++){
            if(X[i] && Y2[i]) return true;
            if(X2[i] && Y[i]) return true;
        }
        return false;
    };
    int l=0,r=inf,res=inf;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
