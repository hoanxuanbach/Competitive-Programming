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
    int N;cin >> N;
    string S;cin >> S;

    int a=1,b=0,c=1;
    reverse(S.begin(),S.end());
    vector<int> X;
    X.push_back(1);
    for(char x:S){
        a*=3,b*=3; 
        if(x=='U') b-=2*c,c*=4;
        else if(x=='d') b+=c,c*=2;

        vector<int> nX;
        for(int d:X){
            if(x=='D') nX.push_back(d*3);
            else if(x=='U'){
                d=d*3-2;
                if(d%4==0) nX.push_back(d/4);
            }
            else{
                d=d*3+1;
                if(d%2==0) nX.push_back(d/2);
            }
        }
        swap(nX,X);
        X.push_back(1);
        //cout << a << ' ' << b << ' ' << c << '\n';
    }
    sort(X.begin(),X.end());

    cout << a << ' ' << b << ' ' << c << '\n';

    __int128 K=((__int128)(N*c)/a)*a;
    while((K+b)%c!=0 || (K+b)/c<=N) K+=a;
    K=(K+b)/c;
    cout << (int)K << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
