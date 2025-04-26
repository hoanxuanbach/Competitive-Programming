#include<bits/stdc++.h>
using namespace std;
#define maxn 200005
#define maxl 25
int cnt[maxn][maxl],num[maxl],x[maxn],n,m;
int f(){
    for(int i=0;i<=16;i++){
        if(num[i]!=(1<<(i+1))) return i+1;
    }
    return 20;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++){char c;cin >> c;x[i]=c-'0';}
    for(int i=1;i<=n;i++){
        int d=0;
        for(int j=0;j<=min(n-i,16);j++){
            d=d<<1|x[i+j];
            if(cnt[d][j]==0) num[j]++;
            cnt[d][j]++;
        }
    }
    cout << f() << '\n';
    for(int t=1;t<=m;t++){
        int p;cin >> p;
        for(int i=p;i>=max(1,p-16);i--){
            int d=0;
            for(int j=0;j<=min(n-i,16);j++){
                d=d<<1|x[i+j];
                if(i+j>=p){
                    cnt[d][j]--;
                    if(cnt[d][j]==0) num[j]--;
                }
            }
        }
        x[p]^=1;
        for(int i=p;i>=max(1,p-16);i--){
            int d=0;
            for(int j=0;j<=min(n-i,16);j++){
                d=d<<1|x[i+j];
                if(i+j>=p){
                    if(cnt[d][j]==0) num[j]++;
                    cnt[d][j]++;
                }
            }
        }
        cout << f() << '\n';
    }
}
