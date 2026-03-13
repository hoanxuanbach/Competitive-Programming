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

vector<pii> f[10][10];

void solve(){
    vector<int> pw(10);pw[0]=1;
    for(int i=1;i<=9;i++) pw[i]=pw[i-1]*10;

    function<vector<pii>(int,int)> dfs = [&](int l,int r){
        if(!f[l][r].empty()) return f[l][r];
        if(l==r) return f[l][r]={pii{l,1}};


        vector<pii> C;
        int T=0;
        for(int i=l;i<=r;i++) T=T*10+i;
        C.push_back({T,1});

        for(int i=l;i<r;i++){
            vector<pii> P=dfs(l,i);
            vector<pii> Q=dfs(i+1,r);
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
        for(int i=0;i<(int)C.size();i++){
            int g=__gcd(C[i].first,C[i].second);
            C[i].first/=g;C[i].second/=g;
            if(C[i].second<0){
                C[i].second=-C[i].second;
                C[i].first=-C[i].first;
            }
        }
        sort(C.begin(),C.end());
        C.erase(unique(C.begin(),C.end()),C.end());
        cout << l << ' ' << r << ' ' << (int)C.size() << endl;
        return f[l][r]=C;
    };
    dfs(1,9);

    int res=0;
    for(auto [a,b]:f[1][9]) if(b==1 && a>0) res+=a; 
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
