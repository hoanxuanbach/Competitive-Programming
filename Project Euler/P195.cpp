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
    N=(int)N*2*sqrt(3);
    vector<int> p(N+1);
    for(int i=2;i<=N;i++) if(!p[i]){
        for(int j=i;j<=N;j+=i) p[j]=i;
    }

    int res=0;
    for(int c=2;c<=N;c++){
        if(c%1000==0) cout << c << endl;
        int x=c;
        vector<pii> P;

        int d=3*c*c,k=0;
        //(2*b-2*a+c)*(2*b+2*a-c)=3*c*c
        while(x%2==0) x/=2,k++;

        int SS=1;
        if(k==1) SS*=2;
        else if(k>1) SS*=2,P.push_back({2,2*k-2});
        
        k=0;
        while(x%3==0) x/=3,k++;
        P.push_back({3,2*k+1});

        while(x>1){
            int j=p[x];k=0;
            while(x%j==0) x/=j,k++;
            P.push_back({j,2*k});
        }

        function<void(int,int)> dfs = [&](int i,int S){
            if(S>d/S) return;
            if(i==(int)P.size()){
                int T=d/S,b=(S+T);
                if(b%4!=0) return; 
                b/=4;
                int a=(2*b+c-S)/2;
                if(a<=c) return;
                if(a+c-b<=N) res++;
                return;
            }
            for(int j=0;j<=P[i].second;j++){
                if(j) S*=P[i].first;
                dfs(i+1,S);
            }
        };
        dfs(0,SS);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
