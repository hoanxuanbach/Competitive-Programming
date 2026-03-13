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

int dx[] = {0,1,1,1},
    dy[] = {1,0,1,-1};

const int S = 1000;

void solve(){
    int n;cin >> n;
    vector<vector<int>> f(S,vector<int>(S,-1));

    int k=0;
    vector<int> cnt(2);
    while(n--){
        int x,y;cin >> x >> y;x--;y--;
        f[x][y]=k;
        for(int t=0;t<4;t++){
            int cur=0;
            for(int i=-4;i<=4;i++){
                int xt=x+dx[t]*i,yt=y+dy[t]*i;
                if(xt<0 || yt<0 || xt>=S || yt>=S){
                    cur=0;continue;
                } 
                if(f[xt][yt]==k) cur++;
                else cur=0;
                if(cur>=5) cnt[k]++;
            }
        }
        cout << cnt[k] << ' ';
        k^=1;
        
    }
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}