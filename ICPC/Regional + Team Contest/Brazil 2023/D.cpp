#include<bits/stdc++.h>
using namespace std;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,x,y;cin >> n >> x >> y;
    x=(1<<(n-1))-abs(x-(1<<(n-1)));y=(1<<(n-1))-abs(y-(1<<(n-1)));
    int cx=n-1,cy=n-1;
    for(int i=0;i<=n-2;i++){
        if(x&(1<<i)) break;
        else cx--;
    }
    for(int i=0;i<=n-2;i++){
        if(y&(1<<i)) break;
        else cy--;
    }
    cout << max(cx,cy) << '\n';
}
