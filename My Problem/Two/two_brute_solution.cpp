#include<bits/stdc++.h>
using namespace std;
const int maxn=200005;
int x[2][maxn],ok[2];
bool check(int x1,int y1,int x2,int y2,int l,int r){
    if(x[x1][y1]<l || x[x1][y1]>r) return false;
    ok[x1]=1;
    if(x[x1^1][y1]>=l && x[x1^1][y1]<=r) ok[x1^1]=1;
    else ok[x1^1]=0;
    for(int i=y1+1;i<=y2;i++){
        bool f0=(x[0][i]>=l && x[0][i]<=r),f1=(x[1][i]>=l && x[1][i]<=r);
        ok[0]&=f0;ok[1]&=f1;
        ok[0]|=(ok[1] && f0);
        ok[1]|=(ok[0] && f1);
    }
    return ok[x2];
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,q;cin >> n;
    for(int i=0;i<=1;i++){
        for(int j=1;j<=n;j++) cin >> x[i][j];
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        int x1,y1,x2,y2,l,r;cin >> x1 >> y1 >> x2 >> y2 >> l >> r;
        cout << (check(x1,y1,x2,y2,l,r)?"YES":"NO") << '\n';
    }
}
