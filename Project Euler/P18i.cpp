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

#define poly array<int,3>

poly sub(poly A,poly B,int p){
    for(int i=0;i<=2;i++) A[i]=(A[i]+p-B[i])%p;
    return A;
}

int g[10];
poly mul(poly A,poly B,int p){
    for(int i=0;i<=4;i++) g[i]=0;
    for(int i=0;i<=2;i++) for(int j=0;j<=2;j++) g[i+j]=(g[i+j]+A[i]*B[j])%p;
    g[2]+=3*g[4];
    g[1]-=4*g[4];
    g[1]+=3*g[3];
    g[0]-=4*g[3];

    for(int i=0;i<=2;i++) A[i]=(g[i]%p+p)%p;
    return A;
}

poly power(poly A,int n,int p){
    poly X={1,0,0};
    while(n){
        if(n&1) X=mul(X,A,p);
        A=mul(A,A,p);n>>=1;
    }
    return X;
}

void solve(){
    int L=1000000000,R=1100000000;

    int S=sqrtl(R);
    vector<int> p(S+1,1);
    vector<int> prime;
    for(int i=2;i<=S;i++){
        if(p[i]){
            prime.push_back(i);
            for(int j=i;j<=S;j+=i) p[j]=0;
        }
    }

    vector<int> f(R-L+1,1);
    for(int x:prime) for(int i=((L-1)/x+1)*x;i<=R;i+=x) f[i-L]=0;

    vector<int> pp;
    for(int i=L;i<=R;i++) if(f[i-L]) pp.push_back(i);



    int T=0;
    for(int p:pp){
        cout << p << endl;
        poly A={0,1,0};
        poly B=power(A,p,p);
        poly C=power(B,p,p);

        poly D=sub(A,C,p);
        C=sub(C,B,p);
        B=sub(B,A,p);
        A=mul(B,mul(C,D,p),p);
        T+=(p-A[0])%p;
    }
    cout << T << '\n';
    //842507000531275
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
