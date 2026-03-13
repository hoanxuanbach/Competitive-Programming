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
    int A,B,m;cin >> A >> B >> m;
    
    vector<int> fA(A+1),fB(B+1);
    vector<vector<int>> g(B+1);

    for(int i=1;i<=m;i++){
        int a,b;cin >> a >> b;
        g[b].push_back(a);
    }

    int res=0;
    for(int r=1;r<=B;r++){

        int T=r;
        vector<int> f(B+1);
        function<bool(int)> dfs = [&](int x){
            T=min(T,x);
            for(int v:g[x]){
                if(!fA[v]){
                    fB[x]=v;
                    fA[v]=x;
                    return true;
                }
                else if(!f[fA[v]]){
                    int u=fA[v];
                    f[u]=x;
                    if(dfs(u)){
                        fB[x]=v;
                        fA[v]=x;
                        return true;
                    }
                }
            }
            return false;
        };
        f[r]=-1;
        if(!dfs(r) && T!=r){
            vector<int> S;
            while(T!=r){
                S.push_back(T);
                T=f[T];
            }
            while(!S.empty()){
                int x=S.back();S.pop_back();
                fB[T]=fB[x];fA[fB[T]]=T;T=x;
            }
            fB[T]=0;
        }

        int cnt=0;
        for(int l=r;l>=1;l--){
            if(fB[l]) cnt++;
            (res+=cnt*l*r*((l^r)+1))%=mod;
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}