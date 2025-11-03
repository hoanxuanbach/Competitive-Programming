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
    int total=0;
    for(int x:{1,2}) for(int d:{-1,1}){
        for(int k=1;x*k*k+d<=N;k++){
            int A=x*k*k+d;
            int S=4*A*A-(A+d)*(A+d);
            //cout << '*' << x << ' ' << k << ' ' << d << ' ' << A << ' ' << S << '\n';
            int s=sqrtl(S);
            if(s*s!=S) continue;
            s*=(A+1);
            if(s%4==0 && min(A,A+d)>0){
                if(3*A+d<=N) total+=3*A+d;
                //cout << A << ' ' << A << ' ' << A+d << '\n';
            }
        }
    }
    cout << total << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
