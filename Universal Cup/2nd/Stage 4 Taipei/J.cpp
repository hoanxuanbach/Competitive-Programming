#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
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
const int maxn=5005;
const int B=650;
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

int n,k,w[maxn],s[maxn];
int L[maxn],R[maxn];

void solve(){
    cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> w[i],w[i]+=w[i-1];
    vector<int> dp(n);
    iota(dp.begin(),dp.end(),1);

    while(k--){
        int x;cin >> x;
        for(int i=1;i<=n;i++){
            L[i]=L[i-1];
            while(x<w[i]-w[L[i]]) L[i]++;
        }
        R[n+1]=n;
        for(int i=n;i>=1;i--){
            R[i]=R[i+1];
            while(w[R[i]]-w[i]>x) R[i]--;
        }
        vector<int> ndp(dp.begin(),dp.end());
        for(int i=0;i<n;i++){
            ndp[L[i]]=max(ndp[L[i]],dp[i]);
            ndp[i]=max(ndp[i],R[dp[i]]);
        }
        swap(dp,ndp);
    }
    cout << (dp[0]==n?"Yes":"No") << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
