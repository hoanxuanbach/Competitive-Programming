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
    int n,S,M;cin >> n >> S >> M;

    vector<int> X;
    for(int i=1;i*i<=M;i++){
        if(M%i==0){
            X.push_back(i);
            if(i*i!=M) X.push_back(M/i);
        }
    }
    int m=(int)X.size();
    sort(X.begin(),X.end());
    vector<vector<pii>> f(m);
    for(int i=0;i<m;i++) for(int x=1;x<=i;x++){
        if(X[i]%X[x]==0){
            int y=lower_bound(X.begin(),X.end(),X[i]/X[x])-X.begin();
            f[i].push_back({x,y});
        }
    }

    vector<int> d(m);
    for(int i=0;i<n;i++){
        int x;cin >> x;
        if(M%x!=0) continue;
        x=lower_bound(X.begin(),X.end(),x)-X.begin();
        d[x]++;
    }

    int res=inf;
    function<void(int,int,int,int,int)> dfs = [&](int t,int x,int c,int sum,int cnt){
        if(sum>S) return;
        if(!t){
            res=min(res,cnt+abs(S-sum-d[0]));
            return;
        }
        for(auto [i,j]:f[t]){
            if(i>x) break;
            int nc=(i==x?c+1:1);
            dfs(j,i,nc,sum+X[i],cnt+(nc<=d[i]?-1:1));
        }
    };
    dfs(m-1,m-1,0,0,n-d[0]);
    cout << (res==inf?-1:res) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}