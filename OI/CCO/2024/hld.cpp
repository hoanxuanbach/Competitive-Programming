#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int maxn = 5e5+5;
const int mod = 1e6+3;
#define pii pair<int,int>
#define fi first
#define se second

struct Segtree{;
    int tree[4*maxn],lazy[4*maxn],cnt[4*maxn];
    void update_val(int l,int r,int id,int x,int val){
        if(l==r){
            cnt[id]=val;
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) update_val(l,mid,id<<1,x,val);
        else update_val(mid+1,r,id<<1|1,x,val);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
        cnt[id]=((tree[id]==tree[id<<1])*cnt[id<<1]+(tree[id]==tree[id<<1|1])*cnt[id<<1|1])%mod;
        tree[id]+=lazy[id];
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            tree[id]+=val;
            lazy[id]+=val;
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
        cnt[id]=((tree[id]==tree[id<<1])*cnt[id<<1]+(tree[id]==tree[id<<1|1])*cnt[id<<1|1])%mod;
        tree[id]+=lazy[id];
    }
    pii query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return {inf,0};
        if(tl<=l && r<=tr) return {tree[id],cnt[id]};
        int mid=(l+r)>>1;
        pii a=query(l,mid,id<<1,tl,tr),b=query(mid+1,r,id<<1|1,tl,tr);
        int x=min(a.fi,b.fi),y=((x==a.fi)*a.se+(x==b.fi)*b.se)%mod;
        return {x+lazy[id],y};
    }
}T[2];

int n,a[maxn],dp[maxn];
int pre[maxn],lst[maxn],L,lt[2];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    dp[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=1;j++) T[j].update_val(1,n,1,i,dp[i-1]);

        int x=pre[a[i]],t=(i&1);
        if((x&1)!=t) L=max(L,x+1);
        lt[t]=max(lt[t],x+1);

        T[t^1].update(1,n,1,x+1,i,1);
        if(x) T[t^1].update(1,n,1,lst[x]+1,x,-1);
        //cout <<  '*' << i << '\n';
        for(int j=0;j<=1;j++){
            //cout << L << ' ' << lt[j] << '\n';
            pii cc=T[j].query(1,n,1,max(L,lt[j]),i);
            dp[i]=(dp[i]+(!cc.fi)*cc.se)%mod;
        }
        //cout << dp[i] << '\n';
        pre[a[i]]=i;lst[i]=x;
    }
    cout << dp[n] << '\n';
}
