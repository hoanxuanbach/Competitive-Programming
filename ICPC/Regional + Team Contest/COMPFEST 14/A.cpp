#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n,m;cin >> n >> m;
    if(m==1) cout << n-1 << '\n';
    else cout << n*(m-1) << '\n';
}
