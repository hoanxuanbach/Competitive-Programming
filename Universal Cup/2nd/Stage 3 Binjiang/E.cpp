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

bool vis[45][45];
int block[45][45];

void solve(){
    int n;cin >> n;
    string S;cin >> S;
    for(int i=0;i<=2*n;i++) for(int j=0;j<=2*n;j++) block[i][j]=3;
    block[n][n]=1;
    function<void(int,int,int)> dfs = [&](int i,int x,int y){
        //cout << "dfs " << i << ' ' << x << ' ' << y << '\n';
        if(i==n){vis[x][y]=true;return;}
        int nx=x,ny=y;
        if(S[i]=='L') nx--;
        else if(S[i]=='R') nx++;
        else if(S[i]=='U') ny++;
        else ny--;
        for(int j=0;j<=1;j++){
            int cur=block[nx][ny];
            if(block[nx][ny]>>j&1){
                block[nx][ny]=(1<<j);
                if(j) dfs(i+1,x,y);
                else dfs(i+1,nx,ny);
                block[nx][ny]=cur;
            }
        }
    };
    dfs(0,n,n);
    vector<pii> ans;
    for(int i=0;i<=2*n;i++) for(int j=0;j<=2*n;j++) if(vis[i][j]) ans.push_back({i-n,j-n});
    cout << (int)ans.size() << '\n';
    for(auto [x,y]:ans) cout << x << ' ' << y << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
