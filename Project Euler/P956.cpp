#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 999999001;
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
    vector<int> f(N+1);f[N]=1;
    for(int x=1;x<=3;x++) for(int i=N-1;i>=1;i--) f[i]+=f[i+1];

    vector<int> g(N+1);

    vector<int> p(N+1);
    for(int i=2;i<=N;i++) if(!p[i]){
        for(int j=i;j<=N;j+=i) p[j]=i;
    }   
    for(int i=2;i<=N;i++){
        int x=i;
        while(x>1){
            int j=p[x],k=0;
            while(x%j==0) x/=j,k++;
            g[j]+=f[i]*k;
        }
    }

    vector<int> d(N);d[0]=1;
    for(int i=2;i<=N;i++) if(p[i]==i){
        //cout << i << ' ' << g[i] << '\n';
        int x=(g[i]/N)%mod,k=g[i]%N; 

        vector<int> nd(N);
        
        int s=1,t=1;
        for(int b=0;b<N;b++) t=t*i%mod;
        assert(t!=1);
        int t0=(power(t,x)+mod-1)*power(t-1,mod-2)%mod;
        int t1=(t*t0+1)%mod;

        //cout << t << ' ' << t0 << ' ' << t1 << '\n';
        for(int b=0;b<N;b++){
            int nx=s*(b<=k?t1:t0)%mod;
            for(int a=0;a<N;a++) (nd[(a+b)%N]+=d[a]*nx)%=mod;
            s=(s*i)%mod;
        }
        d=nd;
    }
    cout << d[0] << '\n';

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
