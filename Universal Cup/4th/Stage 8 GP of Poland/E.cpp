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
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

const int M = 100000;
const int K = 25;

void solve(){
    int n;cin >> n;
    vector<vector<int>> adj(M);
    vector<vector<int>> d(M,vector<int>(K+1,inf));

    for(int i=0;i<n;i++){
        string s;cin >> s;
        int x=0;
        for(char c:s) x=x*10+c-'0';
        d[x][0]=i;
    }
    for(int x=0;x<M;x++){
        int k=1;
        for(int i=0;i<5;i++){
            int s=(x/k)%10;
            if(s) adj[x].push_back(x-k);
            else adj[x].push_back(x+9*k);
            if(s<9) adj[x].push_back(x+k);
            else adj[x].push_back(x-9*k);
            k*=10;
        }
    }

    for(int i=0;i<K;i++){
        for(int x=0;x<M;x++) for(int y:adj[x]) d[y][i+1]=min(d[y][i+1],d[x][i]);
    }
    vector<vector<int>> cnt(n+1,vector<int>(K+1,0));

    for(int x=0;x<M;x++){
        int pos=n;
        for(int i=0;i<=K;i++){
            if(d[x][i]<pos){
                int cur=d[x][i];
                cnt[cur][i]++;cnt[pos][i]--;
                pos=cur;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(i){
            for(int j=0;j<=K;j++) cnt[i][j]+=cnt[i-1][j];
        }
        int id=K;
        while(!cnt[i][id]) id--;
        cout << id << ' ' << cnt[i][id] << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}