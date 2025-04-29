#include<bits/stdc++.h>
using namespace std;
#define int long long
int x[]={0,1,3};
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    if(n<=3) cout << 2*n+1 << '\n';
    else cout << ((n+2)/3)*4+x[(n+2)%3] << '\n';
}
