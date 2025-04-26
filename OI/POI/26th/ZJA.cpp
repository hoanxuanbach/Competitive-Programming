#include<bits/stdc++.h>
using namespace std;
#define maxn 255
struct matrix{
    int n,m,x[maxn][maxn];
    matrix(int n=-1,int m=-1):n(n),m(m){
        memset(x,0,sizeof(x));
    }
    friend matrix operator*(matrix a,matrix b){
        matrix c(a.n,b.m);
        for(int i=1;i<=a.n;i++){
            for(int j=1;j<=a.m;j++){
                for(int k=1;k<=b.m;k++) c.x[i][k]|=(a.x[i][j]&&b.x[j][k]);
            }
        }
        return c;
    }
};
matrix c[65];
int n,m,sz,a[maxn];
bool check(matrix &s){
    for(int i=1;i<=n;i++){
        bool ok=true;
        for(int j=1;j<=sz;j++){
            if(!s.x[a[j]][i]) ok=false;
        }
        if(ok) return true;
    }
    return false;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> sz;
    for(int i=1;i<=sz;i++) cin >> a[i];
    sort(a+1,a+sz+1);
    c[0].n=c[0].m=n;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        c[0].x[u][v]=1;
    }
    if(a[1]==a[sz]){
        cout << "TAK\n0\n";
        return 0;
    }
    int d=0;
    while(!check(c[d])){
        if(d==40) break;
        c[d+1]=c[d]*c[d];
        d++;
    }
    if(!check(c[d])){
        cout << "NIE\n";
        return 0;
    }
    if(d==0){
        cout << "TAK\n";
        cout << 1 << '\n';
        return 0;
    }
    long long res=1;
    matrix s=c[0];
    for(int i=d-1;i>=0;i--){
        matrix nxt=s*c[i];
        if(!check(nxt)){s=nxt;res+=(1LL<<i);}
    }
    cout << "TAK\n";
    cout << res+1 << '\n';
}

