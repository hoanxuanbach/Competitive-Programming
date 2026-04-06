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
    int N=10000000,res=0;
    vector<int> f(N);
    for(int i=2;i<N;i++) if(!f[i]) for(int j=i;j<N;j+=i) f[j]=i;
    for(int s=1;s<N;s++){
        if(s%10000==0) cout << s << endl;
        vector<pii> P;
        int x=s;
        while(x>1){
            int j=f[x],k=0;
            while(x%j==0) x/=j,k++;
            P.push_back({j,2*k});
        }

        function<void(int,int)> dfs = [&](int i,int d){
            if(i==(int)P.size()){
                int g=s*s/d;
                int a=4*s-g;
                int c=d-a;
                int b=s-c;
                if(min({a,b,c})>0 && (a+b+c)<=N) res+=a+b+c;
                return;
            }
            for(int k=0;k<=P[i].second;k++){
                if(k) d*=P[i].first;
                dfs(i+1,d);
            }
        };
        dfs(0,1);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
