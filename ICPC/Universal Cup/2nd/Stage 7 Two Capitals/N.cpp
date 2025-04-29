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
const int mod=998244353;
const int maxn=10005;
const int bl=10;
const int maxs=1005;
const int maxm=200005;
const int maxq=1000005;
const int L=15;
const int maxa=1000000;
const int root=3;
const int base=131;

long long n,K,T,a[maxn];
int lt[maxn],rt[maxn],lg2[maxn];
short int dp[maxn][maxn];

//RMQ O(n) O(1)
short int mask[maxn][maxn],d[maxn][maxs][L];

void build(int x){
    int sz=n-x+1;

    for(int i=0;i<=sz/L;i++) d[x][i][0]=n;
    for(int i=1;i<=sz;i++) d[x][i/L][0]=min(d[x][i/L][0],dp[i][i+x-1]);
    for(int k=1;k<L;k++){
        for(int i=0;i<=sz/L-(1<<k)+1;i++) d[x][i][k]=min(d[x][i][k-1],d[x][i+(1<<(k-1))][k-1]);
    }

    for(int t=0;t<=sz/L;t++){
        int M=0;
        vector<int> cur;
        for(int i=max(1,t*L);i<=min(sz,t*L+L-1);i++){
            while(!cur.empty() && dp[cur.back()][cur.back()+x-1]>=dp[i][i+x-1]){
                M-=1<<(cur.back()-t*L);
                cur.pop_back();
            }
            M+=1<<(i-t*L);
            cur.push_back(i);
            mask[x][i]=M;
        }
    }
}

int get_small(int x,int l,int r){
    int M=mask[x][r];
    int k=l+__builtin_ctz(M>>(l%L));
    return dp[k][k+x-1];
}

int get_big(int x,int l,int r){
    int p=lg2[r-l+1];
    return min(d[x][l][p],d[x][r-(1<<p)+1][p]);
}

int query(int x,int l,int r){
    int lt=l/L,rt=r/L,res=n;
    if(lt==rt) res=min(res,get_small(x,l,r));
    else{
        res=min(res,get_small(x,l,lt*L+L-1));
        res=min(res,get_small(x,rt*L,r));
    }
    if(lt+1<rt) res=min(res,get_big(x,lt+1,rt-1));
    return res;
}

void solve(){
    cin >> n >> K >> T;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=2;i<=n;i++) lg2[i]=lg2[i/2]+1;
    sort(a+1,a+n+1);
    auto cal = [&](int l,int r){
        return 2*(max(a[r],0LL)-min(a[l],0LL));
    };
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++) if((j-i+1)<=(T-cal(i,j))/K) lt[i]=j;
        for(int j=i;j>=1;j--) if((i-j+1)<=(T-cal(j,i))/K) rt[i]=j;
    }
    for(int len=1;len<=n;len++){
        //cout << len << endl;
        for(int l=1;l<=n-len+1;l++){
            int r=l+len-1;dp[l][r]=n;
            if(lt[l]>=r) dp[l][r]=1;
            else dp[l][r]=min((int)dp[l][r],dp[lt[l]+1][r]+1);
            if(rt[r]<=l) dp[l][r]=1;
            else dp[l][r]=min((int)dp[l][r],dp[l][rt[r]-1]+1);
            long long d=(T-cal(l,r))/K;
            if(d<=0) continue;
            if(d<len){
                d=len-d;
                dp[l][r]=min((int)dp[l][r],query(d,l,r-d+1)+1);
            }
            else dp[l][r]=1;
        }
        build(len);
    }
    cout << dp[1][n] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

