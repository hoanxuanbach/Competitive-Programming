#include<bits/stdc++.h>
using namespace std;
set<int> s;
void f(int x,int y){
    int g=__gcd(x,y);
    for(int i=1;i<=sqrt(g);i++){
        if(g%i==0){s.insert(i);s.insert(g/i);}
    }
}
void solve(){
    s.clear();
    int w,l;cin >> w >> l;
    f(w-1,l-1);f(w-2,l);f(w,l-2);
    s.insert(2);
    cout << (int)s.size() << ' ';
    for(set<int>::iterator it=s.begin();it!=s.end();it++) cout << *it << " ";
    cout << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t;cin >> t;
    while(t--) solve();
}


