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

const int S=5;
const int L=30;
const int K=10;

vector<int> P={2,3,5,7,11};
int g[L+5][(1<<S)],T[K+5];
int f[1<<S][K+5];

void init(){
    vector<int> cur=P;
    for(int i=0;i<L;i++){
        for(int mask=0;mask<(1<<S);mask++){
            g[i][mask]=1;
            for(int j=0;j<S;j++) if(mask>>j&1) g[i][mask]=g[i][mask]*cur[j]%mod;
        }
        for(int j=0;j<S;j++) cur[j]=cur[j]*cur[j]%mod;
    }

    for(int mask=0;mask<(1<<S);mask++){
        vector<int> X(S);
        for(int i=0;i<S;i++) X[i]=(mask>>i&1);

        int p=0;
        for(int i=0;i<S;i++) for(int j=i+1;j<S;j++) f[mask][p++]=X[i]+X[j];
    }

    T[0]=1;
    for(int i=1;i<=K;i++) T[i]=T[i-1]*3;
}
int dp[35][200005];
int cal(vector<int> X){
    assert((int)X.size()==10);
    dp[L][0]=1;
    for(int i=L-1;i>=0;i--){
        for(int x=0;x<T[K];x++) dp[i][x]=0;
        
        for(int x=0;x<T[K];x++){
            if(!dp[i+1][x]) continue;
            for(int d=0;d<(1<<S);d++){
                int nx=0;
                for(int j=0;j<K;j++){
                    int a=(x/T[j])%3,b=f[d][j];
                    a=a*2+(X[j]>>i&1)-b;
                    if(a<0){
                        nx=-1;
                        break;
                    }
                    else nx+=min(a,2LL)*T[j];
                }
                if(nx==-1) continue;
                dp[i][nx]=(dp[i][nx]+dp[i+1][x]*g[i][d])%mod;
            }
        }
    }
    int res=0;
    for(int x=0;x<T[K];x++) res=(res+dp[0][x])%mod;
    return res;
}

void solve(){
    int N=100;init();
    vector<int> A(10*N);A[0]=1;A[1]=7;
    for(int i=2;i<10*N;i++) A[i]=(7*A[i-1]+A[i-2]*A[i-2])%mod;

    int res=0;
    for(int i=0;i<N;i++){
        cout << i << endl;
        res=(res+cal(vector<int>(A.begin()+i*10,A.begin()+(i+1)*10)))%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
