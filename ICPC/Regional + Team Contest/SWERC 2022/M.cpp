#include<bits/stdc++.h>
using namespace std;
void solve(){
    int n,m,w=0,r=0;
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int a,b;cin >> a >>  b;
        r=max(r,a);w=max(w,b);
    }
    if((r+w)>n){
        cout << "IMPOSSIBLE\n";return;
    }
    for(int i=1;i<=r;i++) cout << "R";
    for(int i=1;i<=(n-r);i++) cout << "W";
    cout << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t;cin >> t;
    while(t--) solve();
}



