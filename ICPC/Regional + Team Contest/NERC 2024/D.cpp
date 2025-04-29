#include<bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define isz(x) ((int)(x).size())
#define sumof(x) accumulate(all(x), 0ll)



void solve(){
   int b, n;
   cin >> b >> n;
   pair<int, int> ans={-1, -1};
   for (int k=1, cur=b%n; k<=n; ++k){
      if (cur==0){
         ans={1, k};
         break;
      }
      if (cur==1){
         ans={2, k};
         break;
      }
      if (cur==n-1){
         ans={3, k};
         break;
      }
      cur=cur*b%n;
   }
   if (ans.first==-1) cout << 0;
   else cout << ans.first << ' ' << ans.second;
   cout << '\n';
}

int32_t main(){
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   int ntests=1;
   cin >> ntests;
   for (int i=1; i<=ntests; ++i) solve();
   return 0;
}
