#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int maxn = 5e5+5;
int n,a[maxn],l[maxn],r[maxn],nxt[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    
    r[n+1]=2*n;
    for(int i=n;i>=1;i--){
        r[i]=(a[i]==-1?i:r[i+1]);
        nxt[i]=(a[i+1]?i+1:nxt[i+1]);
    }
    int ans=0;l[0]=-n;
    for(int i=1;i<=n;i++){
        ans+=max(0LL,a[i]);
        l[i]=(a[i]==-1?i:l[i-1]);
    }

    priority_queue<int> pq;
    for(int i=1,s=0;i<=n;i++){
        if(a[i]>0){
            auto add = [&](int d){
                if(s<i) ans--,s+=d,pq.push(d);
                else if(d<pq.top()) s-=(pq.top()-d),pq.pop(),pq.push(d);
                else return true;
                return false;
            };
            for(int j=1;j<a[i];j++) if(add(min(i-l[i],r[i]-i)*2)) break;
            add(min(i-l[i],r[i]-nxt[i])*2);
        }
    }
    cout << ans << '\n';
}