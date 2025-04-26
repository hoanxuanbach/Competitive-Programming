#include<bits/stdc++.h>
using namespace std;

signed main(){
    //freopen("PUN.INP","r",stdin);
    //freopen("PUN.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,cur=1,ans=0;cin >> n;
    for(int i=1;i<=n;i++){
        char c;cin >> c;
        cur&=(c=='T');
        if(i%(n/10)==0){ans+=cur;cur=1;}
    }
    cout << ans << '\n';
}
