#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 998244353;
const int S = 100;

void solve(){
    int n,k;cin >> n >> k;
    
    auto cal = [&](vector<pair<int,int>> P){
        int T=0;
        vector<vector<int>> f(S+1);
        for(auto [x,y]:P) T+=x,f[x].push_back(y);

        T=min(T,k*S);
        vector<vector<int>> dp(T+1,vector<int>(k+1,-1));

        dp[0][0]=0;
        for(int i=1;i<=S;i++){
            sort(f[i].begin(),f[i].end(),greater<int>());
            while((int)f[i].size()>k) f[i].pop_back();
            int sz=(int)f[i].size();
            for(int j=1;j<sz;j++) f[i][j]+=f[i][j-1];
            for(int x=T;x>=0;x--) for(int a=0;a<k;a++) for(int b=1;b<=min(k-a,sz);b++){
                if(dp[x][a]!=-1) dp[x+i*b][a+b]=max(dp[x+i*b][a+b],dp[x][a]+f[i][b-1]);
            }
        }
        return dp;
    };  

    vector<pair<int,int>> A,B;
    for(int i=0;i<n;i++){
        int a,b;cin >> a >> b;
        if(a<=S) A.push_back({a,b});
        else B.push_back({b,a});
    }

    int res=0;
    vector<vector<int>> X=cal(A),Y=cal(B);


    for(int i=0;i<=k;i++){
        for(int x=0;x<(int)X.size();x++) for(int y=0;y<(int)Y.size();y++){
            if(X[x][i]==-1 || Y[y][k-i]==-1) continue;
            res=max(res,(x+Y[y][k-i])*(y+X[x][i]));
        }
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}