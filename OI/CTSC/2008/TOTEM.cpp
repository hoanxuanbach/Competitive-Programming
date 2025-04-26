#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
const int mod=(1<<24);
const int maxn=200005;
int n,p[maxn],L[maxn],R[maxn],bit[maxn];
int query(int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
    return res;
}
void update(int x,int val){
    for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
}
void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> p[i];
    for(int i=1;i<=n;i++){L[i]=query(p[i]);R[i]=p[i]-1-L[i];update(p[i],1);}
    int ans=0;
    for(int i=1;i<=n;i++){
        int x=n-i-R[i];
        ans-=x*(x-1)*(x-2)/6;
    }
    memset(bit,0,sizeof(bit));
    for(int i=1;i<=n;i++){ans+=(n-i-R[i])*query(p[i]);update(p[i],L[i]);}
    memset(bit,0,sizeof(bit));
    for(int i=1;i<=n;i++){ans+=(n-i-R[i])*(L[i]*(i-1)-query(p[i])-L[i]*(L[i]-1)/2);update(p[i],i);}
    memset(bit,0,sizeof(bit));
    for(int i=n;i>=1;i--){ans+=(n-i-R[i])*(query(p[i])-R[i]*(R[i]+1)/2);update(p[i],p[i]);}
    cout << ans%mod << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
