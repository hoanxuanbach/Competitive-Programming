#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int> 
const int maxn = 2e5+5;
const int mod = 998244353;


void solve(){
    int n,m,A,B;cin >> n >> m >> A >> B;
    
    int k=0;
    vector<int> f(n*m);
    for(int i=0;i<n*m;i++){
        int x;cin >> x;
        if(x) f[x-1]++;
        else k++;
    }
    sort(f.begin(),f.end(),greater<int>());
    int res=(n*m-k)*A;
    for(int i=0;i<n*m;i++){
        int add=f[i]*(B*i-A)+B*k;
        if(add<0) res+=add;
        else break;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}