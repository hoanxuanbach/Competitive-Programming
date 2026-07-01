#include<bits/stdc++.h>

using namespace std;

void solve() {
    int n, x;
    map<int, bool> mp;
    cin >> n >> x;
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        mp[a] = true;
        if (mp.size() == x) {
            res++;
            mp.clear();
            mp[a] = true;
        }
    }
    cout << n - 1 - res;
}
 
signed main(){
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;
    // cin >> test;
    while(test--) solve();
}