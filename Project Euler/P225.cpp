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
    int res=0,T=124;
    
    int X=27;
    while(true){
        cout << X << ' ' << T << endl;
        int a=1,b=1,c=1;
        set<array<int,3>> S;
        while(S.find({a,b,c})==S.end()){
            S.insert({a,b,c});
            swap(a,b);
            swap(b,c);
            c=(c+a+b)%X;
            if(!c) break;
        }
        if(c){
            res+=X;T--;
            if(!T){
                cout << X << '\n';
                return;
            }
        }
        X+=2;
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
