#include<bits/stdc++.h>
using namespace std;
#define maxn 1005
#define maxc 1000005
int x[maxn][maxn],n,k,cnt,num[maxn][maxn];
bool ok[maxc];
int rx[maxc],ry[maxc],ru[maxc],rv[maxc];
int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};
signed main(){
    freopen("art.in","r",stdin);
    freopen("art.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n*n;i++) rx[i]=ry[i]=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> x[i][j];
            if(x[i][j]==0) continue;
            rx[x[i][j]]=min(rx[x[i][j]],i);
            ry[x[i][j]]=min(ry[x[i][j]],j);
            ru[x[i][j]]=max(ru[x[i][j]],i);
            rv[x[i][j]]=max(rv[x[i][j]],j);
            if(k==0){k=x[i][j];cnt++;}
            else if(x[i][j]!=k) cnt++;
        }
    }
    if(cnt==1){
        if(n==1) cout << 1 << '\n';
        else cout << n*n-1 << '\n';
        return 0;
    }
    int res=n*n;
    for(int i=1;i<=n*n;i++){
        if(rx[i]==n && ry[i]==n) continue;
        num[rx[i]][ry[i]]++;num[rx[i]][rv[i]+1]--;
        num[ru[i]+1][ry[i]]--;num[ru[i]+1][rv[i]+1]++;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            num[i][j]+=num[i-1][j]+num[i][j-1]-num[i-1][j-1];
            if(num[i][j]>=2 && x[i][j]!=0) ok[x[i][j]]=true;
        }
    }
    for(int i=1;i<=n*n;i++){
        if(ok[i]) res--;
    }
    cout << res << '\n';
}
