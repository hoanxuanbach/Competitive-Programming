#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int inf = 1e8;
const int maxn = 505;

int n,x[maxn],y[maxn];
int p[maxn][maxn],d[maxn][maxn];

int dist(int i,int j){
    return abs(x[i]-x[j])+abs(y[i]-y[j]);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> x[i] >> y[i];
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) d[i][j]=dist(i,j);
    for(int i=1;i<=n;i++){
        iota(p[i]+1,p[i]+n+1,1);
        sort(p[i]+1,p[i]+n+1,[&](int u,int v){
            return d[i][u]<d[i][v];
        });
    }
    int res=INF;
    for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++){
        int D=d[i][j],X=0;
        array<int,3> A={0,0,0};
        auto get = [&](int a,int b,int p,int q){
            return max({d[i][a]+d[i][b],d[j][p]+d[j][q],d[i][b]+d[j][q]+D});
        };
        for(int k=n;k>=0;k--){
            int u=p[i][k];
            if(k<n){
                if(X) res=min(res,get(u,X,A[1],A[0]));
                if(A[0]) res=min(res,get(u,A[0],A[2],A[1]));
                if(A[1]) res=min(res,get(u,A[1],A[2],A[0]));
            }
            for(int t=0;t<3;t++) if(d[j][A[t]]<d[j][u]) swap(A[t],u);
            X=(!X || d[i][u]<d[i][X]?u:X);
        }
    }
    cout << res << '\n';
}
