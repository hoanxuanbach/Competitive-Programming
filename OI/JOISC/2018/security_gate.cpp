#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int maxn = 305;

int n,ans;
char s[maxn];
int f[maxn][maxn][maxn],g[maxn][2*maxn][3];
int F[maxn][maxn];

bool ok(int i,int x){
    if(s[i]=='(' && x==-1) return false;
    if(s[i]==')' && x==1) return false;
    return true;
};

void dp1(){
    F[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++) for(int x:{-1,1}){
            if(!ok(i,x)) continue;
            int nj=j+x;
            if(nj>=0) F[i][nj]=(F[i][nj]+F[i-1][j])%mod;
        }
    }
    ans=(ans+F[n][0])%mod;
    //cout << ans << '\n';
}
void dp2(){
    memset(F,0,sizeof(F));
    memset(f,0,sizeof(f));

    f[0][0][0]=1;
    for(int i=1;i<=n;i++) for(int j=0;j<i;j++) for(int k=0;k<i;k++){
        for(int x:{-1,1}){
            if(!ok(i,x)) continue;
            int nj=j+x,nk=max(k,nj);
            if(nj>=0) f[i][nj][nk]=(f[i][nj][nk]+f[i-1][j][k])%mod;
            if(nj==-1) F[i][nk]=(F[i][nk]+f[i-1][j][k])%mod;
        }
    }
    for(int t=1;t<=n;t++){
        memset(g,0,sizeof(g));
        g[n+1][0][0]=1;
        for(int i=n;i>=1;i--) for(int j=0;j<=(n-i);j++){
            for(int x:{-1,1}){
                if(!ok(i,-x)) continue;
                int nj=j+x;
                int *a=g[i][nj],*b=g[i+1][j];
                if(nj>=0) a[0]=(a[0]+b[0])%mod;
                if(nj==t) a[1]=(a[1]+b[0])%mod;
                else if(nj<=2*t) a[1]=(a[1]+b[1])%mod;
            }
        }
        for(int a=0;a<t;a++){
            int b=(a-t)*2;
            for(int i=1;i<=n;i++) ans=(ans+F[i][a]*g[i+1][-1-b][a+b/2<0])%mod;
        }
    }
    //cout << ans << '\n';
}
void dp3(int d){
    for(int t=0;t<=n;t++){
        memset(g,0,sizeof(g));
        g[n+1][n][0]=1;
        if(t+d==0) g[n+1][n][1]=1;
        for(int i=n;i>=1;i--) for(int j=-(n-i);j<=(n-i);j++){
            for(int x:{-1,1}){
                if(!ok(i,-x)) continue;
                int nj=j+x;
                int *a=g[i][nj+n],*b=g[i+1][j+n];
                if(nj>=0) a[0]=(a[0]+b[0])%mod;
                if(nj==t+d) a[1]=(a[1]+b[0])%mod;
                else if(nj>=0) a[1]=(a[1]+b[1])%mod;
                if(nj==-1) a[2]=(a[2]+b[1])%mod;
                if(nj<=2*t) a[2]=(a[2]+b[2])%mod;
            }
        }
        for(int a=0;a<=n;a++){
            int b=2*(a-t);
            if(b>=-n && b<n) for(int i=1;i<=n;i++) ans=(ans+F[i][a]*g[i+1][-1-b+n][2])%mod;
        }
    }
    //cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> s[i];
    dp1();dp2();dp3(0);
    reverse(s+1,s+n+1);
    for(int i=1;i<=n;i++) if(s[i]!='x') s[i]='('+')'-s[i];
    dp2();dp3(1);
    cout << ans << '\n';
}
