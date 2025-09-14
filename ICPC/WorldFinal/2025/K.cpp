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
    int n,m,k,X,Y;cin >> n >> m >> k >> X >> Y;Y+=n;
    vector<vector<pii>> g(n+m+1);
    for(int i=1;i<=k;i++){
        int x,y,d;cin >> x >> y >> d;y+=n;
        g[x].push_back({y,d});
        g[y].push_back({x,d});
    }
    vector<int> A(n+m+1);
    vector<bool> vis(n+m+1);

    bool check=true;
    for(int i=1;i<=n+m;i++){
        if(!vis[i]){
            vector<int> S,T;
            function<void(int)> dfs = [&](int u){
                vis[u]=true;
                if(u>n) T.push_back(u);
                else S.push_back(u);
                for(auto [v,w]:g[u]){
                    if(!vis[v]){
                        A[v]=w-A[u];
                        dfs(v);
                    }
                    else if((A[u]+A[v])!=w) check=false;
                }
            };
            dfs(i);
            if(!check){
                cout << "impossible\n";
                return;
            }
            if(S.empty() || T.empty()) continue;
            bool fX=false,fY=true;
            for(int u:S) if(u==X) fX=true;
            for(int u:T) if(u==Y) fY=true;

            if(fX){
                int d=inf;
                for(int u:S) d=min(d,A[u]);
                for(int u:S) A[u]-=d;
                for(int u:T) A[u]+=d;
            }
            else{
                int d=inf;
                for(int u:T) d=min(d,A[u]);
                for(int u:T) A[u]-=d;
                for(int u:S) A[u]+=d;
            }
            for(int u:S) if(A[u]<0) check=false;
            for(int u:T) if(A[u]<0) check=false;
            if(!check){
                cout << "impossible\n";
                return;
            }
        }
    }
    cout << A[X]+A[Y] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
