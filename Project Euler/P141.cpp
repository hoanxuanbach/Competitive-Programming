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
    int N=1000000;
    vector<bool> f(N+1);
    vector<int> p(N+1);
    for(int i=2;i<=N;i++){
        if(!p[i]){
            for(int j=i;j<=N;j+=i) p[j]=i;
        }
    }
    auto add = [&](int val){
        if(val>N*N) return;
        int s=sqrtl(val);
        if(s*s==val) f[s]=true;
    };
    for(int b=1;b<=N;b++){
        if(b%1000==0) cout << b/1000 << endl;
        vector<pii> X;

        int x=b;
        while(x>1){
            int j=p[x],k=0;
            while(x%j==0) x/=j,k++;
            X.push_back({j,2*k});
        }
        function<void(int,int)> dfs = [&](int i,int a){
            if(a>=b) return;
            if(i==(int)X.size()){
                int c=b*b/a;
                add(b*c+a);
                add(a*c+b);
                return;
            }
            dfs(i+1,a);
            for(int j=1;j<=X[i].second;j++){
                if(a*X[i].first>=b) break;
                a*=X[i].first;
                dfs(i+1,a);
            }
        };
        dfs(0,1);
    }
    int cnt=0;
    for(int i=1;i<=N;i++) if(f[i]) cnt+=i*i;
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
