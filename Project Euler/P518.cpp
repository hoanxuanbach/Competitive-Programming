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
    vector<int> p(N+1);
    for(int i=2;i<=N;i++) if(!p[i]){
        for(int j=i;j<=N;j+=i) p[j]=i;
    }
    vector<vector<int>> f(N+1);
    for(int i=2;i<N;i++) if(p[i]==i){
        int x=i+1,val=1;
        while(x>1){
            int j=p[x],k=0;
            while(x%j==0) x/=j,k^=1;
            if(k) val*=j;
        }
        f[val].push_back(i+1);
    }
    int T=0;
    for(int i=1;i<=N;i++){
        int sz=(int)f[i].size();
        for(int j=0;j<sz;j++) for(int k=j+1;k<sz;k++){
            int b=f[i][j]*f[i][k];
            int d=sqrtl(b);
            if(d*d!=b || p[d-1]!=d-1) continue;
            T+=f[i][j]+f[i][k]+d-3;
        }
    }
    cout << T << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
