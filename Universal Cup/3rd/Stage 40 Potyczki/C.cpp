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
    int n;string S;cin >> n >> S;
    vector<int> ans(n+1,-1);

    S="#"+S;
    vector<int> C(256,-1);
    C['A']=0;C['T']=1;C['G']=2;C['C']=3;
    vector<vector<int>> f(n+1,vector<int>(4,-1));
    for(int i=1;i<=n;i++){
        f[i]=f[i-1];
        f[i][C[S[i]]]=i;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<4;j++) f[i][j]=min(f[i][j],i-3);
        sort(f[i].begin(),f[i].end());
    }

    vector<int> g(n+1),a(n+1),b(n+1);
    function<void(int,int,int,int)> dnc = [&](int lX,int lY,int rX,int rY){
        if(lX>=rX) return;
        int dX=rX-lX,dY=lY-rY;
        for(int i=1;i<=n;i++){
            g[i]=g[i-1],a[i]=a[i-1],b[i]=b[i-1];
            for(int j=3;j>=0;j--){
                int k=f[i][j]-1;
                if(k<0) continue;
                int val=g[k]+(4-j)*dX+dY;
                if(val>g[i]) g[i]=val,a[i]=a[k]+1,b[i]=b[k]+4-j;
            }
        }
        int A=a[n],B=b[n];
        if((A-lX)*(rY-B)==(B-lY)*(rX-A)){
            int d=(rY-lY)/(rX-lX);
            for(int i=lX+1;i<rX;i++) ans[i]=ans[i-1]+d;
            return;
        }
        ans[A]=B;
        dnc(lX,lY,A,B);dnc(A,B,rX,rY);
    };
    ans[0]=0;
    dnc(0,0,n/4+1,0);
    for(int i=1;i<=n;i++) cout << (ans[i]!=-1?4*i-ans[i]:-1) << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
