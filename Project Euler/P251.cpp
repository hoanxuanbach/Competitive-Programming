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
    int K=N/4+1;
    
    int S=8*K+5;
    vector<int> p(S);
    for(int i=2;i<S;i++){
        if(!p[i]){
            for(int j=i;j<S;j+=i) p[j]=i;
        }
    }

    int cnt=0;
    for(int k=0;k<K;k++){
        if(k%100000==0){
            cout << k << endl;
        }
        int a=3*k+2;
        __int128 T=(__int128)(k+1)*(k+1)*(8*k+5);

        map<int,int> mp;
        
        int x=k+1;
        while(x>1){
            int j=p[x];
            while(x%j==0) mp[j]++,x/=j;
        }
        x=8*k+5;
        while(x>1){
            int j=p[x],d=0;
            while(x%j==0) x/=j,d++;
            if(d>1) mp[j]+=d/2;
        }

        vector<pii> P;
        for(auto [x,d]:mp) P.push_back({x,d});
        function<void(int,int)> dfs = [&](int i,int x){
            if(i==(int)P.size()){
                if(T/(x*x)+x+a<=N) cnt++;
                return;
            }
            for(int j=0;j<=P[i].second;j++){
                if(j) x*=P[i].first;
                dfs(i+1,x);
            }
        };
        dfs(0,1);
    }
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
