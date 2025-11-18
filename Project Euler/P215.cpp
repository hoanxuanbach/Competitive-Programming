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
    int m,n;cin >> m >> n;

    int T=0;
    map<vector<int>,int> state;

    vector<int> cur;
    function<void(int)> dfs = [&](int i){
        if(i==n){
            if(state.find(cur)==state.end()) state[cur]=T++;
            return;
        }
        for(int k=1;k<=3;k++){
            if(i && cur.back()==k) continue;
            cur.push_back(k);
            dfs(i+1);
            cur.pop_back();
        }
    };
    dfs(0);

    vector<vector<int>> dp(m,vector<int>(T,0));
    vector<vector<int>> g(T);

    vector<int> lst;
    for(auto [v,x]:state){
        bool start=true;
        for(int k:v) if(k==1) start=false;
        if(start) dp[1][x]++;

        bool end=true;
        for(int k:v) if(k==2) end=false;
        if(end) lst.push_back(x);

        vector<int> nv=v;
        for(int i=0;i<n;i++) nv[i]--;
        function<void(int)> dfs2 = [&](int i){
            if(i==n){
                g[x].push_back(state[nv]);
                return;
            }
            if(!nv[i]){
                for(int k=2;k<=3;k++){
                    nv[i]=k;
                    if(i && nv[i]==nv[i-1]) continue;
                    dfs2(i+1);
                }
                nv[i]=0;
            }
            else if(!i || (nv[i]!=nv[i-1])) dfs2(i+1);
        };
        dfs2(0);
    }

    for(int i=1;i<m-2;i++) for(int x=0;x<T;x++) for(int y:g[x]) dp[i+1][y]+=dp[i][x];

    int res=0;
    for(int x:lst) res+=dp[m-2][x];
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
