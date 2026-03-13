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

void solve(){
    int N;cin >> N;
    int M=sqrtl(N),S=1;
    while(S<M) S<<=1;

    vector<int> f(S),p;
    for(int i=2;i<S;i++) if(!f[i]){
        p.push_back(i);
        for(int j=i*2;j<S;j+=i) f[j]=i;
    }

    int res=0;
    M=(int)p.size();

    int e=0;
    function<void(int,int,int)> dfs = [&](int x,int d,int s){
        int mx=sqrtl(N/x);
        for(int i=s+1;i<M && p[i]<=mx;i++) dfs(x*p[i],d^p[i],i);
        e++;
        if(e%1000000==0) cout << e << endl;
        if(s==-1 || (d>p[s] && d<S && !f[d])){
            if(s!=-1) x*=d;
            if(x<=N){
                int k=sqrtl(N/x);
                res=(res+(__int128)x*k*(k+1)*(2*k+1)/6)%mod;
            }
        }
    };
    dfs(1,0,-1);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
