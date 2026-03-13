#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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

const int S = 1000;

vector<int> mul(vector<int> a,vector<vector<int>> b){
    int n=(int)a.size();
    vector<int> c(n);
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) c[j]=(c[j]+a[i]*b[i][j])%mod;
    return c;
}
vector<vector<int>> mul(vector<vector<int>> a,vector<vector<int>> b){
    int n=(int)a.size();
    vector<vector<int>> c(n,vector<int>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) for(int k=0;k<n;k++) c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
    return c;
}

void solve(){
    int n,k;cin >> n >> k;

    int M=1;
    vector<int> T(k);
    for(int i=1;i<k;i++) cin >> T[i],M=max(M,T[i]);

    int total=0;
    vector<int> f(M);n-=M;
    for(int i=0;i<M;i++){
        f[i]=1;
        for(int j=1;j<k;j++){
            if(T[j]>i) continue;
            f[i]=(f[i]+1)%mod;
            for(int x=i-T[j];x<i;x++) f[i]=(f[i]+f[x])%mod;
        }
        total=(total+f[i])%mod;
    }

    //f[0],...,f[M-1],total,k


    //f[1],...,f[M],total+f[M],k
    f.push_back(total);f.push_back(k);
    vector<vector<int>> S(M+2,vector<int>(M+2));
    
    for(int i=1;i<M;i++) S[i][i-1]=1;
    S[M+1][M-1]=1;
    for(int i=1;i<k;i++) for(int x=1;x<=T[i];x++) S[M-x][M-1]++;
    for(int i=0;i<=M+1;i++) S[i][M]=S[i][M-1];
    S[M][M]=1;
    S[M+1][M+1]=1;

    while(n){
        if(n&1) f=mul(f,S);
        S=mul(S,S);n>>=1;
    }
    cout << f[M] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}