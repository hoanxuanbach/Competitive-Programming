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

int n,a[maxn],cnt[maxn][maxn];
int C,c[maxn],S[maxn];

int cal(){
    int res=0;
    for(int i=n;i>=1;i--){
        for(int l=1;l<=n-i+1;l++){
            int r=l+i-1;
            cnt[l][r]=(a[l]==a[r])*(2+cnt[l-1][r+1]);
        }
    }
    {//contain midpoint
        for(int i=1;i<=n;i++){
            int l=i;
            for(int j=1;j<=C;j++) c[j]=0;
            set<int> s;
            s.insert(a[l]);
            c[a[l]]++;
            while(l>1 && a[l-1]>=a[l]){
                l--;
                s.insert(a[l]);
                c[a[l]]++;
            }
            for(int j=1;j<=C;j++) S[j]=S[j-1]+c[j];

            int Min=-1,cc=0;
            for(int j=i+1;j<=n;j++){
                if(a[i]>a[j]){
                    if(Min!=-1){
                        if(a[j]==Min) cc++;
                        else break;
                    }
                    else{
                        Min=a[j],cc=1;
                    }
                }
                else{
                    if(!c[a[j]]) s.insert(a[j]);
                    c[a[j]]--;
                    if(!c[a[j]]) s.erase(a[j]);
                }
                int last=C;
                if(!s.empty()) last=*s.begin();
                else res=max(res,j-l+1+cnt[l-1][j+1]);
                res=max(res,S[last-1]*2+(S[last]-S[last-1]+min(0LL,-c[last]))*2+cc);
            }
        }
    }
    {//not contain midpoint
        auto query = [&](int l,int r){
            while(l>=1 && r<=n && a[l]==a[r]) l--,r++;
            res=max(res,r-l-1);
            if(l<1 || r>n) return;
            int lt=l;
            for(int j=1;j<=C;j++) c[j]=0;
            set<int> s;
            s.insert(a[lt]);
            c[a[lt]]++;
            while(lt>1 && a[lt-1]>=a[lt]){
                lt--;
                s.insert(a[lt]);
                c[a[lt]]++;
            }
            for(int j=1;j<=C;j++) S[j]=S[j-1]+c[j];
            for(int j=r;j<=n;j++){
                if(a[l]>a[j]) break;
                if(!c[a[j]]) s.insert(a[j]);
                c[a[j]]--;
                if(!c[a[j]]) s.erase(a[j]);
                int last=C;
                if(!s.empty()) last=*s.begin();
                else res=max(res,j-lt+1+cnt[lt-1][j+1]);
                res=max(res,S[last-1]*2+(S[last]-S[last-1]+min(0LL,-c[last]))*2+r-l-1);
            }
        };
        for(int i=1;i<n;i++){
            if(i>1) query(i-1,i+1);
            query(i,i+1);
        }
    }
    return res;
}

void solve(){
    cin >> n >> C;
    for(int i=1;i<=n;i++) cin >> a[i];
    int ans=cal();
    for(int i=1;i<=n;i++) a[i]=C-a[i]+1;
    reverse(a+1,a+n+1);
    ans=max(ans,cal());
    for(int j=1;j<=C;j++) c[j]=0;
    for(int i=1;i<=n;i++){
        c[a[i]]++;
        ans=max(ans,c[a[i]]);
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
