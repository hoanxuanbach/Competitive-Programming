#include<bits/stdc++.h>
using namespace std;
#define maxn 200005
int num[maxn],n,k,q,cnt[maxn],a[maxn];
bool check(int mid){
    int x=0;
    for(int i=0;i<k;i++) cnt[i]=0;
    for(int i=1;i<=mid;i++){
        cnt[a[i]]++;
        if(cnt[a[i]]==num[a[i]]) x++;
    }
    if(x==q) return true;
    for(int i=mid+1;i<=n;i++){
        cnt[a[i]]++;
        if(cnt[a[i]]==num[a[i]]) x++;
        if(cnt[a[i-mid]]==num[a[i-mid]]) x--;
        cnt[a[i-mid]]--;
        if(x==q) return true;
    }
    return false;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=q;i++){
        int x,c;cin >> x >> c;
        num[x]=c;
    }
    int l=1,r=n,ans=-1;
    while(r>=l){
        int mid=(r+l)>>1;
        if(check(mid)){ans=mid;r=mid-1;}
        else l=mid+1;
    }
    if(ans==-1) cout << "impossible\n";
    else cout << ans << '\n';
}
