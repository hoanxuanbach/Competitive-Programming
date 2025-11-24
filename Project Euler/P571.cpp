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

bool f(int X,int d){
    int all=(1<<d)-1,used=0;
    while(X){
        int k=X%d;X/=d;
        used|=(1<<k);
    }
    return (used==all);
}

void solve(){
    int B=12,T=10,res=0;
    vector<int> P={1,0,2,3,4,5,6,7,8,9,10,11};
    do{
        int X=0;
        for(int i=0;i<B;i++) X=X*B+P[i];
        if(!f(X,8)) continue;
        bool ok=true;
        for(int i=B-1;i>1;i--) if(!f(X,i)){
            ok=false;
            break;
        }
        if(ok){
            cout << X << endl;
            T--;
            res+=X;
            if(!T){
                cout << res << '\n';
                return;
            }
        }
    }while(next_permutation(P.begin(),P.end()));
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
