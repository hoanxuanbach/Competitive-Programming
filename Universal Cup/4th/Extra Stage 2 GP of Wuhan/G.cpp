#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int mod = 998244353;
#define ld long double

void solve(){
    int n,R;cin >> n >> R;
    vector<int> X(n),L(n);
    for(int i=0;i<n;i++) cin >> X[i];
    for(int i=0;i<n;i++) cin >> L[i];

    ld l=0,r=1;
    for(int t=0;t<100;t++){
        ld d=(l+r)/2,S=0;
        for(int i=0;i<n;i++){
            ld x=X[i]*d;
            x=min(max(x,-(ld)L[i]),(ld)L[i]);
            S+=x*x;
        }
        if(S<=R) l=d;
        else r=d;
    }
    ld d=(l+r)/2;
    for(int i=0;i<n;i++){
        ld x=X[i]*d;
        x=min(max(x,-(ld)L[i]),(ld)L[i]);
        cout << setprecision(9) << fixed << x << ' ';
    } 
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}