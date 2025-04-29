#include<bits/stdc++.h>
using namespace std;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    char c='S';
    for(int i=0;i<8;i++){
        int a;cin >> a;
        if(a==9) c='F';
    }
    cout << c;
}
