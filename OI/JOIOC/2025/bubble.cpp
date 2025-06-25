#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int maxn = 5e5+5;


int n,a[maxn],res[maxn],pre[maxn];

vector<pii> qq[maxn],cur;
vector<array<int,3>> all;

int cnt[4*maxn],sum[4*maxn];
void update(int l,int r,int id,int x,int val){
    if(l==r){
        cnt[id]=1;
        sum[id]=val;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) update(l,mid,id<<1,x,val);
    else update(mid+1,r,id<<1|1,x,val);
    cnt[id]=cnt[id<<1]+cnt[id<<1|1];
    sum[id]=sum[id<<1]+sum[id<<1|1];
}
int get(int l,int r,int id,int k){
    if(l==r) return l;
    int mid=(l+r)>>1;
    if(cnt[id<<1|1]<k) return get(l,mid,id<<1,k-cnt[id<<1|1]);
    else return get(mid+1,r,id<<1|1,k);
}
pii query(int l,int r,int id,int x){
    if(l==r) return {cnt[id],sum[id]};
    int mid=(l+r)>>1;
    if(x<=mid) return query(l,mid,id<<1,x);
    else{
        pii val=query(mid+1,r,id<<1|1,x);
        return {val.first+cnt[id<<1],val.second+sum[id<<1]};
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        pre[i]=pre[i-1]+a[i];
        cur.push_back({a[i],i});
    }
    sort(cur.begin(),cur.end());
    
    int k=0,cq=0;
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int t=0;cin >> t;
        if(t==1) k=min(k+1,n);
        else{
            cq++;
            int l,r;cin >> l >> r;
            if(!k) res[cq]=pre[r]-pre[l-1];
            else{
                qq[min(r+k,n)].push_back({k,cq});
                qq[min(l-1+k,n)].push_back({k,-cq});
                all.push_back({r,k,cq});
                all.push_back({l-1,k,-cq});
            }
        }   
    }

    for(int i=1;i<=n;i++){
        int pos=lower_bound(cur.begin(),cur.end(),make_pair(a[i],i))-cur.begin();
        update(0,n-1,1,pos,a[i]);
        for(auto [k,id]:qq[i]){
            int x=get(0,n-1,1,k);
            pii p=query(0,n-1,1,x);
            x=cur[x].first;
            int total=(i-p.first)*x+p.second-x*k;
            if(id<0) total=-total,id=-id;
            res[id]+=total;
            //cout << "res " << id << ' ' << i << ' ' << x << ' ' << p.first << ' ' << p.second << ' ' << total << '\n';
        }
    }

    vector<int> ss(n);
    for(int i=0;i<n;i++){
        ss[i]=cur[i].first;
        if(i) ss[i]+=ss[i-1];
    }
    for(auto [r,k,id]:all){
        int d=n-r;
        if(d>=k) continue;
        if(d==0){
            int y=cur[n-k].first,sy=ss[n-k]+(k-1)*y;
            int total=pre[n]-sy+y*k;
            if(id<0) total=-total,id=-id;
            res[id]+=total;
        }
        else{
            int x=cur[n-d].first,y=cur[n-k].first;
            int sx=ss[n-d]+(d-1)*x,sy=ss[n-k]+(k-1)*y;
            int total=y*k+sx-sy-x*d;
            if(id<0) total=-total,id=-id;
            //cout << "add " << id << ' ' << total << '\n';
            res[id]+=total;
        }
    }
    for(int i=1;i<=cq;i++) cout << res[i] << '\n';
}