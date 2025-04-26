#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    int l,r;cin >> l >> r;
    int cur=l*(l+1);
    for(int i=l+2;i<=r;i++){
        cur=cur*i/__gcd(i,cur);
        cout << cur << '\n';
    }
    cout << cur << '\n';
}
