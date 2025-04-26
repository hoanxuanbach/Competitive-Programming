#include<bits/stdc++.h>
using namespace std;

int c[105][105];

signed main(){
    freopen("17.out","r",stdin);
    freopen("17.ans","w",stdout);
    int n;cin >> n;
    string s;cin >> s;
    int x=1,y=1;c[x][y]=1;
    for(char k:s){
        int d=c[x][y];
        if(k=='L' || k=='l') y--;
        else if(k=='R' || k=='r') y++;
        else if(k=='U' || k=='u') x--;
        else x++;
        if(k>='A' && k<='Z') c[x][y]=d;
        assert(x>=1 && y>=1 && x<=n && y<=n);
        //cout << x << ' ' << y << '\n';
    }
    cout << n << '\n';
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout << (c[i][j]?'B':'W');
        cout << '\n';
    }
    cout << 17 << '\n';
}
