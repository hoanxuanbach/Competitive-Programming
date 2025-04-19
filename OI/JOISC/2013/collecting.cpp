#include<bits/stdc++.h>
using namespace std;
#define maxn 25
#define int long long
int n,q,c[2][maxn][(1<<20)+5],num[2][maxn],sum,ans;
void update(int p,int x){
    c[p][0][x]^=1;ans=0;
    for(int i=1;i<=n;i++){
        x>>=1;int pre=c[p][i][x];
        if(c[p][i-1][x<<1|1]==c[p][i-1][x<<1]) c[p][i][x]=c[p][i-1][x<<1];
        else c[p][i][x]=-1;
        if(pre!=-1 && c[p][i][x]==-1) num[p][i]--;
        if(pre==-1 && c[p][i][x]!=-1) num[p][i]++;
        ans+=num[p][i]*num[p^1][i];
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> q;
    for(int i=0;i<=n;i++) sum+=(1LL<<(2*i));
    for(int i=1;i<=n;i++) num[0][i]=num[1][i]=(1LL<<(n-i));
    for(int i=1;i<=q;i++){
        int p,x;cin >> p >> x;x--;
        update(p,x);
        cout << sum-4*ans << '\n';
    }
}
