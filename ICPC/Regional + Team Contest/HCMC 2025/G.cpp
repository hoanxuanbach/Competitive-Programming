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

const int N=1e14;
vector<int> X;
void init(){
    auto cal = [&](int x){
        int s=sqrtl(x),res=0;
        for(int i=1;i<s;i++) res+=2*(x/i);
        for(int i=s;i<=x/s;i++) res+=x/i;
        res-=(x/s)*(s-1);
        return res;
    };
    X={4,8};
    vector<int> F={cal(4),cal(8)};

    int k=0;
    while(X.back()<=N){
        while(F[k]<X.back()){
            k++;
            if(k==(int)F.size()) F.push_back(cal(X[k]));
        }
        X.push_back(X.back()+X[k]);
    }
}
 
void solve(){
    int n,x;cin >> n >> x;
    if(n%2==1) n=1;
    else if(n%4==2) n=2;
    else{
        for(int i=(int)X.size()-1;i>=0;i--){
            if(n>X[i]) n-=X[i];
            else if(n==X[i]) break;
        }
    }
    cout << (x>=n?"First":"Second") << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    init();
    int test=1;cin >> test;
    while(test--) solve();
}
