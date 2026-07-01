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

void solve(){
    vector<int> sg(1<<10);
    vector<vector<int>> g(1<<10,vector<int>(10,-1));
    for(int mask=0;mask<(1<<10);mask++) for(int x=0;x<=9;x++){
        int cur=mask;
        for(int i=x;i>=0;i--) if(cur>>i&1){
            cur^=(1<<i);
            break;
        }
        cur^=(1<<x);
        g[mask][x]=cur;
        sg[mask]=__builtin_popcount(mask);
    }

    int T=0;
    map<vector<int>,int> mp;
    vector<vector<int>> f;
    vector<int> sf;
    
    queue<vector<int>> q;
    auto add = [&](vector<int> X){
        if((int)X.size()>10) return -1LL;
        if(mp.find(X)==mp.end()){
            mp[X]=T++;
            sf.emplace_back((int)X.size());
            f.emplace_back(vector<int>(10,-1));
            q.push(X);
        }
        return mp[X];
    };

    vector<int> empty;add(empty);
    while(!q.empty()){
        vector<int> X=q.front();q.pop();
        int u=mp[X];
        for(int d=0;d<10;d++){
            int pos=upper_bound(X.begin(),X.end(),d)-X.begin();
            if(pos==(int)X.size()){
                X.push_back(d);
                f[u][d] = add(X);
                X.pop_back();
            }
            else{
                int k=X[pos];
                X[pos]=d;
                f[u][d] = add(X);
                X[pos]=k;
            }
        }
    }

    cout << "start" << endl;
    map<pii,int> dp;

    int cnt=0;
    function<int(int,int)> dnc = [&](int x,int y){
        if(dp.find({x,y})!=dp.end()) return dp[{x,y}];
        int ret=(sf[x]==sg[y]);
        cnt++;
        if(cnt%100000==0) cout << cnt << endl;
        for(int d=0;d<=9;d++) if(f[x][d]!=-1) (ret+=dnc(f[x][d],g[y][d]))%=mod;
        return dp[{x,y}]=ret;
    };

    int res=0;
    for(int x=1;x<=9;x++) res=(res+dnc(f[0][x],g[0][x]))%mod;
    cout << res << '\n';

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
