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
    int L,W,H;cin >> L >> W >> H;
    int P,Q,R;cin >> P >> Q >> R;

    int n;cin >> n;
    vector<pii> A(n),B(n),C(n);
    for(int i=0;i<n;i++){
        cin >> A[i].first >> B[i].first >> C[i].first;
        A[i].second=B[i].second=C[i].second=i;
    }

    int cnt=1;
    auto cal = [&](vector<pii> X,int k){
        int d=n/(k+1);
        sort(X.begin(),X.end());
        vector<int> res(n);
        for(int i=0;i<n;i++) res[X[i].second]=i/d;
        for(int i=1;i<=k;i++) cnt=cnt*(X[i*d].first-X[i*d-1].first)%mod;
        return res;
    };

    int d=(P+1)*(Q+1)*(R+1);
    if(n%d!=0){
        cout << 0 << '\n';
        return;
    }
    d=n/d;
    vector<int> X=cal(A,P);
    vector<int> Y=cal(B,Q);
    vector<int> Z=cal(C,R);

    vector<vector<vector<int>>> f(P+1,vector<vector<int>>(Q+1,vector<int>(R+1)));
    for(int i=0;i<n;i++) f[X[i]][Y[i]][Z[i]]++;

    bool check=true;
    for(int i=0;i<=P;i++) for(int j=0;j<=Q;j++) for(int k=0;k<=R;k++) if(f[i][j][k]!=d) check=false;
    cout << (check?cnt:0) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
