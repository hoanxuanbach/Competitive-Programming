#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 999999937;
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
    vector<vector<pii>> g(n+1);

    ifstream fbed("beds.txt");
    ifstream fdesk("desks.txt");

    string ss;
    while(fbed >> ss){
        int x=0,y=0;
        bool mid=false;
        for(char c:ss){
            if(c==',') mid=true;
            else if(!mid) x=10*x+c-'0';
            else y=10*y+c-'0';
        }
        g[x].push_back({y,0});
        g[y].push_back({x,0});
    }
    while(fdesk >> ss){
        int x=0,y=0;
        bool mid=false;
        for(char c:ss){
            if(c==',') mid=true;
            else if(!mid) x=10*x+c-'0';
            else y=10*y+c-'0';
        }
        g[x].push_back({y,1});
        g[y].push_back({x,1});
    }

    int cnt=0;
    vector<int> f(n+1);
    function<void(int)> dfs = [&](int u){
        f[u]=cnt;
        for(auto [v,w]:g[u]) if(!f[v]) dfs(v);
    };
    for(int i=1;i<=n;i++) if(!f[i]) cnt++,dfs(i);

    vector<array<int,3>> S(cnt+1,{0,0,0});
    for(int i=1;i<=n;i++) S[f[i]][2]++;
    for(int u=1;u<=n;u++) for(auto [v,k]:g[u]) if(u<v) S[f[u]][k]++;

    map<array<int,3>,int> mp;
    for(int i=1;i<=cnt;i++) mp[S[i]]++;
    
    int res=1;
    for(auto [x,k]:mp){
        for(int i=1;i<=k;i++) res=res*i%mod;
        if(x[0]+x[1]==x[2]){
            for(int i=1;i<=k;i++) res=res*x[2]%mod;
        }
        else{
            if(x[0]!=x[1]){
                for(int i=1;i<=k;i++) res=res*2%mod;
            }
        }
    }
    cout << res << '\n';
}
/*
36 
13
2 13    
4 30
5 27
6 16
10 18
12 35
14 19
15 20
17 26
21 32
22 33
24 34
25 28
13
1 35
2 22
3 36
4 28
5 25
7 18
9 23
13 19
14 33
15 34
20 24
26 29
27 30
*/
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
