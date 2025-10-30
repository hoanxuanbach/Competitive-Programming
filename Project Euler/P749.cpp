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

    int X=1;
    for(int i=0;i<N;i++) X*=10;

    vector<int> a(10),b(10);

    int S=0;
    vector<int> f(10,1);
    auto g = [&](int x){
        if(x<0 || x>=X) return;
        int d=x;
        while(d) b[d%10]++,d/=10;
        bool check=true;
        for(int i=1;i<10;i++){
            if(b[i]!=a[i]) check=false;
            b[i]=0;
        }
        if(check) S+=x;
    };
    function<void(int,int,int)> dfs = [&](int n,int s,int d){
        if(!n) return;
        if(s+f[d]<=X){
            a[d]++;
            g(s+f[d]-1);
            g(s+f[d]+1);
            dfs(n-1,s+f[d],d);
            a[d]--;
        }
        if(d<9) dfs(n,s,d+1);
    };
    for(int k=1;k<=60;k++){
        for(int i=1;i<10;i++) f[i]=min(inf,f[i]*i);
        if(f[2]>=X) break;
        dfs(N,0,1);
    }
    cout << S << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
