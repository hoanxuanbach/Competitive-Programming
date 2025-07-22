#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 2e5+5;

void solve(){   
    int n,m;cin >> n >> m;
    if(min(n,m)==1 || (n==2 && m==2)) cout << "NO\n";
    else cout << "YES\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}