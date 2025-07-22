#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 2e5+5;

void solve(){   
    int n;cin >> n;
    int total=0;
    for(int i=1;i<=n;i++){
        int a,b,c,d;cin >> a >> b >> c >> d;
        if(b>d) total+=a+b-d;
        else if(a>c) total+=a-c;
    }
    cout << total << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}