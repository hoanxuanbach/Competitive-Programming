#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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

const int N = 25;
const int K = 6;

void solve(){
    int n,m,q;cin >> n >> m >> q;
    vector<vector<int>> c(n,vector<int>(m));
    for(int i=0;i<n;i++) for(int j=0;j<m;j++){
        char ch;cin >> ch;
        c[i][j]=(ch=='#');
    }

    vector<int> ans(q);
    vector<vector<array<int,3>>> qq(K);
    for(int i=0;i<q;i++){
        int x,y,k;cin >> x >> y >> k;
        qq[k].push_back({x,y,i});
    }

    vector<vector<vector<int>>> d(n,vector<vector<int>>(m,vector<int>(K,0)));
    for(int i=n-1;i>=0;i--) for(int j=0;j<m;j++){
        if(c[i][j]) continue;
        d[i][j][0]=1;
        if(i+1<n) d[i][j][0]+=d[i+1][j][0]; 
    }
    for(int k=1;k<K;k++){
        for(int i=n-1;i>=0;i--) for(int j=0;j<m;j++){
            d[i][j][k]=1;
            if(i+1<n) d[i][j][k]+=d[i+1][j][k-c[i][j]];
        }
    }

    for(int k=0;k<K;k++){
        //cout << '*' << k << '\n';
        vector<vector<pair<int,int>>> f(n+1),g(n+1);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                //cout << d[i][j][k] << ' ';
                f[d[i][j][k]].push_back({i,j});
            }
            //cout << '\n';
        }
        for(auto [x,y,id]:qq[k]) g[x].push_back({y,id});

        vector<int> bit(m+1),cnt(m+1);
        auto update = [&](int x,int delta){
            for(int i=m-x+1;i<=m;i+=(i&(-i))){
                bit[i]+=x*delta;
                cnt[i]+=delta;
            }
        };
        auto query = [&](int x){
            x=m-x+1;
            pair<int,int> res={0,0};
            for(int i=x;i>=1;i-=(i&(-i))){
                res.first+=bit[i];
                res.second+=cnt[i];
            }
            return res;
        };

        vector<int> cc(n*m),sz(n*m),p(n*m);
        iota(p.begin(),p.end(),0);
        function<int(int)> fp = [&](int u){
            if(u!=p[u]) return p[u]=fp(p[u]);
            return u;
        };
        auto unite = [&](int u,int v){
            u=fp(u);v=fp(v);
            if(u==v) return;
            update(sz[u],-1);
            update(sz[v],-1);
            if(sz[u]<sz[v]) swap(u,v);
            p[v]=u;sz[u]+=sz[v];
            update(sz[u],1); 
        };

        for(int i=n;i>=1;i--){
            for(auto [x,y]:f[i]){
                //cout << "add " << x << ' ' << y << '\n';
                int t=x*m+y;
                cc[t]=1;sz[t]=1;
                update(sz[t],1);
                if(y && cc[t-1]) unite(t,t-1);
                if(y+1<m && cc[t+1]) unite(t,t+1);
            }
            for(auto [x,id]:g[i]){
                //cout << "query " << x << ' ' << id << '\n';
                pair<int,int> cur=query(x);
                ans[id]=cur.first-(x-1)*cur.second;
            }
        }
    }

    for(int i=0;i<q;i++) cout << ans[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
/*
3 3 6        
..#
#..
...
1 1 0
1 2 1
2 1 1
3 1 1
2 2 0
3 3 1

5 5 4
.#.##
..#..
...#.
#.#.#
.#...
3 3 2
2 2 1
3 1 0
2 3 2
*/
