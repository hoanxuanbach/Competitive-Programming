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
    int K;cin >> K;
    vector<int> f(K);
    vector<array<int,3>> A,B;
    for(int x=0;x<K;x++){
        f.assign(K,0);f[x]=1;
        for(int i=x;i>=3;i--){
            f[i-3]+=2*f[i];
            f[i-2]-=f[i];
            f[i]=0;
        }
        cout << f[0] << ' ' << f[1] << ' ' << f[2] << '\n';
        if(x<K/2) A.push_back({f[0],f[1],f[2]});
        else B.push_back({f[0],f[1],f[2]});
    }
    reverse(B.begin(),B.end());

    K/=2;
    vector<vector<array<int,2>>> fA(3),fB(3);

    function<void(
    vector<vector<array<int,2>>>& ,   // note the &
    vector<array<int,3>>& ,             // note the &
    int, int, array<int,3>
    )> dfs = [&](auto&& ff, auto&& X, int k, int d, array<int,3> S) {
        if(k==K){
            ff[d].push_back({S[0]-S[1]-S[2],S[1]-S[2]});
            return;
        }
        if(d>=2) dfs(ff,X,k+1,0,array<int,3>{S[0]+X[k][0],S[1]+X[k][1],S[2]+X[k][2]});
        dfs(ff,X,k+1,min(d+1,2LL),S);
    };

    array<int,3> S = {0,0,0};
    dfs(fA,A,0,2,S);
    dfs(fB,B,0,2,S);

    int res=0;
    for(int i=0;i<=2;i++) for(int j=2-i;j<=2;j++){
        map<int,vector<int>> mp;
        for(auto [x,a]:fB[j]) mp[a].push_back(x);
        for(auto [x,a]:fA[i]){
            auto it = mp.find(-a);
            if(it!=mp.end()) for(int y:it->second) if(x+y>0){
                cout << x+y << endl;
                res+=x+y;
            }
        }
    }
    cout << res << '\n';

    /*
    0 0 1
    -2 1 2
    -8 6 3
    36 -16 -16
    */
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
