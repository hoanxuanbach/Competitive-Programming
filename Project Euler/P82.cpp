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
    int N=80;
    vector<vector<int>> a(N,vector<int>(N));
    for(int i=0;i<N;i++){
        string S;cin >> S;
        int x=0,j=0;
        for(char c:S){
            if(c>='0' && c<='9') x=x*10+c-'0';
            else{
                if(x) a[j++][i]=x;
                x=0;
            }
        }
        if(x) a[j++][i]=x;
    }
    for(int i=1;i<N;i++){
        vector<int> d=a[i];
        for(int j=0;j<N;j++) a[i][j]+=a[i-1][j];
        for(int j=1;j<N;j++) a[i][j]=min(a[i][j],a[i][j-1]+d[j]);
        for(int j=N-2;j>=0;j--) a[i][j]=min(a[i][j],a[i][j+1]+d[j]);
    }
    int res=inf;
    for(int i=0;i<N;i++) res=min(res,a[N-1][i]);
    cout << res << '\n';
}
 
signed main(){
    freopen("82.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
