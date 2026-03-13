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
const int L = 30;
void solve(){
    int K;cin >> K;
    while(true){
        int n=rand_int(0,5)+15,m=4*n;
        vector<int> f(m+1);f[0]=1;
        vector<int> a(n);
        for(int i=0;i<n;i++){
            a[i]=rand_int(1,4);
            for(int j=m;j>=a[i];j--) f[j]+=f[j-a[i]];
        }
        for(int i=1;i<=m && (int)a.size()<L;i++){
            if(f[i] && f[0]+f[i]<=K){
                a.push_back(-i);
                for(int j=0;j<=m-i;j++) f[j]+=f[j+i];
            }
        }
        if(f[0]==K){
            cout << (int)a.size() << '\n';
            for(int x:a) cout << x << ' ';
            cout << '\n';
            return;
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
