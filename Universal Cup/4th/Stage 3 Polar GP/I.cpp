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
    vector<int> p(n),q(n);
    for(int i=0;i<n;i++) cin >> p[i];
    for(int i=0;i<n;i++) cin >> q[i];

    vector<pair<int,int>> op;
    for(int x=n;x>=1;x--){
        int a=-1,b=-1;
        for(int i=0;i<n;i++) if(p[i]==x) a=i;
        for(int i=0;i<n;i++) if(q[i]==x) b=i;
        if(a<b){
            cout << "NO\n";
            return;
        }
        if(a==b) continue;
        vector<int> pos;
        for(int i=b;i<a;i++){
            if(p[i]>x) continue;
            if(pos.empty() || p[pos.back()]<p[i]) pos.push_back(i);
        }
        while(!pos.empty()){
            op.push_back({pos.back(),a});
            swap(p[a],p[pos.back()]);
            a=pos.back();pos.pop_back();
            
        }
    }
    cout << "YES\n";
    cout << (int)op.size() << '\n';
    for(auto [x,y]:op) cout << x+1 << ' ' << y+1 << '\n';
    assert(p==q);
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}