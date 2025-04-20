#include<bits/stdc++.h>
using namespace std;
const int maxn = 255;
const int inf = 1e9;
int n,m,k,q,c[maxn][maxn],lt[maxn],rt[maxn],a[maxn];

int cal(){
    for(int i=0;i<=n+1;i++) lt[i]=rt[i]=inf;
    for(int l=1;l<=n;l++){
        for(int i=1;i<=m;i++) a[i]=0;
        for(int r=l;r<=n;r++){
            for(int i=1;i<=m;i++) a[i]+=c[r][i];
            int j=0,sum=0;
            for(int i=1;i<=m;i++){
                sum+=a[i];
                while(sum-a[j]>=k) sum-=a[j++];
                if(sum==k){
                    int total=2*(i-j+1)+2*(r-l+1);
                    lt[r]=min(lt[r],total);
                    rt[l]=min(rt[l],total);
                    //cout << l << ' ' << r << ' ' << i << ' ' << j << '\n';
                }
            }
        }
    }
    for(int i=1;i<=n;i++) lt[i]=min(lt[i],lt[i-1]);
    for(int i=n;i>=1;i--) rt[i]=min(rt[i],rt[i+1]);
    int res=inf;
    for(int i=0;i<=n;i++) res=min(res,lt[i]+rt[i+1]);
    //cout << res << '\n';
    return res;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> q >> k;
    for(int i=1;i<=q;i++){int x,y;cin >> x >> y;c[x][y]++;}
    int res=cal();
    for(int i=1;i<=max(n,m);i++) for(int j=1;j<i;j++) swap(c[i][j],c[j][i]);
    swap(n,m);
    res=min(res,cal());
    if(res==inf) cout << "NO\n";
    else cout << res << '\n';
}
