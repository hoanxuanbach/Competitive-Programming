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
    int N;cin >> N;
    vector<int> f(N+1,0);
    vector<vector<int>> g(N+1,vector<int>(4,0));

    map<int,vector<int>> mp;
    for(int i=1;i<=N;i++){
        for(int x=0;x<=3;x++){
            vector<int> S;
            for(int j=0;j<i;j++){
                for(int d=0;d<=3;d++){
                    if(j==0 && d!=3) continue;
                    if(j==i-1 && (d^x)!=3) continue;
                    S.push_back(g[j][d]^g[i-j-1][x^d]);
                }
            }
            sort(S.begin(),S.end());
            S.erase(unique(S.begin(),S.end()),S.end());
            while(g[i][x]<(int)S.size() && S[g[i][x]]==g[i][x]) g[i][x]++;
        }

        vector<int> S;
        for(int j=0;j<i;j++){
            for(int d=0;d<=3;d++){
                if(j==0 && d!=3) continue;
                S.push_back(g[j][d]^f[i-j-1]);
            }
        }
        sort(S.begin(),S.end());
        S.erase(unique(S.begin(),S.end()),S.end());
        while(f[i]<(int)S.size() && S[f[i]]==f[i]) f[i]++;
        
        int T=0;
        for(int j=0;j<i;j++) T|=(1<<(f[j]^f[i-j-1]));
        mp[T].push_back(i);
    }
    for(auto [x,v]:mp){
        for(int k=1;k<16;k++){
            int y=0;
            for(int i=0;i<16;i++) if(x>>i&1) y|=1<<(i^k);

            if(mp.find(y)!=mp.end()){
                cout << x << ' ' << y << ' ' << k << '\n';
            }
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
