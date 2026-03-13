#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 888888883;
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
    vector<int> a(50*N);

    a[0]=88888888;
    for(int i=1;i<50*N;i++) a[i]=a[i-1]*8888%mod;
    
    map<vector<int>,int> mp;
    for(int i=0;i<N;i++){
        string s;
        for(int j=0;j<50;j++) s+=char('x'+a[i*50+j]%3);
        vector<int> f(3);
        int cnt=0;
        for(char c:s){
            for(int k=c-'x'+1;k<3;k++) cnt^=f[k];
            f[c-'x']^=1;
        }
        f.push_back(cnt);
        mp[f]++;
    }

    int res=0;
    for(auto [x,dx]:mp) for(auto [y,dy]:mp){
        vector<int> f(3);
        for(int i=0;i<3;i++) f[i]=x[i]^y[i];
        int cnt=x[3]^y[3];
        for(int i=0;i<3;i++) for(int j=0;j<i;j++) cnt^=(x[i]&y[j]);
        if(f[0]==f[1] && f[1]==f[2] && (cnt^f[0])==0) res+=dx*dy;
    }

    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
