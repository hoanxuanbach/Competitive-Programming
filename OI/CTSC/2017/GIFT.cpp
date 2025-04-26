#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int maxn=220005;
int n,a[maxn],ans,sum[(1<<18)+5];
int query(int x){
    int d=(x>>9),r=x&((1<<9)-1),res=0;
    for(int i=d;;i=(i-1)&d){
        res=(res+sum[i<<9|r])%mod;
        if(i==0) break;
    }
    return res;
}
void update(int x,int val){
    int d=x>>9,r=x&((1<<9)-1),nr=r^((1<<9)-1);
    for(int i=nr;;i=(i-1)&nr){
        sum[d<<9|r|i]=(sum[d<<9|r|i]+val)%mod;
        if(i==0) break;
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=n;i>=1;i--){
        int dp=query(a[i]);
        update(a[i],dp+1);
        ans=(ans+dp)%mod;
    }
    cout << ans << '\n';
}
