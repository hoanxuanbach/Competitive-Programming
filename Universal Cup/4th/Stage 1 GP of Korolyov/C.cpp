#include<bits/stdc++.h>
using namespace std;
#define int long long 

void solve(){
    int a,b,s;cin >> a >> b >> s;
    
    int res=a+b;
    for(int x=1;x*x<=s;x++){
        int y=s/x;

        int val=0;
        if(x<a) val+=(a-1)/x;
        if(y<b) val+=(b-1)/y;
        res=min(res,val);

        val=0;
        if(x<b) val+=(b-1)/x;
        if(y<a) val+=(a-1)/y;

        res=min(res,val);
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}