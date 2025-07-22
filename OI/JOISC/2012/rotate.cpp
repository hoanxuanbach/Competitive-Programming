
#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 1e3+5;
const int maxT = 11e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

int dx[]={1,0,-1,0},
    dy[]={0,1,0,-1};

char X[maxT];
int p[maxT][4],c[maxT];
int a[4][maxT],b[4][maxT];


void solve(){   
    int n,q;cin >> n >> q;
    auto get_id = [&](int i,int j){
        return i*(n+2)+j+1;
    };
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin >> X[get_id(i,j)];
    for(int i=0;i<=n+1;i++) for(int j=0;j<=n+1;j++) for(int k=0;k<4;k++){
        int x=i+dx[k],y=j+dy[k];
        if(x<0 || y<0 || x>n+1 || y>n+1) continue;
        p[get_id(i,j)][k]=get_id(x,y);
    }
    auto nxt = [&](int x,int i){
        int y=p[x][(i-c[x]+4)%4];
        for(int j=0;j<4;j++) if(p[y][j]==x){
            c[y]=(i-j+6)%4;break;
        }
        return y;
    };

    while(q--){
        int x,y,L;cin >> x >> y >> L;
        int cur=1;
        for(int i=0;i<x;i++) cur=nxt(cur,0);
        for(int i=0;i<y;i++) cur=nxt(cur,1);
        for(int i=0;i<4;i++) for(int j=0;j<L;j++){
            a[i][j]=cur,b[i][j]=nxt(cur,(i+3)%4);
            if(j<L-1) cur=nxt(cur,i);
        }
        for(int i=0;i<4;i++) for(int j=0;j<L;j++){
            p[a[i][j]][(i-c[a[i][j]]+3)%4]=b[(i+1)%4][j];
            p[b[i][j]][(i-c[b[i][j]]+5)%4]=a[(i+3)%4][j];
        }
    }
    int cur=nxt(1,1);
    for(int i=1;i<=n;i++){
        cur=nxt(cur,0);
        int x=cur;
        for(int j=1;j<=n;j++){
            cout << X[x];
            x=nxt(x,1);
        }
        cout << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}