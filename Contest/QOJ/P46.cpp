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
    int n;cin >> n;
    vector<int> a(n),f(n);
    vector<int> d(n,inf);d[0]=0;

    int m=0;
    vector<vector<int>> g(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        f[i]=lower_bound(d.begin(),d.end(),a[i])-d.begin();
        d[f[i]]=a[i];
        g[f[i]-1].push_back(i);
        m=max(m,f[i]);
    }
    for(int i=0;i<m;i++) reverse(g[i].begin(),g[i].end());

    int cnt=0;
    vector<int> T;
    while(true){
        int i=(int)T.size();
        if(i==m){
            cnt++;
            T.clear();
            continue;
        }
        while(!T.empty() && !g[i].empty() && T.back()>=g[i].back()) g[i].pop_back();
        if(g[i].empty()) break;

        if(!T.empty() && a[g[i].back()]<=a[T.back()]) T.pop_back();
        else{
            T.push_back(g[i].back());
            g[i].pop_back();
        }
    }   
    cout << n-cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
