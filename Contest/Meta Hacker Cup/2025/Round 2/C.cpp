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

void solve(){
    int n,k,m;cin >> n >> k >> m;

    vector<vector<pii>> f(n+1);
    vector<vector<int>> P(m),S(m);
    for(int i=0;i<m;i++){
        int x;cin >> x;
        P[i].assign(x,0);
        S[i].assign(x,0);
        for(int j=0;j<x;j++){
            cin >> P[i][j];
            f[P[i][j]].push_back({i,j});
        }
    }
    vector<int> d(n+1,inf),q;
    q.push_back(1);d[1]=0;
    while(!q.empty()){
        vector<int> nq;
        for(int x:q) for(auto [i,j]:f[x]){
            for(int t=1;t<=k && j+t<(int)P[i].size();t++){
                int y=P[i][j+t];
                if(d[y]<=d[x]) break;
                d[y]=d[x]+1;
                nq.push_back(y);
            }
        }
        swap(q,nq);
        sort(q.begin(),q.end());
        q.erase(unique(q.begin(),q.end()),q.end());
    }
    int res=0;
    for(int i=1;i<=n;i++){
        if(d[i]==inf) res-=i;
        else res+=d[i]*i;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    for(int t=1;t<=test;t++){
        cout << "Case #" << t << ": ";
        solve();
    }
}
