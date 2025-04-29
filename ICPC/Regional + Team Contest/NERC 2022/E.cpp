#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
int len,n,a[maxn],c[maxn],d[maxn],ans[maxn],minlen,maxlen;
bool check(int l,int r){
    c[0]=d[0]=0;
    for(int i=1;i<=n;i++){
        c[i]=max(a[i],c[i-1]+l);
        d[i]=min(a[i+1],d[i-1]+r);
        if(c[i]>d[i]) return false;
    }
    if(d[n]<a[n+1]) return false;
    for(int i=n-1;i>=0;i--) ans[i]=min(d[i],ans[i+1]-l);
    return true;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> len >> n;ans[n]=a[n+1]=len;
    for(int i=1;i<=n;i++) cin >> a[i];
    int l=1,r=1e9;
    while(r>=l){
        int mid=(r+l)>>1;
        if(check(mid,1e9)){minlen=mid;l=mid+1;}
        else r=mid-1;
    }
    l=minlen;r=1e9;
    while(r>=l){
        int mid=(r+l)>>1;
        if(check(minlen,mid)){maxlen=mid;r=mid-1;}
        else l=mid+1;
    }
    check(minlen,maxlen);
    for(int i=0;i<n;i++) cout << ans[i] << ' ' << ans[i+1] << '\n';
}
