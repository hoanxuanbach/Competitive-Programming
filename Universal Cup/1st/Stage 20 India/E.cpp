#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 1e6+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int nxt[maxn][26],val[maxn];

void solve(){
    int N,K;cin >> N >> K;
    
    vector<string> S(N);
    vector<int> X(K,inf);

    int D=0;
    for(int i=0;i<N;i++){
        cin >> S[i];
        int d=(int)S[i].length();
        X[d%K]=min(X[d%K],d);
        D=max(D,d);
    }

    vector<int> G;
    for(int i=1;i<K;i++) if(X[i]!=inf) G.push_back(X[i]);
    sort(G.begin(),G.end(),greater<int>());

    vector<int> cost(D+K,inf);

    queue<int> q;
    q.push(0);cost[0]=0;
    while(!q.empty()){
        int x=q.front();q.pop();
        if(x<D){
            if(cost[x+K]>cost[x]+1){
                cost[x+K]=cost[x]+1;
                q.push(x+K);
            }
        }
        for(int y:G){
            if(x<y) continue;
            if(x>=y+K) break;

            y=x-y;
            if(cost[y]>cost[x]+1){
                cost[y]=cost[x]+1;
                q.push(y);
            }
        }
    }

    int T=0;val[0]=0;
    memset(nxt[0],0,sizeof(nxt[0]));
    for(int i=0;i<N;i++){
        int d=(int)S[i].length();
        
        int u=0;
        for(int j=0;j<d;j++){
            int x=S[i][j]-'a';
            if(!nxt[u][x]){
                nxt[u][x]=++T;
                memset(nxt[T],0,sizeof(nxt[T]));
                val[T]=inf;
            }
            u=nxt[u][x];
            int w=1+cost[d-j-1];
            val[u]=min(val[u],w);
        }
    }

    string Z;
    cin >> Z;
    int m=(int)Z.length();Z="#"+Z;
    vector<int> dp(m+1,inf);dp[0]=0;
    for(int i=0;i<m;i++){
        int u=0;
        for(int j=1;i+j<=m;j++){
            int x=Z[i+j]-'a';
            if(!nxt[u][x]) break;
            u=nxt[u][x];
            dp[i+j]=min(dp[i+j],dp[i]+val[u]);
        }
    }
    cout << (dp[m]==inf?-1:dp[m]) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}