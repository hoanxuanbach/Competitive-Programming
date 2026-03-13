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
    int n,M,T;cin >> n >> M >> T;

    int res=0,sz=0;
    vector<int> S(n+1),f(n+1);
    f[0]=-1;
    
    auto add = [&](int x){
        sz++;
        S[sz]=x;
        int j=f[sz-1];
        while(j>=0 && S[j+1]!=S[sz]) j=f[j];
        f[sz]=j+1;
    };
    auto is_minimal = [&](){
        int d=sz-f[sz];
        if(sz%d!=0 || d==sz || d>sz/2) return true;
        else return false;
    };
    function<void(int,int,int,int,int)> dfs = [&](int i,int p,int q,int r,int s){
        if(i){
            if(abs(s+p)<=1 && is_minimal()) res++;
        }
        if(i==4) cout << S[1] << ' ' << S[2] << ' ' << S[3] << ' ' << S[4] << endl; 
        if(i==n || abs(p)>T || abs(r)>T) return;
        for(int x=0;x<=M;x++){
            int np=p*x+q,nq=-p,nr=r*x+s,ns=-r;
            add(x);
            dfs(i+1,np,nq,nr,ns);
            sz--;
        }
        if(i==4) cout << res << endl;
    };
    dfs(0,1,0,0,1);
    cout << res << '\n';
}
/*
1 1 7 0
3796266
*/
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
