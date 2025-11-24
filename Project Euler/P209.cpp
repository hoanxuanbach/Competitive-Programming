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
    int N=64;
    vector<int> f(N),d(N);
    for(int x=0;x<N;x++){
        int a=x&1,nx=x>>1;
        int b=nx&1,c=(nx>>1&1);
        nx+=(a^(b&c))<<5;
        f[x]=nx;d[nx]++;
    } 
    vector<array<int,2>> g(N,array<int,2>{1,1});
    queue<int> q;
    for(int i=0;i<N;i++) if(!d[i]) q.push(i);
    while(!q.empty()){
        int x=q.front();q.pop();
        int u=f[x];
        if(!(--d[u])) q.push(u);
        g[u][0]*=(g[x][0]+g[x][1]);
        g[u][1]*=g[x][0];
    }
    int res=1;
    for(int i=0;i<N;i++) if(d[i]){
        vector<int> X;
        int u=i;
        while(d[u]){
            X.push_back(u);
            d[u]=0;u=f[u];
        }
        int cnt=0;
        for(int k=0;k<=1;k++){
            int A=0,B=0;
            if(k) B=g[X[0]][1];
            else A=g[X[0]][0];

            for(int j=1;j<(int)X.size();j++){
                int v=X[j];

                int tmp=A;
                A=g[v][0]*(A+B);
                B=g[v][1]*tmp;
            }

            if(k) cnt+=A;
            else cnt+=A+B;
        }
        res*=cnt;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
