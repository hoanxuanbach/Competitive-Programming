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
const int inf = 1e9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int n,a,b;cin >> n >> a >> b;
    string S;cin >> S;S="#"+S;
    int T=(a+b);

    int dp=0;
    vector<int> A(n+1),B(n+1);
    for(int i=1;i<=n;i++){
        A[i]=A[i-1]+(S[i]=='R');
        B[i]=B[i-1]+(S[i]=='B');
    }

    vector<vector<pii>> P(T);
    vector<vector<int>> cA(T);
    for(int i=1;i<=n;i++){
        A[i]=(i/T)*a-A[i],B[i]=(i/T)*b-B[i];
        cA[i%T].push_back(A[i]);
        P[i%T].push_back({A[i],B[i]});
    }
    cA[0].push_back(0);
    P[0].push_back({0,0});

    vector<vector<vector<int>>> g(T),f(T);
    auto compress = [&](vector<int> &C){
        sort(C.begin(),C.end());
        C.erase(unique(C.begin(),C.end()),C.end());
    };
    auto get_compress = [&](vector<int> &C,int x){
        int t=upper_bound(C.begin(),C.end(),x)-C.begin();
        return t;
    };

    for(int i=0;i<T;i++){
        compress(cA[i]);
        int sA=(int)cA[i].size();
        g[i].assign(sA+1,{});
        f[i].assign(sA+1,{});
        for(auto [x,y]:P[i]){
            x=get_compress(cA[i],x);
            for(int j=x;j<=sA;j+=(j&(-j))) g[i][j].push_back(y);
        }
        for(int j=1;j<=sA;j++){
            compress(g[i][j]);
            f[i][j].assign((int)g[i][j].size()+1,-inf);
        }
    }
    auto update = [&](int id,int x,int y,int val){
        x=get_compress(cA[id],x);
        for(int i=x;i<=(int)cA[id].size();i+=(i&(-i))){
            for(int j=get_compress(g[id][i],y);j<=(int)g[id][i].size();j+=(j&(-j))) f[id][i][j]=max(f[id][i][j],val);
        }
    };
    auto query = [&](int id,int x,int y){
        int res=-inf;
        x=get_compress(cA[id],x);
        for(int i=x;i>=1;i-=(i&(-i))) for(int j=get_compress(g[id][i],y);j>=1;j-=(j&(-j))) res=max(res,f[id][i][j]);
        return res;
    };

    update(0,0,0,0);
    for(int i=1;i<=n;i++){
        dp=max(dp,query(i%T,A[i],B[i])+i/T);
        update(i%T,A[i],B[i],dp-i/T);
    }
    cout << dp << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
