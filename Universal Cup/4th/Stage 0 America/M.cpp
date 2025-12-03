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
    int n,k;cin >> n >> k;
    vector<int> s(n),f(n+1);
    for(int i=0;i<n;i++) cin >> s[i];
    while(k){
        int d=--k;
        sort(s.begin(),s.end());
        s.erase(s.begin(),upper_bound(s.begin(),s.end(),0));
        int m=(int)s.size();
        if(m<=1) break;
        for(int i=1;i<m;i++){
            s[i]-=s[i-1];
            if(s[i-1]) d=min(d,s[i]/s[i-1]);
        }
        if(d){
            f[0]=1;
            for(int i=1;i<=m;i++) f[i]=-f[i-1]*(d+i-1)/i;
            for(int i=m-1;i>=0;i--) for(int j=1;j<=i;j++) s[i]+=f[j]*s[i-j];
            k-=d;
        }
    }
    int m=(int)s.size();
    for(int i=0;i<n-m;i++) cout << 0 << ' ';
    for(int i=0;i<m;i++) cout << s[i] << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
