#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const int inf = 1e18;
const int maxn = 200005;
const int S = 2;
const int mod[] = {998244353,1000000007};
const int base[] = {101,31};
int rand(int l,int r){
    return l+rng()%(r-l+1);
}
 
int n,a[maxn],cnt[maxn];
 
void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i],a[i]--;
    long long res=0;
    for(int l=1;l<=n;l++){
        int mx=0,k=0;
        for(int r=l;r<=n;r++){
            k+=!cnt[a[r]],cnt[a[r]]++;
            mx=max(mx,cnt[a[r]]);
            if(k*mx==(r-l+1)) res++;
        }
        for(int r=l;r<=n;r++)
            cnt[a[r]]--;
    }
    cout << res << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
