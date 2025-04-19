#include<bits/stdc++.h>
using namespace std;
#define maxn 200005
#define int long long
const int inf=6e18;
int dp[maxn],x[maxn],b[maxn],k,m,d,a,n;
int bit[2][maxn],len;
int query(int id,int p){
    int Max=-inf;
    for(int i=p;i>=1;i-=(i&(-i))) Max=max(Max,bit[id][i]);
    return Max;
}
void update(int id,int p,int val){
    for(int i=p;i<=len;i+=(i&(-i))) bit[id][i]=max(bit[id][i],val);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> k >> m >> d >> a >> n;
    vector<int> p;p.push_back(k%d);p.push_back(m%d);
    for(int i=1;i<=n;i++){
        cin >> x[i] >> b[i];
        p.push_back({x[i]%d});
    }
    sort(p.begin(),p.end());
    p.erase(unique(p.begin(),p.end()),p.end());
    x[0]=k;x[n+1]=m;len=(int)p.size()+1;
    for(int i=0;i<=len;i++) bit[1][i]=bit[0][i]=-inf;
    int km=lower_bound(p.begin(),p.end(),k%d)-p.begin()+1;
    update(0,km,0+(k/d)*a);update(1,len-km,0+(k/d)*a);
    for(int i=1;i<=n+1;i++){
        int q=lower_bound(p.begin(),p.end(),x[i]%d)-p.begin()+1;
        int t1=query(0,q-1),t2=query(1,len-q);
        dp[i]=max(t1-a*(x[i]/d+1),t2-a*(x[i]/d))+b[i];
        update(0,q,dp[i]+(x[i]/d)*a);update(1,len-q,dp[i]+(x[i]/d)*a);
    }
    cout << dp[n+1] << '\n';
}
