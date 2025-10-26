#include<bits/stdc++.h>
using namespace std;
#define maxn 5005
#define int long long
#define ld long double
ld p[maxn][maxn];
int a[maxn],n;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    sort(a+1,a+n+1,greater<int>());
    for(int i=1;i<=n;i++){
        if((n-i)&1){
            for(int j=1;j<=i;j++) p[i][j]=(p[i-1][j-1]*(j-1)+p[i-1][j]*(i-j))/i;
        }
        else{
            for(int j=2;j<=i;j++) p[i][j]=p[i-1][j-1];
            p[i][1]=1.0;
        }
    }
    ld ans1=0,sum=0;
    //for(int i=1;i<=n;i++) cout << p[n][i] << ' ';
    for(int i=1;i<=n;i++){ans1+=p[n][i]*a[i];sum+=a[i];}
    cout << setprecision(12) << fixed << ans1 << ' ' << sum-ans1 << '\n';
}
