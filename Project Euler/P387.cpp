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
    vector<int> X;
    function<void(int,int)> dfs = [&](int x,int d){
        if(x>N) return;
        X.push_back(x);
        for(int i=0;i<=9;i++) if((x*10+i)%(d+i)==0) dfs(x*10+i,d+i);
    };
    for(int i=1;i<=9;i++) dfs(i,i);
    //cout << (int)X.size() << '\n';
    
    vector<int> Y;
    for(int xx:X){
        int d=0,x=xx;
        while(x) d+=x%10,x/=10;
        x=xx/d;
        if(x==1) continue;
        bool check=false;
        for(int i=2;i*i<=x;i++){
            if(x%i==0){
                check=true;
                break;
            }
        }
        if(!check) Y.push_back(xx);
    }

    int T=0;
    //cout << (int)Y.size() << '\n';
    for(int xx:Y) for(int k=0;k<=9;k++){
        int x=xx*10+k;
        if(x>N) continue;
        bool check=false;
        for(int i=2;i*i<=x;i++) if(x%i==0){
            check=true;
            break;
        }
        if(!check){
            T+=x;
            //cout << x << '\n';
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
