#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 987898789;
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

#define matrix array<array<int,2>,2>

void solve(){

    int N;cin >> N;
    vector<vector<array<int,2>>> f(N+1,vector<array<int,2>>(N+1,{0,0}));
    for(int i=1;i<=N;i++) f[i][0][0]=f[0][i][0]=f[0][i][1]=-1,f[i][0][1]=i;
    for(int i=1;i<=N;i++) for(int j=1;j<=N;j++){
        {
            if(i==j) f[i][j][0]=i;
            else if(j>=2*i) f[i][j][0]=f[i][j-2*i][0];
            else if(i>=2*j) f[i][j][0]=f[i-2*j][j][0];
            else{
                int a=i,b=j;
                if(a<b) swap(a,b);
                f[i][j][0]=f[b][a-b][1];
            }
        }
        {
            if(i==j) f[i][j][1]=-1;
            else if(i>=j) f[i][j][1]=f[i-j][j][1];
            else if(j>=2*i) f[i][j][1]=f[i][j-2*i][1];
            else f[i][j][1]=f[i][j-i][0];
        }
    }
    int total=10*N*N;

    vector<int> cnt(N+2);
    for(int i=1;i<=N;i++) for(int j=1;j<=N;j++){
        int d=f[i][j][0];
        cnt[d+1]++;
    }
    auto mul = [&](matrix a,matrix b){
        matrix c;
        for(int i=0;i<=1;i++) for(int j=0;j<=1;j++){
            c[i][j]=0;
            for(int k=0;k<=1;k++) c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
        }
        return c;
    };

    vector<vector<matrix>> g(N+1,vector<matrix>(N+1));
    for(int c=2;c<=N;c++){
        g[c][0]={array<int,2>{0,1},array<int,2>{1,10}};
        for(int i=1;i<=N;i++){
            g[c][i]=g[c][i-1];
            matrix a=g[c][i-1];
            int d=c-1;
            while(d){
                if(d&1) g[c][i]=mul(g[c][i],a);
                a=mul(a,a);d>>=1;
            }
        }
    }
    for(int d=-1;d<=N;d++){
        int val=0;
        for(int c=2;c<=N;c++){
            if(d==-1) val=(val+(c&1?10:1))%mod;
            else val=(val+g[c][d][1][1])%mod;
        }
        total=(total+val*cnt[d+1])%mod;
    }

    cout << total << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
