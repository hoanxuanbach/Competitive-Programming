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

int cal(int n){
    vector<int> f(n),d(n);
    vector<array<int,2>> dp(n,{0,0});
    for(int i=0;i<n;i++){
        f[i]=(i*i*i+i+1)%n;
        d[f[i]]++;
        //cout << i << ' ' << f[i] << '\n';
    }
    queue<int> q;
    for(int i=0;i<n;i++) if(!d[i]) q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        dp[u][0]+=dp[u][1];
        dp[u][1]++;

        int x=f[u];
        dp[x][1]+=dp[u][0];
        dp[x][0]=max(dp[x][0],dp[u][1]-dp[u][0]);
        if(!(--d[x])) q.push(x);
    }
    int res=0;
    for(int v=0;v<n;v++) if(d[v]){
        int u=v;
        vector<int> X;
        while(d[u]){
            d[u]=0;
            dp[u][0]+=dp[u][1];
            //cout << "dp " << u << ' ' << dp[u][0] << ' ' << dp[u][1] << '\n';
            X.push_back(u);
            u=f[u];
        }
        int mx=0;
        for(int t=0;t<=1;t++){
            array<int,2> T={0,0};
            if(t) T={dp[X[0]][0],dp[X[0]][1]+1};
            else T={dp[X[0]][1],-inf};
            for(int i=1;i<(int)X.size();i++){
                int x=X[i];
                int B=max(dp[x][0]-dp[x][1],T[1]-T[0]);
                int A=dp[x][1]+T[0];
                
                B+=A;A++;
                //cout << x << ' ' << B << ' ' << A << '\n';
                T={B,A};
            }
            //cout << 'T' << ' ' << T[0] << ' ' << T[1] << '\n';
            if(t) mx=max(mx,T[0]);
            else mx=max(mx,max(T[0],T[1]));
        }
        res+=mx;
        //cout << '*' << v << ' ' << mx << '\n';
    }
    return res;
}

void solve(){
    int res=0;
    //int n;cin >> n;
    //cout << cal(n) << '\n';
    //cout << cal(5) << ' ' << cal(10) << '\n';
    for(int i=1;i<=100;i++) res+=cal(100000+i);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
