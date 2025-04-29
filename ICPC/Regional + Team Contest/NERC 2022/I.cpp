#include<bits/stdc++.h>
using namespace std;
int dig(int x,int y){
    cout << "DIG " << x << " " << y << '\n';
    cout.flush();
    int a;cin >> a;
    return a;
}
int query(int x,int y){
    cout << "SCAN " << x << " " << y << '\n';
    cout.flush();
    int a;cin >> a;
    return a;
}
void solve(){
    int n,m;cin >> n >> m;
    int s1=query(1,1)+4,s2=query(1,m)+2-2*m;
    int sx=(s1+s2)/2,sy=s1-sx;
    int mx=query(sx/2,1)+2-sy,my=query(1,sy/2)+2-sx;
    int x1=(sx+mx)/2,x2=sx-x1,y1=(sy+my)/2,y2=sy-y1;
    int a1=dig(x1,y1);
    if(a1==1) dig(x2,y2);
    else{dig(x2,y1);dig(x1,y2);}
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t;cin >> t;
    while(t--) solve();
}
