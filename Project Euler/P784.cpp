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
    vector<int> f(N+1);
    for(int i=2;i<=N;i++) if(!f[i]){
        for(int j=i;j<=N;j+=i) f[j]=i;
    }

    int res=0;
    for(int r=2;r<N;r++){
        if(r%1000==0) cout << r << endl;
        vector<pii> P;
        int x=r-1,y=r+1,k=0;
        while(x%2==0) x/=2,k++;
        while(y%2==0) y/=2,k++;
        if(k) P.push_back({2,k});
        while(x>1){
            int j=f[x];k=0;
            while(x%j==0) x/=j,k++;
            P.push_back({j,k});
        }
        while(y>1){
            int j=f[y];k=0;
            while(y%j==0) y/=j,k++;
            P.push_back({j,k});
        }

        int T=r*r-1;
        function<void(int,int)> dfs = [&](int i,int X){
            if(i==(int)P.size()){
                res+=X+T/X+2*r;
                return;
            }
            for(int j=0;j<=P[i].second;j++){
                if(j) X*=P[i].first;
                if(X*X>=T || r+X>N) break;
                dfs(i+1,X);
            }  
        };
        dfs(0,1);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
