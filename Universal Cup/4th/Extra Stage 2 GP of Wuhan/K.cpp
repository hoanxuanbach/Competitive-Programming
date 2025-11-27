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

    vector<vector<int>> g(n+1);
    vector<vector<pii>> f(n+1);
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++) cin >> b[i];
    for(int i=0;i<n;i++){
        if(a[i]==b[i]) continue;
        g[a[i]].push_back(i);
        g[b[i]].push_back(i);
    }
    for(int i=1;i<=n;i++){
        if((int)g[i].size()%2==1){
            cout << -1 << '\n';
            return;
        }
        for(int j=0;j<(int)g[i].size();j+=2){
            int x=g[i][j],y=g[i][j+1];
            f[x].push_back({y,i});
            //cout << "add " << x << ' ' << y << ' ' << i << endl;
        }
    }
    int cost=0;
    vector<pii> op;
    auto mv = [&](int x,int y){
        cost+=abs(x-y);
        //cout << "mv " << x << ' ' << y << endl;
        op.push_back({x,y});
        swap(a[x],b[y]);
    };
    auto add = [&](int x,int y,int val){
        if(a[x]==val){
            if(b[y]==val) mv(y,y);
            mv(x,y);
        }
        else if(b[x]==val){
            if(a[y]==val) mv(y,y);
            mv(y,x);
        }
    };
    for(int i=0;i<n;i++){
        if(a[i]==b[i]) continue;
        assert((int)f[i].size()==2);
        pii x=f[i][0],y=f[i][1];
        if(x<y) swap(x,y);
        //cout << x.first << ' ' << x.second << ' ' << y.first << ' ' << y.second << endl;
        add(y.first,i,y.second);
        if(x!=y) f[y.first].push_back(x);
    }
    cout << cost << ' ' << (int)op.size() << '\n';
    for(auto [x,y]:op) cout << x+1 << ' ' << y+1 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}