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
    int n;cin >> n;
    string S;cin >> S;
    int cnt=0;
    for(int i=n-1;i>=0;i--){
        cnt+=(S[i]=='A'?1:-1);
        if(cnt>0){
            cout << "Alice\n";
            return;
        }
    }
    cout << "Bob\n";
}
 
signed main(){
    freopen("A.inp","r",stdin);
    freopen("A.txt","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    for(int t=1;t<=test;t++){
        cout << "Case #" << t << ": ";
        solve();
    }
}
