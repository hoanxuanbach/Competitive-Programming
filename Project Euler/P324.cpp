#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e8+7;
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

int K[155][155][15];

void solve(){
    int S=9,T=(1<<S);
    vector<vector<int>> A(T,vector<int>(T,0));
    function<void(int,int,int,int)> dfs = [&](int x,int y,int a,int b){
        if(a==3){
            A[x][y]++;
            return;
        }
        int na=a,nb=b;
        if(b==2) na++,nb=0;
        else nb++;

        int p=a*3+b;
        dfs(x,y,na,nb);
        if(!(y>>p&1)){
            y|=(1<<p);
            if(b+1<3 && !(y>>(p+1)&1)) dfs(x,y|(1<<(p+1)),na,nb); 
            if(a+1<3 && !(y>>(p+3)&1)) dfs(x,y|(1<<(p+3)),na,nb); 
        }
    };
    for(int mask=0;mask<T;mask++){
        int nmask=mask^(T-1);
        dfs(mask,nmask,0,0);
    }
    auto mul = [&](vector<vector<int>> X,vector<vector<int>> Y){
        int n=(int)X.size();
        vector<vector<int>> Z(n,vector<int>(n,0));
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) for(int k=0;k<n;k++) (Z[i][j]+=X[i][k]*Y[k][j])%=mod;
        return Z;
    };
    A=mul(A,A);

    int P=0;
    vector<int> f(T,-1);
    for(int i=0;i<T;i++) if(A[T-1][i]) f[i]=P++;


    vector<vector<int>> B(P,vector<int>(P,0));
    for(int i=0;i<T;i++) for(int j=0;j<T;j++) if(f[j]!=-1 && f[i]!=-1) B[f[i]][f[j]]=A[i][j];

    A=B;A=mul(A,B);A=mul(A,B);A=mul(A,B);A=mul(A,B);
    for(int i=0;i<P;i++) for(int j=0;j<P;j++) K[i][j][1]=A[i][j];

    int N=10000;
    for(int t=1;t<N;t++){
        cout << t << endl;
        for(int k=2;k<=10;k++) for(int i=0;i<P;i++) for(int j=0;j<P;j++){
            K[i][j][k]=0;
            for(int x=0;x<P;x++) K[i][j][k]=(K[i][j][k]+K[i][x][1]*K[x][j][k-1])%mod;
        }
        for(int i=0;i<P;i++) for(int j=0;j<P;j++) K[i][j][1]=K[i][j][10];
    }
    cout << K[P-1][P-1][1] << endl;
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
