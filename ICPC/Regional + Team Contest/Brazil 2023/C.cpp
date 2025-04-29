#include<bits/stdc++.h>
using namespace std;
#define maxn 10005
#define maxa 1000
#define pii pair<int,int>
int n,c[maxa+5][maxa+5],r[maxa+5][maxa+5],x[maxn],y[maxn],m[maxa+5][maxa+5],p=0,num[maxa+5][maxa+5],cnt[(maxa+5)*(maxa+5)];
int dx[]={1,0,-1,0},
    dy[]={0,1,0,-1};
void dfs(int it,int jt){
    queue<pii> q;q.push({it,jt});num[it][jt]=p;cnt[p]++;
    while(!q.empty()){
        int i=q.front().first,j=q.front().second;q.pop();
        for(int t=0;t<4;t++){
            if(m[i][j]&(1<<t)){
                int xt=i+dx[t],yt=j+dy[t];
                assert(xt>=0);assert(yt>=0);
                assert(xt<=maxa);assert(yt<=maxa);
                if(num[xt][yt]==0){
                    num[xt][yt]=p;cnt[p]++;
                    q.push({xt,yt});
                }
            }
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int i=0;i<=maxa;i++){
        for(int j=0;j<=maxa;j++){
            if(i!=maxa) m[i][j]^=1;
            if(j!=maxa) m[i][j]^=2;
            if(i!=0) m[i][j]^=4;
            if(j!=0) m[i][j]^=8;
        }
    }
    cin >> n;
    for(int i=0;i<=n;i++) cin >> x[i] >> y[i];
    for(int i=0;i<n;i++){
        if(x[i]==x[i+1]){
            c[x[i]][min(y[i],y[i+1])]++;
            c[x[i]][max(y[i],y[i+1])]--;
        }
        else{
            r[min(x[i],x[i+1])][y[i]]++;
            r[max(x[i],x[i+1])][y[i]]--;
        }
    }
    for(int i=0;i<=maxa;i++){
        for(int j=1;j<=maxa;j++){
            c[i][j]+=c[i][j-1];
            if(c[i][j]>=1){
                m[i][j]^=4;
                m[i-1][j]^=1;
            }
        }
    }
    for(int i=1;i<=maxa;i++){
        for(int j=0;j<=maxa;j++){
            r[i][j]+=r[i-1][j];
            if(r[i][j]>=1){
                m[i][j]^=8;
                m[i][j-1]^=2;
            }
        }
    }
    int ans=0;
    for(int i=0;i<=maxa;i++){
        for(int j=0;j<=maxa;j++){
            if(!num[i][j]){
                p++;dfs(i,j);
                if(p>=2) ans=max(ans,cnt[p]);
            }
        }
    }
    cout << ans << '\n';
}
