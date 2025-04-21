#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a,b,c;
void add(ll x,ll y){
    while(x){
        ll t=a/x;
        a-=x*t;b-=y*t;
        swap(a,x),swap(b,y);
    }
    c=__gcd(c,y);
    if(c) b%=c;
}
signed main(){
    int n,p,q;cin >> n >> p >> q;
    for(int i=1;i<n;i++){
        int x,y;cin >> x >> y;
        add(x-p,y-q);
    }
    if(!a || !c) cout << -1 << '\n';
    else cout << abs(a*c) << '\n';
}
