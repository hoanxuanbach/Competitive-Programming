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
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma")
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
const int inf=2e18;
const int mod=998244353;
const int maxn=300005;
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
const int base=1000003;

int add(int x,int y){
    return min(x+y,inf);
}
int mul(int x,int y){
    if(x==0 || y==0) return 0;
    if(x>inf/y) return inf;
    else return x*y;
}

int n,k,dp[55][55][2],sum[55][2],C[55][55];
int pos[maxn];
vector<int> res;

int query(int l,int r){
    int N=r-l+1,t=0;
    //cout << '*' << l << ' ' << r << endl;
    if(N==1) return 1;
    if(l>1 && r<n){
        if((r-l+1)%2==0) return 0;
    }
    else if(l>1) t=(r-l)&1;
    //cout << '*' << l << ' ' << r << ' ' << N << ' ' << t << endl;
    //cout << l << ' ' << r << ' ' << sum[N][t] << '\n';
    return sum[N][t];
}

int get(int N){
    for(int i=2;i<n;i++){
        if((pos[i]-pos[i-1])*(pos[i]-pos[i+1])<0) return 0;
    }
    int l=n+1,r=0,res=1;
    for(int i=1;i<=n;i++){
        //cout << i << endl;
        if(pos[i]==n+1) l=min(l,i),r=i;
        else{
            if(l<=r){
                res=mul(C[N][r-l+1],mul(res,query(l,r)));
                N-=(r-l+1);
            }
            l=n+1;r=0;
        }
    }
    if(l<=r) res=mul(res,query(l,r));
    return res;
}

void solve(){
    cin >> n >> k;
    dp[2][1][0]=dp[2][2][1]=1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=i;j++){
            for(int k=1;k<=j;k++) dp[i+1][k][0]=add(dp[i+1][k][0],dp[i][j][1]);
            for(int k=j+1;k<=i+1;k++) dp[i+1][k][1]=add(dp[i+1][k][1],dp[i][j][0]);
            for(int k=0;k<=1;k++) sum[i][k]=add(sum[i][k],dp[i][j][k]);
        }
    }
    C[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i;j++){
            C[i][j]=C[i-1][j];
            if(j) C[i][j]=add(C[i][j],C[i-1][j-1]);
        }
    }
    for(int i=1;i<=n;i++) pos[i]=n+1;
    if(add(sum[n][0],sum[n][1])<k){
        cout << -1 << '\n';
        return;
    }
    for(int i=1;i<=n;i++){
        //cout << i << endl;
        for(int j=1;j<=n;j++){
            if(pos[j]<=n) continue;
            pos[j]=i;
            //cout << i << ' ' << j << endl;
            int num=get(n-i);
            //cout << num << '\n';
            if(k>num){
                k-=num;
                pos[j]=n+1;
            }
            else{
                res.push_back(j);
                break;
            }
        }
    }
    for(int x:res) cout << x << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
