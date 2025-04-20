#include<bits/stdc++.h>
using namespace std;

signed main(){
    freopen("apio-2013-taskauthor_6.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int V=17;
    cout << 2*V-1 << '\n';
    for(int i=0;i<V-1;i++){
        cout << 1+(i>=1) << ' ';
        cout << i+V-1 << ' ' << 0 << ' ';
        if(i) cout << i-1 << ' ' << 0 << ' ';
        cout << '\n';
    }
    cout << 0 << '\n';
    for(int i=V;i<=2*V-2;i++){
        cout << 1 << ' ' << i-V << ' ';
        if(i==2*V-2) cout << 0 << '\n';
        else cout << -(1<<(i-V)) << '\n';
    }
    cout << 8 << '\n';
    for(int i=0;i<8;i++) cout << 2*V-2 << ' ' << V-1 << '\n';
}
