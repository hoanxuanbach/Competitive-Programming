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

vector<int> P={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

void solve(){
    int N,S=(int)P.size();cin >> N;
    vector<vector<int>> f(N,vector<int>(S,0));
    for(int i=1;i<N;i++){
        int x=i;
        for(int j=0;j<S;j++) while(x%P[j]==0) f[i][j]++,x/=P[j];
    }
    
    set<vector<int>> ss;
    for(int i=0;i<N;i++) for(int j=0;j<=i;j++){
        vector<int> A(S);
        for(int k=i-j+1;k<=i;k++) for(int x=0;x<S;x++) A[x]+=f[k][x];
        for(int k=1;k<=j;k++) for(int x=0;x<S;x++) A[x]-=f[k][x];
        bool free=true;
        for(int k=0;k<S;k++) if(A[k]>1) free=false;
        if(free) ss.insert(A);
    }
    int res=0;
    for(auto A:ss){
        int val=1;
        for(int x=0;x<S;x++) if(A[x]) val*=P[x];
        res+=val;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
