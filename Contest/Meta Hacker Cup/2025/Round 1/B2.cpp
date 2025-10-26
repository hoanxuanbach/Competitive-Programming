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

const int K=60;
void solve(){
    int n,a,b;cin >> n >> a >> b;

    vector<int> d(K);d[0]=1;
    for(int i=1;i<K;i++) d[i]=(n+i-1)%mod*d[i-1]%mod*power(i,mod-2)%mod;

    vector<pair<int,int>> p;
    for(int i=2;i*i<=b;i++){
        if(b%i==0){
            int x=0;
            while(b%i==0) b/=i,x++;
            p.push_back({i,x});
        }
    }
    if(b>1) p.push_back({b,1});

    int res=0;
    function<void(int,int,int)> dfs = [&](int i,int x,int val){
        if(i==(int)p.size()){
            res=(res+val)%mod;
            return;
        }
        for(int j=0;j<=p[i].second;j++){
            if(x>a) break;
            dfs(i+1,x,val*d[j]%mod*d[p[i].second-j]%mod);
            if(j<p[i].second) x*=p[i].first;
        }
    };
    dfs(0,1,1);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    for(int t=1;t<=test;t++){
        cout << "Case #" << t << ": ";
        solve();
    }
}
