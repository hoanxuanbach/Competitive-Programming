#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
const int inf = 1e9;
int n,m,a[maxn],mn[maxn],dp[maxn];

int tree[4*maxn],lazy[4*maxn];
void update(int l,int r,int id,int tl,int tr,int val){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        tree[id]+=val;
        lazy[id]+=val;
        //cout << id << ' ' << tree[id] << ' ' << val << '\n';
        return;
    }
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
    tree[id]=min(tree[id<<1],tree[id<<1|1])+lazy[id];
    //cout << id << ' ' << tree[id] << ' ' << val << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    iota(a+1,a+n+1,1);
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        if(u>v) swap(u,v);
        a[v]=min(a[v],u);
    }
    mn[n+1]=n+1;
    for(int i=n;i>=1;i--) mn[i]=min(mn[i+1],a[i]);
    for(int i=1;i<=4*n;i++) tree[i]=inf;

    int p=1;
    for(int i=2;i<=n;i++){
        while(p<min(i,mn[i+1])) update(1,n,1,p,p,dp[p]-inf),p++;
        if(a[i]>1) update(1,n,1,1,a[i]-1,1);
        dp[i]=min(inf,tree[1]);
    }
    cout << dp[n] << '\n';
}
