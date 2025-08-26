#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int X,n,m;cin >> X >> n >> m;
    vector<int> a(n+1),b(m+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=m;i++) cin >> b[i];

    vector<int> h(n+1,m);
    for(int i=1,j=m;i<=n;i++){
        while(j && a[i]+b[j]>=X) j--;
        h[i]=j;
    }
    int cnt=0;
    for(int i=0;i<n;i++) cnt+=2*(h[i]>h[i+1]);

    int T=1;
    if(h[1]==m) cnt++;
    if(h[n]) cnt++,T=0;

    if(cnt==2){
        if(T) cout << 0 << '\n';
        else cout << 1 << '\n';
        return;
    }

    int x=0;
    while((1<<x)+T+1 < cnt) x++; 
    cout << x << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
