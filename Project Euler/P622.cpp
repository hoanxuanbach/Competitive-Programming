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
    int A=(1LL<<(n/2))-1,B=A+2;

    vector<int> dA,dB;
    for(int i=1;i*i<=A;i++){
        if(A%i==0){
            dA.push_back(i);
            if(i*i!=A) dA.push_back(A/i);
        }
    }
    for(int i=1;i*i<=B;i++){
        if(B%i==0){
            dB.push_back(i);
            if(i*i!=B) dB.push_back(B/i);
        }
    }
    sort(dA.begin(),dA.end());
    sort(dB.begin(),dB.end());
    int res=0;
    for(int a:dA) for(int b:dB){
        int x=a*b;
        bool check=true;
        for(int i=1;i<n;i++) if(((1LL<<i)-1)%x==0) check=false;
        if(check) res+=x+1;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
