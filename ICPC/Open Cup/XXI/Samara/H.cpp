#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define int long long
int n,m,k,last[maxn],c[maxn],x[maxn],y[maxn],z[maxn],inv[maxn];
int power(int a,int mod){
    int t=mod-2,res=1;
    while(t){
        if(t&1) res=(res*a)%mod;
        t>>=1;a=(a*a)%mod;
    }
    return res;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> last[0] >> k;
    for(int i=1;i<=k;i++){
        cin >> c[i] >> x[i] >> y[i] >> z[i];
        int p=last[i-1];
        inv[i]=power(x[i],z[i]);
        for(int j=1;j<=c[i];j++) p=(p*x[i]+y[i])%z[i];
        last[i]=p;
    }
    int cnt=0,ans=0;
    for(int i=k;i>=1;i--){
        int p=last[i];
        if(p<m) m--;
        else if((n-cnt)<=m){ans++;m--;}
        cnt++;
        for(int j=1;j<c[i];j++){
            p=(p+z[i]-y[i])*inv[i]%z[i];
            if(p<m) m--;
            else if((n-cnt)<=m){ans++;m--;}
            cnt++;
        }
    }
    if(last[0]<m) m--;
    else if((n-cnt)<=m){ans++;m--;}
    cnt++;
    cout << ans << '\n';
}