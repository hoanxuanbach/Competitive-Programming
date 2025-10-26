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
const int maxn=300005;
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

int n,a[maxn],s[maxn];
vector<pair<double,int>> P;

void solve(){
    cin >> n;
    for(int _=0;_<3;_++){
        int m=0;
        for(int i=0;i<=n;i++){
            cin >> a[i];
            while(m>1 && (a[s[m]]-a[i])*(s[m]-s[m-1])<=(a[s[m-1]]-a[s[m]])*(i-s[m])) m--;
            s[++m]=i;
        }
        for(int i=2;i<=m;i++) P.push_back({(double)(a[s[i-1]]-a[s[i]])/(s[i]-s[i-1]),s[i]-s[i-1]});
    }
    sort(P.begin(),P.end());
    P.push_back({inf,0});
    vector<bool> f(3*n+1);
    int cur=0;f[0]=1;
    for(int i=0;i<(int)P.size()-1;i++){
        cur+=P[i].se;
        if(P[i].fi!=P[i+1].fi) f[cur]=1;
    }
    int cnt=0;
    for(int i=0;i<=3*n;i++) cnt+=!f[i];
    cout << cnt << '\n';
    for(int i=0;i<=3*n;i++) if(!f[i]) cout << i << ' ';
    cout << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
