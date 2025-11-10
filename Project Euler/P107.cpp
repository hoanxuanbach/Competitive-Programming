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
    int N=40;
    vector<array<int,3>> E;
    for(int i=0;i<N;i++){
        string S;cin >> S;
        int j=0,x=0;
        for(char c:S){
            if(c==','){
                if(x!=-1){
                    E.push_back({x,i,j});
                }
                x=0;j++;
            }
            else if(c=='-') x=-1;
            else x=x*10+c-'0';
        }
        assert(j==N-1);
        if(x!=-1) E.push_back({x,i,j});
    }
    sort(E.begin(),E.end());
    vector<int> p(N);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp = [&](int u){
        if(u!=p[u]) return p[u]=fp(p[u]);
        return u;
    };
    auto unite = [&](int u,int v){
        u=fp(u);v=fp(v);
        if(u==v) return false;
        p[v]=u;
        return true;
    };

    int res=0;
    for(auto [x,u,v]:E){
        if(u>v) continue;
        if(!unite(u,v)) res+=x;
    }
    cout << res << '\n';
}
 
signed main(){
    freopen("107.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
