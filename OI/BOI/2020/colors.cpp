#include<bits/stdc++.h>
using namespace std;
#define int long long
int query(int x){
    cout << "? " << x << endl;
    int a;cin >> a;
    return a;
}
void solve(){
    int n;cin >> n;
    int pre=0,l=1,r=n-1,d=0,Min=0,Max=0;
    while(r>=l){
        int mid=(r+l)/2;
        if(d) pre+=mid;
        else pre-=mid;
        d^=1;Min=min(Min,pre);Max=max(Max,pre);
        l=mid+1;
    }
    pre=-Min+1;query(pre);
    r=n-1;l=1;d=0;
    int ans=n;
    while(r>=l){
        int mid=(r+l)/2,x=0;
        if(d){x=query(pre+mid);pre+=mid;}
        else{x=query(pre-mid);pre-=mid;}
        d^=1;
        if(x){r=mid-1;ans=mid;}
        else l=mid+1;
    }
    cout << "= " << ans << endl;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;
    while(t--) solve();
}