#include<bits/stdc++.h>
using namespace std;
int num[15];
void solve(){
    int n;cin >> n;
    for(int i=1;i<=10;i++) num[i]=0;
    for(int i=1;i<=n;i++){
        int b,d;cin >> b >> d;
        num[d]=max(num[d],b);
    }
    int ans=0;
    for(int i=1;i<=10;i++){
        if(num[i]==0){
            cout <<  "MOREPROBLEMS\n";return;
        }
        ans+=num[i];
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t;cin >> t;
    while(t--) solve();
}

