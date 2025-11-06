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

int dp[35][5][5][5][20];

void solve(){
    map<vector<int>,int> mp;
    mp[{2,3,1,1}]=0;
    mp[{2,0,3,1}]=1;
    mp[{0,3,1,0}]=2;
    mp[{3,1,1,2}]=3;
    dp[0][1][1][1][0]=1;

    int n;cin >> n;
    for(int i=0;i<n;i++){
        for(int a=0;a<=3;a++) for(int b=0;b<=3;b++) for(int c=0;c<=3;c++) for(int x=0;x<16;x++){
            if(!dp[i][a][b][c][x]) continue;
            for(int d=0;d<=3;d++){
                int y=x,k=-1;
                vector<int> v={a,b,c,d};
                if(mp.find(v)!=mp.end()) k=mp[v];
                if(k!=-1 && (x>>k&1)) continue;
                if(k!=-1) y|=(1<<k);
                dp[i+1][b][c][d][y]+=dp[i][a][b][c][x];
            }
        }
    }
    int res=0;
    for(int a=0;a<=3;a++) for(int b=0;b<=3;b++) for(int c=0;c<=3;c++) res+=dp[n][a][b][c][15];
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
