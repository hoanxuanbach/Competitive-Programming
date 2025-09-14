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

int dp[20][1005][2][2][2];
void solve(){  
    int lim,n;cin >> lim >> n;
    string R=to_string(lim);
    reverse(R.begin(),R.end());
    vector<int> res(9,0);
    for(char x:R){
        if(x=='9') res[6]++;
        else res[x-'0']++;
    }
    res[0]=max(res[0],1LL);


    vector<int> X(n);
    for(int i=0;i<n;i++) cin >> X[i];
    sort(X.begin(),X.end());
    int T=X[0];


    vector<int> D(T,inf);
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({D[0]=0,0});
    while(!pq.empty()){
        auto [d,u]=pq.top();pq.pop();
        if(D[u]!=d) continue;
        for(int i=0;i<n;i++){
            int k=(u+X[i])%T;
            if(D[k]>D[u]+X[i]) pq.push({D[k]=D[u]+X[i],k});
        }
    }
    int mx=0;
    for(int i=0;i<T;i++) if(D[i]<inf) mx=max(mx,D[i]);
    //mx=lim;
    for(int i=1;i<=min(mx,lim);i++){
        vector<int> cnt(9);
        if(i>=D[i%T]){
            int u=i;
            while(u){
                int k=u%10;u/=10;
                if(k==9) cnt[6]++;
                else cnt[k]++;
            }
        }
        for(int j=0;j<9;j++) res[j]=max(res[j],cnt[j]);
    }
    
    if(mx<lim){
        string L=to_string(mx+1);
        reverse(L.begin(),L.end());
        int m=(int)R.size();
        while((int)L.size()<m) L+='0';
        
        for(int k=0;k<=8;k++){
            for(int i=0;i<=m;i++) for(int j=0;j<T;j++) for(int a=0;a<=1;a++) for(int b=0;b<=1;b++) for(int c=0;c<=1;c++) dp[i][j][a][b][c]=-inf;
            dp[m][0][1][1][0]=0;
            for(int i=m;i>=1;i--) for(int j=0;j<T;j++) for(int a=0;a<=1;a++) for(int b=0;b<=1;b++) for(int c=0;c<=1;c++){
                if(dp[i][j][a][b][c]==-inf) continue;
                for(int x=0;x<=9;x++){
                    if(a && x<L[i-1]-'0') continue;
                    if(b && x>R[i-1]-'0') continue;
                    int nj=(j*10+x)%T;
                    int na=(a && x==(L[i-1]-'0')),nb=(b && x==(R[i-1]-'0'));
                    int nc=(c || (x!=0));
                    int d=(nc && (x==k || (x==9 && k==6)));
                    dp[i-1][nj][na][nb][nc]=max(dp[i-1][nj][na][nb][nc],dp[i][j][a][b][c]+d);
                }
            }
            int cnt=0;
            for(int j=0;j<T;j++) if(D[j]<inf){
                for(int a=0;a<=1;a++) for(int b=0;b<=1;b++) cnt=max(cnt,dp[0][j][a][b][1]);
            } 
            res[k]=max(res[k],cnt);
        }
    }
    for(int i=0;i<9;i++) if(res[i]) cout << i << ' ' << res[i] << endl;
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
