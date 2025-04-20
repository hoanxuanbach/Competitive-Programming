#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,p[maxn],cnt[maxn];

bool check(int d){
    for(int i=0;i<=n;i++) cnt[i]=0;
    for(int i=0;i<n;i++){
        int x=p[i];
        //x-d->x+d
        int l=(i-(x+d)+2*n)%n,r=(i-(x-d)+2*n)%n;
        if(l>r) cnt[0]++;
        cnt[l]++;cnt[r+1]--;
    }
    for(int i=0;i<n;i++){
        if(i) cnt[i]+=cnt[i-1];
        if(cnt[i]==n) return true;
    }
    return false;
}

int cal(){
    int l=0,r=n/2-1,res=n/2;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    return res;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for(int i=0;i<n;i++) cin >> p[i],p[i]--;
    int res=cal();
    reverse(p,p+n);
    res=min(res,cal());
    cout << res << '\n';
}
