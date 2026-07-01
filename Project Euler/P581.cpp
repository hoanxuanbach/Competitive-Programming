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

vector<int> S={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};

void solve(){
    int N;cin >> N;

    int res=0;
    function<void(int,int)> dfs = [&](int i,int x){
        if(i==(int)S.size()){
            int k=x+1;
            for(int d:S) while(k%d==0) k/=d;
            if(k==1) res+=x;
            return;
        }
        for(int j=0;x<=N;j++){
            dfs(i+1,x);
            x*=S[i];
        }
    };
    dfs(0,1);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
