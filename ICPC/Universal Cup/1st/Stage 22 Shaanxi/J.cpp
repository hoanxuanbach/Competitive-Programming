#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

#define stint basic_string<int>

void solve(){
    int n,m;cin >> n >> m;
    vector<int> l(n+1),r(n+1),a(n+1);
    for(int i=1;i<=n;i++){
        int type;cin >> type;
        if(type==1) cin >> l[i] >> r[i];
        else cin >> a[i];
    }

    function<vector<stint>(int)> dfs = [&](int u){
        if(a[u]) return vector<stint>{{a[u]}};
        int x=l[u],y=r[u];
        vector<stint> X=dfs(x),Y=dfs(y);
        
        vector<stint> Z((int)X.size()+(int)Y.size());
        for(int i=0;i<(int)X.size();i++) for(int j=0;j<(int)Y.size();j++){
            stint A=X[i]+Y[j];
            if(Z[i+j].empty()) Z[i+j]=A;
            else Z[i+j]=min(Z[i+j],A);
            A=Y[j]+X[i];
            if(Z[i+j+1].empty()) Z[i+j+1]=A;
            else Z[i+j+1]=min(Z[i+j+1],A);
        }

        return Z;
    };
    vector<stint> dp=dfs(1);
    stint ans=dp[m];
    for(int i=m-2;i>=0;i-=2) ans=min(ans,dp[i]);
    for(int x:ans) cout << x << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}