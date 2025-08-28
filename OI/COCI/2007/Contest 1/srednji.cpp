#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define int long long
int n,a[maxn],p[maxn],num[2][2*maxn];
int solve(int k){
    for(int i=1;i<=n;i++){
        if(a[i]>k) p[i]=1;
        else if(a[i]<k) p[i]=-1;
    }
    p[0]=n+1;num[0][p[0]]=1;
    int ans=0;
    for(int i=1;i<=n;i++){
        p[i]+=p[i-1];
        ans+=num[(i&1)^1][p[i]];
        num[(i&1)][p[i]]++;
    }
    return ans;
}
signed main(){
    //freopen("SRE.INP","r",stdin);
    //freopen("SRE.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int k;cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> a[i];
    cout << solve(k) << '\n';
}
