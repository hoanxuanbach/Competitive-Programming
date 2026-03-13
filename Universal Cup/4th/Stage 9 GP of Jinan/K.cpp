#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 7;

int n, a[N], b[N];
vector<vector<int>> pos;

void solve() {
    cin >> n;
    pos.assign(n + 1, vector<int>());
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]].push_back(i);
        b[i] = 0;
    }

    vector<int> vt1, vt2;
    for (int i=1; i <= n; ++i) {
        if (pos[i].size() == 0) {
            vt2.push_back(i);
        } else if (pos[i].size() == 2) {
            vt1.push_back(i);
        }
    }
    int score = 0;
    vector<int> used;
    for (int i = 0; i < vt1.size(); ++i) {
        int l = pos[vt1[i]][0], r = pos[vt1[i]][1];
        if (l == 1) {
            score++;
            used.push_back(vt2[i]);
            used.push_back(vt2[i]);
        }
        else {
            b[l-1] = b[r-1] = vt2[i];
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (pos[a[i]].size() == 1) used.push_back(a[i]);
        if (b[i] == 0) {
            b[i] = used.back();
            used.pop_back();
        }
    }
    
    cout << score << '\n';
    for (int i = 1; i <= n; ++i) cout << b[i] << " ";
    cout << '\n';
}

signed main(){
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int num_test = 1;
    cin >> num_test;
    while(num_test--) solve();
}
