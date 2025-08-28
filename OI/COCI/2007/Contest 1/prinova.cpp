#include<bits/stdc++.h>
using namespace std;
#define maxn 105
int n,p[maxn],a,b,ans,id;
signed main(){
    //freopen("PRI.INP","r",stdin);
    //freopen("PRI.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> p[i];
    sort(p+1,p+n+1);
    cin >> a >> b;
    if(a%2==0) a++;
    if(b%2==0) b--;
    if((p[1]-a)>ans){ans=(p[1]-a);id=a;}
    if((b-p[n])>ans){ans=b-p[n];id=b;}
    for(int i=2;i<=n;i++){
        int x=max(a,p[i-1]),y=min(b,p[i]);
        if(x%2==0) x++;
        if(y%2==0) y--;
        int l=(p[i-1]+p[i])/2,r=l;
        if(l%2==0) l--;
        if(r%2==0) r++;
        if(y<=l && (y-p[i-1])>ans){ans=y-p[i-1];id=y;}
        if(x>=r && (p[i]-x)>ans){ans=p[i]-x;id=x;}
        if(x<=r && y>=r && (p[i]-r)>ans){ans=p[i]-r;id=r;}
    }
    cout << id << '\n';
}