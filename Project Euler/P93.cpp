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

    map<vector<int>,vector<pii>> mp;
    function<vector<pii>(vector<int>)> dfs = [&](vector<int> X){
        if(mp.find(X)!=mp.end()) return mp[X];
        int sz=(int)X.size();
        if(sz==1) return mp[X]={pii{X[0],1}};

        vector<pii> C;
        for(int i=1;i<(1<<sz)-1;i++){
            vector<int> A,B;
            for(int j=0;j<sz;j++){
                if(i>>j&1) A.push_back(X[j]);
                else B.push_back(X[j]);
            }
            vector<pii> P=dfs(A);
            vector<pii> Q=dfs(B);
            for(auto p:P) for(auto q:Q){
                pii x={p.first*q.second+p.second*q.first,p.second*q.second};
                C.push_back(x);
                x={p.first*q.second-p.second*q.first,p.second*q.second};
                C.push_back(x);
                x={p.first*q.first,p.second*q.second};
                C.push_back(x);
                x={p.first*q.second,p.second*q.first};
                if(x.second) C.push_back(x);
            }
        }
        return mp[X]=C;
    };

    int val=-1;
    string S;
    for(int i=0;i<(1<<10);i++){
        vector<int> X;
        for(int j=0;j<10;j++) if(i>>j&1) X.push_back(j);
        if((int)X.size()!=4) continue;
        vector<pii> A=dfs(X);
        set<int> ss;
        for(auto [x,y]:A) if(x%y==0) ss.insert(x/y);
        int x=1;
        while(ss.find(x)!=ss.end()) x++;

        string C;
        for(int c:X) C+=to_string(c);
        if(x>val) val=x,S=C;
    }
    cout << val-1 << ' ' << S << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
