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
const long long inf=9e18;
const int mod=998244353;
const int maxn=200005;
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

void solve(){
    int n;cin >> n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++) cin >> b[i];
    int res=inf;
    for(int i=0;i<=30;i++){
        int l=0,r=inf;
        for(int j=0;j<n;j++){
            l=max(l,b[j]*(1<<i)-a[j]);
            r=min(r,(b[j]+1)*(1<<i)-a[j]);
        }
        if(l>=r) continue;

        int d=l/(1<<i);
        for(int k=0;k<=30;k++){
            int L=max(l,(d+k)*(1<<i));
            int R=min(r,(d+k+1)*(1<<i));
            if(L>=R) continue;
            R--;
            int X=L^R,cnt=0;
            for(int j=i-1;j>=0;j--){
                if(X>>j&1){
                    if(L%(1<<j)!=0) cnt++;
                    break;
                }
                cnt+=(L>>j&1);
            }
            res=min(res,cnt+d+k+i);
        }
    }
    cout << (res==inf?-1:res) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
