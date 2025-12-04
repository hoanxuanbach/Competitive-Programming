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

const int N = 85;

void solve_small(int n,int K){
    int T=(n-1)*(n-1)-K;
    
    cout << n << '\n';
    for(int i=1;i<n;i++) cout << 1;
    cout << '\n';
    for(int i=1;i+1<n;i++){
        for(int j=i+1;j<n;j++){
            cout << (T>0);
            if(T) T--;
        }
        cout << '\n';
    }
}

const int M = 10000;
const int D = 5;

int d[N+5][N+5][D+5];
void init(){
    for(int n=1;n<=N;n++) for(int x=0;x<n;x++) for(int k=1;k<=min(n-x-1,D);k++){
        int y=x+k,cnt=0;
        for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) cnt+=min(j-i,abs(i-x)+abs(j-y)+1);
        d[n][x][k]=(n*n*n-n)/6-cnt;
    }
}

bitset<M> B[N+5];
bool solve_large(int n,int K){
    int T=(n*n*n-n)/6;
    if(K>T || T-K>=M) return false;

    K=T-K;
    for(int i=0;i<n;i++) B[i].reset();
    B[0][0]=1;
    for(int x=0;x+1<n;x++) for(int k=1;k<=min(n-x-1,D);k++) B[x+k]|=B[x]<<d[n][x][k];
    if(!B[n-1][K]) return false;

    int X=n-1;
    vector<vector<int>> g(n,vector<int>(n,0));
    for(int i=0;i+1<n;i++) g[i][i+1]=1;

    while(X){
        for(int k=1;k<=min(D,X);k++){
            int nK=K-d[n][X-k][k];
            if(nK<0) continue;
            if(B[X-k][nK]){
                g[X-k][X]=1;
                K=nK,X-=k;
                break;
            }
        }
    }

    cout << n << '\n';
    for(int i=0;i+1<n;i++){
        for(int j=i+1;j<n;j++) cout << g[i][j];
        cout << '\n';
    }
    return true;
}

void solve(){
    int K;cin >> K;
    for(int n=1;n<=N;n++){
        int L=n*(n-1)/2,R=(n-1)*(n-1);
        if(L<=K && K<=R){
            solve_small(n,K);
            return;
        }
    }
    for(int n=1;n<=N;n++) if(solve_large(n,K)) return;
    assert(false);
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    init();
    int test=1;cin >> test;
    while(test--) solve();
}
