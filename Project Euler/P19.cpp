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

vector<int> days = {31,28,31,30,31,30,31,31,30,31,30,31};

void solve(){

    int x=0,cnt=0;
    for(int y=1900;y<=2000;y++) for(int m=0;m<12;m++){
        if(x==6 && y>1900) cnt++;
        x=(x+days[m])%7;
        if(m==1 && y%4==0 && (y%400==0 || y%100!=0)) x=(x+1)%7;
    }
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
