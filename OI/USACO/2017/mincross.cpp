#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define int long long
int n,a[maxn],p[maxn],bit[maxn],x[maxn],b[maxn];
int query(int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
    return res;
}
void update(int x){
    for(int i=x;i<=n;i+=(i&(-i))) bit[i]++;
}
int get(){
    for(int i=1;i<=n;i++) bit[i]=0;
    for(int i=1;i<=n;i++) p[a[i]]=i;
    for(int i=1;i<=n;i++) x[i]=p[b[i]];
    int ans=0,res=0;
    for(int i=n;i>=1;i--){res+=query(x[i]);update(x[i]);}
    ans=res;
    for(int i=n;i>=1;i--){
        res+=2*x[i]-n-1;
        ans=min(ans,res);
    }
    return ans;
}
signed main(){
    freopen("mincross.in","r",stdin);
    freopen("mincross.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];
    int ans=get();
    for(int i=1;i<=n;i++) swap(a[i],b[i]);
    ans=min(ans,get());
    cout << ans << '\n';
}
