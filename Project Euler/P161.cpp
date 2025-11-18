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
    int n,m;cin >> n >> m;
    
    int T=0;
    map<pii,int> mp;
    auto add = [&](int x,int y){
        mp[{x,y}]=T++;
    };
    for(int x=0;x<(1<<n);x++){
        for(int y=x;;y=(y-1)&x){
            add(x,y);
            if(y==0) break;
        }
    }

    vector<vector<int>> g(T);
    function<void(int,int,int,int,int)> dfs = [&](int i,int x,int y,int z,int u){
        if(i==n){
            if(x==(1<<n)-1){
                int v=mp[{y,z}];
                g[u].push_back(v);
                //cout << u << ' ' << y << ' ' << z << '\n';
            }
            return;
        }          
        if(i>=2 && !(x>>i&1) && !(x>>(i-1)&1) && !(x>>(i-2)&1)){
            dfs(i+1,x|(7<<(i-2)),y,z,u);
        }
        if(i>=1 && !(x>>i&1) && !(x>>(i-1)&1)){
            if(!(y>>i&1)) dfs(i+1,x|(3<<(i-1)),y|(1<<i),z,u);
            if(!(y>>(i-1)&1)) dfs(i+1,x|(3<<(i-1)),y|(1<<(i-1)),z,u);
        }
        if(i>=1 && !(y>>i&1) && !(y>>(i-1)&1)){
            if(!(x>>i&1)) dfs(i+1,x|(1<<i),y|(3<<(i-1)),z,u);
            if(!(x>>(i-1)&1)) dfs(i+1,x|(1<<(i-1)),y|(3<<(i-1)),z,u);
        }
        if(!(x>>i&1)) dfs(i+1,x|(1<<i),y|(1<<i),z|(1<<i),u);
        dfs(i+1,x,y,z,u);
    };
    for(int x=0;x<(1<<n);x++){
        for(int y=x;;y=(y-1)&x){
            //cout << "jmp " << x << ' ' << y << '\n';
            dfs(0,x,y,0,mp[{x,y}]);
            if(y==0) break;
        }
    }

    vector<int> f(T);
    f[0]=1;
    for(int i=1;i<=m;i++){
        vector<int> nf(T);
        for(int u=0;u<T;u++) for(int v:g[u]) nf[v]+=f[u];
        swap(f,nf);
    }
    cout << f[0] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
