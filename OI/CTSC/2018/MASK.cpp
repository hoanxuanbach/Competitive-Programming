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
const int maxn=205;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);

int fac[maxn],dfac[maxn],inv[maxn];
int C(int n,int k){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
void combi(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

int n,q,s[maxn];
int d[maxn][maxn];

void solve(){
    cin >> n;combi(n);
    for(int i=1;i<=n;i++) cin >> s[i],d[i][s[i]]=1;
    cin >> q;
    while(q--){
        int id;cin >> id;
        if(id){
            int k;cin >> k;
            vector<int> x(k);
            for(int i=0;i<k;i++){
                int p;cin >> p;
                x[i]=(mod+1-d[p][0])%mod;
            }
            vector<int> dp(k,0);dp[0]=1;
            auto add = [&](int id){
                for(int i=k-1;i>=0;i--){
                    if(!dp[i]) continue;
                    dp[i+1]=(dp[i+1]+dp[i]*x[id])%mod;
                    dp[i]=dp[i]*(mod+1-x[id])%mod;
                }
            };
            function<void(int,int)> dnc = [&](int l,int r){
                if(l==r){
                    int total=0;
                    for(int i=0;i<k;i++) total=(total+dp[i]*inv[i+1])%mod;
                    total=total*x[l]%mod;
                    cout << total << ' ';
                    return;
                }
                int mid=(l+r)>>1;
                vector<int> cc=dp;
                for(int i=mid+1;i<=r;i++) add(i);
                dnc(l,mid);dp=cc;
                for(int i=l;i<=mid;i++) add(i);
                dnc(mid+1,r);dp=cc;
            };
            dnc(0,k-1);
            cout << '\n';
        }
        else{
            int x,u,v;cin >> x >> u >> v;
            u=u*power(v,mod-2)%mod;
            for(int j=1;j<=s[x];j++){
                d[x][j-1]=(d[x][j-1]+d[x][j]*u)%mod;
                d[x][j]=(d[x][j]*(1-u)%mod+mod)%mod;
            }
        }
    }
    for(int i=1;i<=n;i++){
        int total=0;
        for(int j=1;j<=s[i];j++) total=(total+j*d[i][j])%mod;
        cout << total << ' ';
    }
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
