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
 
const int maxn = 3e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

const int S=8;
const int Z=13;

int a[20][maxn];
void fix(int i,int k,int x){
    if(i==S-1 || !k) a[i][k]=x;
    else{
        fix(i+1,a[i][k],a[i+1][a[i][k]]-1);
        a[i][k]=x;
        fix(i+1,a[i][k],a[i+1][a[i][k]]+1);
    }
}

const int M=100;
int C[maxn],D[maxn];

void solve(){
    int n,q;cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[0][i];
    for(int i=1;i<S;i++) for(int j=1;j<=n;j++) a[i][a[i-1][j]]++;

    for(int i=0;i<q;i++){
        int op,k,x;cin >> op >> k >> x;
        if(op==1) fix(0,k,x);
        else if(k<S) cout << a[k][x] << '\n';
        else{
            for(int j=1;j<=M;j++) C[j]=a[S-1][j];
            k=min(k,Z);
            while(k>=S){
                for(int j=1;j<=M;j++) D[j]=0;
                for(int j=1;j<=M;j++) D[C[j]]++;
                for(int j=1;j<=M;j++) C[j]=D[j];
                k--;
            }
            cout << C[x] << '\n';
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
