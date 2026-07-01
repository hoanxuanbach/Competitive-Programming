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
#define ld long double
void solve(){
    vector<ld> f(2);f[1]=1;
    vector<int> T={4,6,8,12,20};
    for(int x:T){
        int s=(int)f.size();
        int m=(s-1)*x+1;
        vector<ld> g(m),h(m);g[0]=1;
        for(int i=1;i<s;i++){
            ld total=0;
            for(int j=i*x;j>=0;j--){
                if(j>=x) total+=g[j-x];
                total-=g[j];
                g[j]=total/x;
                h[j]+=f[i]*g[j];
            }
        }
        swap(f,h);
    }
    ld K=0;
    for(int i=0;i<(int)f.size();i++) K+=f[i]*i;
    ld res=0;
    for(int i=0;i<(int)f.size();i++) res+=f[i]*(i-K)*(i-K);
    cout << setprecision(4) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
