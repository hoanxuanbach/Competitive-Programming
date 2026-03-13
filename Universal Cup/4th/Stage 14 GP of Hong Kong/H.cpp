#include<bits/stdc++.h>

using namespace std;
const int N = 5e5 + 7;

string s;
int n;
int nxt[N];

void solve() {
    cin >> s;
    n = (int)s.length(), s = ' ' + s;
    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i + 1]) {
            cout << n - 1 << '\n';
            return;
        }
    }
    cout << n - 2 << '\n';
}
 
signed main(){
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1; cin >> test;
    while(test--) solve();
}