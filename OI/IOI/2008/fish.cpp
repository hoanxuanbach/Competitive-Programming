#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 5e5+5;

int n,k,mod,mx[maxn];
vector<int> p[maxn];
int c[maxn],tree[4*maxn];

void build(int l,int r,int id){
    if(l==r){
        tree[id]=(c[l]+1)%mod;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]*tree[id<<1|1]%mod;
}
void update(int l,int r,int id,int x){
    if(l==r){
        tree[id]=(c[l]+1)%mod;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) update(l,mid,id<<1,x);
    else update(mid+1,r,id<<1|1,x);
    tree[id]=tree[id<<1]*tree[id<<1|1]%mod;
}
int query(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return 1;
    if(tl<=l && r<=tr) return tree[id];
    int mid=(l+r)>>1;
    return query(l,mid,id<<1,tl,tr)*query(mid+1,r,id<<1|1,tl,tr)%mod;
}

signed main(){
    //freopen("FISH.INP","r",stdin);
    //freopen("FISH.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k >> mod;
    vector<pii> d;
    for(int i=1;i<=n;i++){
        int l,x;cin >> l >> x;
        mx[x]=max(mx[x],l);
        d.push_back({l,x});
    }
    vector<int> ord(k);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return mx[x]>mx[y];
    });
    for(int i=0;i<k;i++) mx[ord[i]]=i+1;
    for(auto &[l,x]:d) x=mx[x],p[x].push_back(l);
    for(int i=1;i<=k;i++){
        c[i]=(int)p[i].size();
        sort(p[i].begin(),p[i].end());
    }
    sort(d.begin(),d.end());
    build(1,k,1);

    int pos=1,total=0;
    for(int i=1;i<=k;i++){
        while(!d.empty() && d.back().fi>p[i].back()/2){
            int x=d.back().se;d.pop_back();
            c[x]--;update(1,k,1,x);
        }
        int l=1,r=i-1,pos=i;
        while(l<=r){
            int mid=(l+r)>>1;
            if(p[mid].back()/2>=p[i][c[i]]) l=mid+1;
            else pos=mid,r=mid-1;
        }
        int rt=(i==k?1:query(1,k,1,i+1,k));
        int lt=(pos<i?query(1,k,1,pos,i-1)-1:0);
        lt=(lt+c[i]+1)%mod;
        total=(total+lt*rt)%mod;
    }
    cout << total << '\n';
}
