#include<bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define isz(x) ((int)(x).size())
#define sumof(x) accumulate(all(x), 0ll)

const int N=201;
int n;
string s;
int pf[N][2];

void solve(){
   cin >> n >> s;
   for (int i=1; i<=n; ++i){
      for (int j=0; j<2; ++j) pf[i][j]=pf[i-1][j];
      ++pf[i][s[i-1]=='L'];
   }
   for (int k=1; k<n; ++k){
      int t0=pf[k][0], t1=pf[k][1];
      int f0=pf[n][0]-t0, f1=pf[n][1]-t1;
      if (t0!=f0 && t1!=f1){
         cout << k;
         return;
      }
   }
   cout << -1;
}

int32_t main(){
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   int ntests=1;
   // cin >> ntests;
   for (int i=1; i<=ntests; ++i) solve();
   return 0;
}
