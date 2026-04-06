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

const int M = 20000;
const int T = 104;

map<pii,int> f;
int dx[] = {0,1,0,-1},
    dy[] = {1,0,-1,0};

void solve(){
    int N;cin >> N;

    int X=0,Y=0,k=0;
    vector<int> S;
    for(int i=0;i<M;i++){
        f[{X,Y}]^=1;
        if(f[{X,Y}]) k=(k+1)%4,S.push_back(1);
        else k=(k+3)%4,S.push_back(-1);
        X+=dx[k],Y+=dy[k];
    }

    N-=M;
    int res=0;
    for(int x:S) res+=x;
    for(int i=0;i<T;i++){
        int d=S[M-T+i];
        res+=d*(N/T+(N%T>i));
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
