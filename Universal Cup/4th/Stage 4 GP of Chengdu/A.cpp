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
    int n;cin >> n;
    vector<int> b(n);
    int L=0,R=0,S=0;

    int X=10000;
    for(int i=0;i<n;i++){
        cin >> b[i];b[i]*=100;
        L+=max(b[i]-50,0LL);
        R+=min(b[i]+50,X);
        S+=b[i];
    }
    if(n==1){
        if(b[0]!=10000) cout << "No\n";
        else cout << "Yes\n1\n";
        return;
    }
    if(X<L || X>=R){
        cout << "No\n";
        return;
    }
    if(S>=X){
        for(int i=0;i<n;i++){
            int k=min({b[i],50LL,S-X});
            b[i]-=k;S-=k;
        }
    }
    else{
        vector<int> lim(n);
        for(int i=0;i<n;i++){
            lim[i]=min(X,b[i]+49);
            int k=min(lim[i]-b[i],X-S);
            b[i]+=k;S+=k;
        }
        while(S<X){
            S*=10;X*=10;
            for(int i=0;i<n;i++){
                b[i]*=10;
                lim[i]=min(X,lim[i]*10+9);
                int k=min({lim[i]-b[i],X-S});
                b[i]+=k;S+=k;
            }
        }
    }
    cout << "Yes\n";
    for(int i=0;i<n;i++) cout << b[i] << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}