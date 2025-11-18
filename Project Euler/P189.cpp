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
    int N;cin >> N;
    vector<int> P(N+1);P[0]=1;
    for(int i=1;i<=N;i++) P[i]=P[i-1]*3;

    vector<int> g(P[1],1);
    for(int x=1;x<N;x++){
        vector<int> f(P[x+1]);
        for(int i=0;i<P[x];i++) for(int j=0;j<=2;j++) f[i*3+j]=g[i];
        
        swap(g,f);
        for(int k=1;k<=x;k++){
            f.assign(P[x+1],0);
            for(int i=0;i<P[x+1];i++){
                int a=i/P[x],b=i%3,j=(i-a*P[x])*3;
                for(int c=0;c<=2;c++) for(int d=0;d<=2;d++){
                    if(d!=a && d!=b && d!=c) f[j+c]+=g[i];
                }
            }
            swap(g,f);
        }
    }
    int res=0;
    for(int i=0;i<P[N];i++) res+=g[i];
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
