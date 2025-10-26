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

vector<string> X = {"one","two","three","four","five","six","seven","eight","nine","ten",
                    "eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
                    
vector<string> Y = {"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};

void solve(){

    int total=0;
    int cur=0,cnt=0;
    for(int i=0;i<9;i++) cnt+=(int)X[i].length();
    for(int i=0;i<8;i++) cur+=(int)Y[i].length();
    total=cur*10+cnt*8;

    for(int i=0;i<19;i++) total+=(int)X[i].length();
    total*=10;
    total+=(cnt+90)*99+cnt+63;
    cout << (total+11) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
