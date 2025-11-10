#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
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
    vector<int> p(N),phi(N);phi[1]=p[1]=1;

    int res=0,T=25;
    vector<vector<int>> d(N);
    for(int i=2;i<N;i++){
        for(int j=i;j<N;j+=i) d[j].push_back(i);
        if(!p[i]){
            for(int j=i;j<N;j+=i) p[j]=i;
        }
        int x=p[i];
        if((i/x)%x==0) phi[i]=phi[i/x]*x;
        else phi[i]=phi[i/x]*(x-1);

        if(__gcd(i,10LL)!=1) continue;

        if(i%9==0 && p[i/9]!=(i/9)){
            x=__gcd(phi[i],(i/9)-1);
            bool check=false;
            for(int j:d[x]){
                int k=power(10,j,i);
                if(k==1) check=true;
            }
            if(check){
                cout << i/9 << endl;
                res+=i/9;T--;
                if(!T){
                    cout << res << '\n';
                    return;
                }
            }
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
