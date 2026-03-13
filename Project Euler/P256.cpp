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

int cnt[100000005];
void solve(){
    int N;cin >> N;
    for(int a=1;a<=N;a++) for(int k=1;(a+1)*k+2<=min((a-1)*(k+1)-2,N/a);k++){
        for(int b=(a+1)*k+2;b<=min(N/a,(a-1)*(k+1)-2);b++) if(!(a&b&1)) cnt[a*b]++;
    }
    for(int i=0;i<=N;i++) if(cnt[i]==200){
        cout << i << '\n';
        return;
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
