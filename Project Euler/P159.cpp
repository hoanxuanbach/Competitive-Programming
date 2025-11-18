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
    vector<int> cnt(N);
    for(int i=1;i<N;i++){
        int x=i;
        while(x) cnt[i]+=x%10,x/=10;
        cnt[i]=cnt[cnt[i]];
    }
    vector<vector<int>> d(N);
    for(int i=2;i<N;i++) for(int j=i;j<N;j+=i) d[j].push_back(i);

    int res=0;
    vector<int> f(N);
    for(int i=2;i<N;i++){
        f[i]=cnt[i];
        for(int x:d[i]) f[i]=max(f[i],f[i/x]+cnt[x]);
        res+=f[i];
    }
    cout << f[24] << '\n';
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
