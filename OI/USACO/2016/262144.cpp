#include<bits/stdc++.h>
using namespace std;
#define maxn (1<<18)+5
int len[maxn],n,a[maxn],ans;
signed main(){
    freopen("262144.in","r",stdin);
    freopen("262144.out","w",stdout);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=60;i++){
        bool ok=false;
        for(int j=1;j<=n;j++){
            if(a[j]==i) len[j]=1;
            else if(len[j] && j+len[j]<=n && len[j+len[j]]) len[j]+=len[j+len[j]];
            else len[j]=0;
            if(len[j]) ok=true;
        }
        if(ok) ans=i;
    }
    cout << ans << '\n';
}
