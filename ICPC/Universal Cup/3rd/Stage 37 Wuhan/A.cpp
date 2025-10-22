#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e9;

void solve(){
    int n,q;cin >> n >> q;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];

    vector<int> l(n+1,1),r(n+1,inf);
    for(int i=1;i<=q;i++){
        int x,a,b;cin >> x >> a >> b;
        l[x]=max(l[x],a);
        r[x]=min(r[x],b);
    }
    int res=0;
    for(int i=1;i<=n;i++){
        if(l[i]>r[i]){
            cout << -1 << '\n';
            return;
        }
        else if(a[i]<l[i]) res+=l[i]-a[i];
        else if(a[i]>r[i]) res+=a[i]-r[i];
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}