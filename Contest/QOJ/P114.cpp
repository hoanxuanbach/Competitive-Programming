#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int n,k;cin >> n >> k;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i];

    auto check = [&](int X){
        int lt=inf,cur=inf,fst=-1,lst=-1;
        int cnt=0;
        for(int i=0;i<n;i++){
            if(a[i]<=X/2){
                cnt++;
                if(fst==-1) lt=cur,fst=i;
                else if(cur+max(a[lst],a[i])<=X) cnt++;
                cur=inf;lst=i;
            }
            else cur=min(cur,a[i]);
        }
        cur=min(cur,lt);
        if(cur+max(a[fst],a[lst])<=X) cnt++;
        return k<=cnt;
    };
    int l=0,r=2e9,res=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
