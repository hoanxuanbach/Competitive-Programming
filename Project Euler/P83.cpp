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

int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};

void solve(){
    int N=80;
    vector<vector<int>> a(N,vector<int>(N));
    for(int i=0;i<N;i++){
        string S;cin >> S;
        int x=0,j=0;
        for(char c:S){
            if(c>='0' && c<='9') x=x*10+c-'0';
            else{
                if(x) a[i][j++]=x;
                x=0;
            }
        }
        if(x) a[i][j++]=x;
    }
    vector<vector<int>> d(N,vector<int>(N,inf));
    priority_queue<array<int,3>,vector<array<int,3>>,greater<array<int,3>>> pq;
    pq.push({d[0][0]=a[0][0],0,0});
    while(!pq.empty()){
        auto [dd,x,y]=pq.top();pq.pop();
        if(d[x][y]!=dd) continue;
        for(int t=0;t<4;t++){
            int xt=x+dx[t],yt=y+dy[t];
            if(xt<0 || yt<0 || xt>=N || yt>=N) continue;
            int nd=dd+a[xt][yt];
            if(nd<d[xt][yt]) pq.push({d[xt][yt]=nd,xt,yt});
        }
    }
    cout << d[N-1][N-1] << '\n';
}
 
signed main(){
    freopen("83.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
