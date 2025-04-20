#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e18;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int l=-inf,r=inf,p=0;
    int n;cin >> n;
    for(int i=1;i<=n;i++){
        int x;cin >> x;
        if(i&1) r=min(r,x-p);
        else l=max(l,p-x);
        p=x*2-p;
    }
    cout << max(0LL,r-l+1) << '\n';
}
