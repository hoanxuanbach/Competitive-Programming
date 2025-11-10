#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
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
    
    int S;cin >> S;
    int res=0;
    vector<int> p(S);

    for(int i=2;i<S;i++) if(!p[i]){
        for(int j=i*i;j<S;j+=i) p[j]=1;
        if(i<=5){
            res+=i;
            continue;
        }

        int x=10%i;
        set<int> ss;
        while(x!=1 && ss.find(x)==ss.end()){
            ss.insert(x);
            x=power(x,10,i);
        }
        if(x!=1) res+=i;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
