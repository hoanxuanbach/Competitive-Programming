#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 998244353;

void solve(){

    auto get = [&](int x){
        int s=0;
        while(x) s+=x%10,x/=10;
        return s;
    };
    int k;cin >> k;
    int x=k,s=get(k);
    while(k%s!=get(x)%s) x+=k;

    int cnt=(k-get(x))/s;
    cout << x;
    for(int i=0;i<cnt;i++) cout << k;
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}