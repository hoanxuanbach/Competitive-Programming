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
const __int128 INF = (__int128)inf*inf;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int N,S;cin >> N >> S;
    int T=0;
    vector<int> f(N+1,-1);
    function<void(int,int)> dfs = [&](int i,int x){
        for(int j=1;j<=N;j++){
            if(x%j!=0) continue;
            if(f[j]==-1) f[j]=x,T++;
            else f[j]=min(f[j],x);
        }
        if(i==S) return;
        for(int k=0;k<=2;k++) dfs(i+1,x*10+k);
    };
    dfs(0,1);dfs(0,2);
    
    __int128 res=0;
    cout << '*' << T << endl;
    for(int i=1;i<=N;i++){
        if(i<=2) res++;
        else if(f[i]!=-1) res+=f[i]/i;
        else{
            cout << i << endl;
            vector<__int128> g(i,INF);
            g[1]=1;g[2]=2;
            priority_queue<pair<__int128,int>,vector<pair<__int128,int>>,greater<pair<__int128,int>>> pq;
            pq.push({1,1});
            pq.push({2,2});

            while(!pq.empty()){
                auto [d,x]=pq.top();pq.pop();
                if(g[x]!=d) continue;
                for(int k=0;k<=2;k++){
                    int nx=(x*10+k)%i;
                    if(g[nx]>d*10+k){
                        g[nx]=d*10+k;
                        pq.push({g[nx],nx});
                    }
                }
            }
            res+=g[0]/i;
        }
    }
    string ss;
    while(res) ss+=char('0'+res%10),res/=10;
    reverse(ss.begin(),ss.end());
    cout << T << ' ' << ss << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
