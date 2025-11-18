#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int inf = 1e18;

#define matrix array<array<int,2>,2> 
#define pii array<int,2> 

matrix mul(matrix a,matrix b,int mod){
    matrix c;
    for(int i=0;i<=1;i++) for(int j=0;j<=1;j++){
        c[i][j]=0;
        for(int k=0;k<=1;k++) c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
    }
    return c;
}
pii mul(pii a,matrix b,int mod){
    pii c;
    for(int i=0;i<=1;i++){
        c[i]=0;
        for(int k=0;k<=1;k++) c[i]=(c[i]+a[k]*b[k][i])%mod;
    }
    return c;
}

bool cal(int n,int p){
    //cout << "cal " << n << ' ' << p << endl;
    pii X={1,0};
    matrix A = {pii{1,1},pii{7%p,1}};
    while(n){
        if(n&1) X=mul(X,A,p);
        A=mul(A,A,p);n>>=1;
    }
    if(X[0]==1 && X[1]==0) return true;
    else return false;
}

void solve(){
    int N;cin >> N;
    vector<vector<int>> d(N+1);
    for(int i=1;i<=N;i++) for(int j=i;j<=N;j+=i) d[j].push_back(i);

    vector<int> X,f(N+1),c(N+1);
    for(int i=2;i<=N;i++) if(!c[i]){
        for(int j=i;j<=N;j+=i) c[j]=1;
        X.push_back(i);
    }

    for(int p:X){
        cout << p << endl;
        int a=p-1,b=p+1,x=inf;
        for(int da:d[a]) for(int db:d[b]) if(cal(da*db,p)) x=min(x,da*db);
        if(p==7) x=7;
        //cout << x << endl;
        if(x==inf){
            cout << '*' << p << endl;
            int q=p;
            while(q<=N) f[q]=-1,q*=p;
            continue;
        }
        //cout << p << ' ' << x << endl;
        f[p]=x;
        int q=p*p;
        while(q<=N && cal(x,q)) f[q]=x,q*=p;
        while(q<=N) f[q]=f[q/p]*p,q*=p;
    }
    //cout << "end" << endl;
    for(int i=2;i<=N;i++){
        if(f[i]) continue;
        int x=d[i][1];
        while((i/x)%d[i][1]==0) x*=d[i][1];
        int y=i/x;
        if(f[x]==-1 || f[y]==-1) f[i]=-1;
        else f[i]=f[x]*f[y]/__gcd(f[x],f[y]);
    }
    int res=0;
    for(int i=2;i<=N;i++) if(f[i]!=-1) res+=f[i];
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
