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
    int n,m;cin >> n >> m;
    vector<vector<vector<int>>> F(m+1);
    for(int i=1;i<=n;i++){
        int p,k;cin >> p >> k;
        vector<int> a(k);
        for(int j=0;j<k;j++) cin >> a[j];
        F[p].push_back(a);
    }

    int cnt=0;
    vector<bool> add(m+1);
    vector<int> vis(m+1);
    for(int i=m;i>=1;i--){
        if(F[i].empty()) continue;
        for(auto v:F[i]) for(int x:v) vis[x]++;
        int sz=(int)F[i].size();
        
        vector<int> cur;
        for(int x:F[i][0]) if(vis[x]==sz) cur.push_back(x);
        bool check=false;
        for(int x:cur) if(!add[x]) check=true;
        
        if(!check){
            cout << "no\n";
            return;
        }
        for(auto v:F[i]) for(int x:v){
            vis[x]--;
            if(!add[x]) add[x]=true,cnt++;
        }
        if(cnt>(m-i+1)){
            cout << "no\n";
            return;
        }
    }
    cout << "yes\n";
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
