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
    map<vector<int>,int> mp;
    function<int(vector<int>)> get = [&](vector<int> x){
        if((int)x.size()>=4) return inf;
        if(x==vector<int>{1}) return 0LL;
        if(mp.find(x)!=mp.end()) return mp[x];
        int d=x.back(),res=inf;x.pop_back();
        for(int a=1;a<d;a++){
            int b=d-a;
            vector<int> nx=x;
            nx.push_back(a);
            nx.push_back(b);
            sort(nx.begin(),nx.end());
            nx.erase(unique(nx.begin(),nx.end()),nx.end());
            res=min(res,get(nx)+1);
        }
        x.push_back(d);
        return mp[x]=res;
    };
    int T=0;
    for(int i=1;i<=200;i++){
        cout << i << endl;
        T+=get({i});
    }
    cout << T << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
