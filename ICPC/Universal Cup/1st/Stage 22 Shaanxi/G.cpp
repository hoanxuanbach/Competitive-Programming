#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}


const int N = 5005;
int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};

pair<int,int> nxt[N][N];

void solve(){
    int n,k;cin >> n >> k;
    vector<vector<char>> c(n,vector<char>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin >> c[i][j];
    vector<vector<int>> d(n,vector<int>(n,-1));
    vector<pair<int,int>> q;
    q.push_back({0,0});d[0][0]=0;

    for(int i=0;i<n;i++) for(int j=0;j<n;j++){
        nxt[i][j]={n,n};
        if(c[i][j]=='*') continue;
        int ci=j+1,cj=i;
        while(ci<n && cj<n && c[ci][cj]=='*') swap(ci,cj),ci++;
        nxt[i][j]={ci,cj};
    }


    while(!q.empty()){
        vector<pair<int,int>> nq;
        for(auto [x,y]:q){
            int dd=d[x][y]+1;
            int st=x+y;
            tie(x,y)=nxt[x][y];
            while(x<n && y<n && x+y-st<=k && d[x][y]==-1){
                d[x][y]=dd;
                if(c[x][y]=='.') nq.push_back({x,y});
                tie(x,y)=nxt[x][y];
            }
        }
        for(auto [x,y]:q){
            int dd=d[x][y]+1;
            for(int t=0;t<4;t++){
                int xt=x+dx[t],yt=y+dy[t];
                if(xt<0 || yt<0 || xt>=n || yt>=n || c[xt][yt]=='*' || d[xt][yt]!=-1) continue;
                d[xt][yt]=dd;
                nq.push_back({xt,yt});
            }
        }
        swap(q,nq);
    }

    cout << d[n-1][n-1] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}