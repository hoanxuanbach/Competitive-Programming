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

    vector<int> p(N+1);
    for(int i=2;i<=N;i++) if(!p[i]){
        for(int j=i*i;j<=N;j+=i) p[j]=i;
    }

    int S=sqrtl(N);
    vector<vector<int>> f(S);
    for(int i=2;i<S;i++) if(!p[i]){
        f[i].push_back(1);
        while(f[i].back()*i<=N) f[i].push_back(f[i].back()*i);
        
        f[i][0]=0;
        for(int j=1;j<(int)f[i].size();j++){
            int m=f[i][j-1];
            while(true){
                int d=m,k=0;
                while(d) d/=i,k+=d;
                if(k>=j) break;
                m+=i;
            }
            f[i][j]=m;
        }
    }

    int T=0;
    for(int i=1;i<=N;i++){
        int x=i,m=0;
        while(p[x]){
            int j=p[x],k=0;
            while(x%j==0) x/=j,k++;
            if(j<S) m=max(m,f[j][k]);
            else m=max(m,j);
        }
        if(x>1) m=max(m,x);
        T+=m;
    }
    cout << T << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
