#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int N;cin >> N;
    vector<int> p(N),X;
    for(int i=2;i<N;i++){
        if(!p[i]){
            X.push_back(i);
            for(int j=i;j<N;j+=i) p[j]=i;
        }
    }

    int n;cin >> n;
    int S=(int)X.size(),T=sqrtl(n)+1;

    vector<vector<int>> f(S,vector<int>(T,-1)),g(S,vector<int>(T,-1));
    function<int(int,int)> cal = [&](int i,int x){
        if(x>n) return 0LL;
        if(i==S) return 1LL;
        if(x<T){
            if(f[i][x]!=-1) return f[i][x];
        }
        else if(g[i][n/x]!=-1) return g[i][n/x];
        int res=cal(i+1,x)+cal(i,x*X[i]);
        if(x<T) return f[i][x]=res;
        else return g[i][n/x]=res;
    };
    cout << cal(0,1) << '\n';

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
