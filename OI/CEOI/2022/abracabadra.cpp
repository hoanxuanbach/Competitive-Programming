#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
const int maxq = 1e6+5;
#define pii pair<int,int>
#define fi first
#define se second

int n,q,a[maxn],res[maxq];
vector<pii> qq[maxn];
pii pos[maxn];

int cnt[4*maxn];
void build(int l,int r,int id){
    if(l==r){
        cnt[id]=pos[l].se-pos[l].fi+1;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    cnt[id]=cnt[id<<1]+cnt[id<<1|1];
}
void update(int l,int r,int id,int p){
    if(l==r){
        cnt[id]=pos[l].se-pos[l].fi+1;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p);
    else update(mid+1,r,id<<1|1,p);
    cnt[id]=cnt[id<<1]+cnt[id<<1|1];
}
pii query(int l,int r,int id,int k){
    if(l==r) return {l,pos[l].fi+k-1};
    int mid=(l+r)>>1;
    if(cnt[id<<1]<k) return query(mid+1,r,id<<1|1,k-cnt[id<<1]);
    else return query(l,mid,id<<1,k);
}
int rt[maxn];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i],pos[i]={0,-1};

    vector<int> v;
    for(int i=n;i>=1;i--){
        while(!v.empty() && a[i]>a[v.back()]) v.pop_back();
        rt[i]=(v.empty()?n+1:v.back());
        v.push_back(i);
    }

    for(int i=1;i<=q;i++){
        int t,x;cin >> t >> x;
        t=min(t,n);
        if(!t) res[i]=a[x];
        else qq[t].push_back({x,i});
    }
    for(int t=0;t<=1;t++){
        int mx=0,l=0;
        for(int i=1;i<=n/2;i++){
            int id=t*(n/2)+i;
            if(mx<a[id]){
                if(mx) pos[mx]={l,id-1};
                mx=a[id],l=id;
            }
        }
        if(mx) pos[mx]={l,t*(n/2)+n/2};
    }
    build(1,n,1);
    for(int i=1;i<=n;i++){
        for(auto [x,id]:qq[i]) res[id]=a[query(1,n,1,x).se];
        auto [x,id]=query(1,n,1,n/2);
        if(id<pos[x].se){
            int l=id+1,r=pos[x].se;
            pos[x].se=id;
            update(1,n,1,x);
            while(l<=r){
                int nxt=rt[l];
                int nr=min(nxt-1,r);
                pos[a[l]]={l,nr};
                update(1,n,1,a[l]);
                l=nxt;
            }
        }
    }
    for(int i=1;i<=q;i++) cout << res[i] << '\n';
}
