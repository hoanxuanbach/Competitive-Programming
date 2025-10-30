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

    int S=1;
    while(S*S*S<=N) S++;

    vector<int> p(S);
    for(int i=2;i<S;i++) if(!p[i]){
        for(int j=i;j<S;j+=i) p[j]=i;
    }

    int res=0;
    for(int i=1;i<S;i++){
        vector<int> d;

        int x=i;
        bool check=true;
        while(x>1){
            int j=p[x],k=0;
            d.push_back(j);
            while(x%j==0) x/=j,k++;
            if(k>=2) check=false;
        }
        if(!check) continue;
        function<void(int,int)> dfs = [&](int a,int k){
            if(k==(int)d.size()){
                res+=N/a;
                return;
            }
            while(a<=N){
                dfs(a,k+1);
                if(a>N/d[k]) break;
                a*=d[k];
            }
        };
        dfs(i*i*i,0);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
