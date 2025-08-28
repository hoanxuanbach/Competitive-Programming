//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx2,fma,sse4.2")
#include<bits/stdc++.h>
using namespace std;
#define maxn 3500005
#define maxm 155
int pw(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a;
        a=a*a;n>>=1;
    }
    return res;
}
int t[10],p[10],m,n,ans,sz,sz2,a[maxn],b[maxn],pp[maxm][10];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> t[i] >> p[i];
    for(int i=1;i<=m;i++){
        for(int j=1;j<=6;j++) pp[i][j]=pw(i,p[j]);
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=(n<2?1:m);j++){
            for(int k=1;k<=(n<3?1:m);k++){
                int x=t[1]*pp[i][1]+t[2]*pp[j][2]+t[3]*pp[k][3];
                a[++sz]=x;
            }
        }
    }
    sort(a+1,a+sz+1);
    for(int i=1;i<=(n<4?1:m);i++){
        for(int j=1;j<=(n<5?1:m);j++){
            for(int k=1;k<=(n<6?1:m);k++){
                int x=t[4]*pp[i][4]+t[5]*pp[j][5]+t[6]*pp[k][6];
                b[++sz2]=x;
            }
        }
    }
    sort(b+1,b+sz2+1);
    int pre=-1,preans=-1;
    for(int i=1;i<=sz2;i++){
        if(b[i]!=pre){pre=b[i];preans=(upper_bound(a+1,a+sz+1,-b[i])-a)-(lower_bound(a+1,a+sz+1,-b[i])-a);}
        ans+=preans;
    }
    cout << ans << '\n';
}