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
    int N,T;cin >> N >> T;
    N=(1LL<<N);T--;
    vector<int> f(N),p(N);
    for(int i=2;i<N;i++){
        if(i%1000000==0) cout << i/1000000 << endl;
        if(i&1){
            for(int j=3;j<=i;j+=2){
                int x=0,d=i,a=j;
                while(d){
                    if(d&1) x^=a;
                    a<<=1;d>>=1;
                }
                if(x>=N) break;
                f[x]=true;
            }
        }
        if(!f[i] && (i&1)){
            T--;
            //cout << i << '\n';
            if(!T){
                cout << i << '\n';
                return;
            }
        }
    }
    cout << T << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
