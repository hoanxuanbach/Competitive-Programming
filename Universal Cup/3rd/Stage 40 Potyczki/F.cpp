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
    int n;cin >> n;
    vector<int> p(n+1);
    for(int i=1;i<=n;i++) cin >> p[i];
    vector<array<int,3>> ans;

    auto f = [&](int x,int y,int t){
        ans.push_back({x,y,t});
        if(t) p[x]+=p[y];
        else p[x]-=p[y];
    };

    auto g = [&](int a,int b,int c){
        while((p[a]+p[b])<p[c]){
            if(p[a]<p[b]) f(a,b,1);
            else f(b,a,1);
        }
        while(p[a]>1 || p[b]>1){
            while(p[c]>p[b]) f(c,b,0);
            if(p[a]>p[b]) f(a,b,0);
            else f(b,a,0);
        }
        while(p[c]>1) f(c,b,0);
    };

    int x=0,y=0;
    for(int i=1;i<=n;i++) if(p[i]==1) x=i;
    y=(x>1?x-1:x+1);
    while(p[y]>p[x]) f(y,x,0);
    if(x>y) swap(x,y);
    for(int i=y;i<n;i++) g(i-1,i,i+1);
    for(int i=x;i>1;i--) g(i+1,i,i-1);
    for(int i=1;i<n;i++) f(i+1,i,1);

    cout << (int)ans.size() << '\n';
    for(auto [x,y,t]:ans) cout << x << ' ' << "-+"[t] << ' ' << y << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
