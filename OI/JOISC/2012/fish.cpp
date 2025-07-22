#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 5e5+5;

int sum[4*maxn],mn[4*maxn],mx[4*maxn],lazy[4*maxn];

void update(int l,int r,int id,int x,int y){
    if(l>x) return;
    if(r<=x){
        if(mn[id]>=y) return;
        if(mx[id]<=y){
            mn[id]=mx[id]=y;
            sum[id]=(r-l+1)*y;
            lazy[id]=y;
            return;
        }
    }
    int mid=(l+r)>>1;
    if(lazy[id]){
        lazy[id<<1]=lazy[id<<1|1]=lazy[id];
        mx[id<<1]=mx[id<<1|1]=mn[id<<1]=mn[id<<1|1]=lazy[id];
        sum[id<<1]=(mid-l+1)*lazy[id],sum[id<<1|1]=(r-mid)*lazy[id];
        lazy[id]=0;
    }
    update(l,mid,id<<1,x,y);update(mid+1,r,id<<1|1,x,y);
    mn[id]=min(mn[id<<1],mn[id<<1|1]);
    mx[id]=max(mx[id<<1],mx[id<<1|1]);
    sum[id]=sum[id<<1]+sum[id<<1|1];
}


void solve(){   
    int n;cin >> n;
    vector<int> f(256,-1);
    f['R']=0,f['G']=1,f['B']=2;

    vector<pii> p(n);
    for(int i=0;i<n;i++){
        int x;char c;cin >> x >> c;
        p[i]={x,f[c]};
    }
    sort(p.begin(),p.end());
    
    int pos=0;
    array<int,3> cnt={0,0,0};

    vector<vector<pii>> add(n+1);
    for(int i=0;i<n;i++){
        while(pos<n && p[pos].fi<2*p[i].fi) cnt[p[pos++].se]++;
        add[cnt[0]].push_back({cnt[1],cnt[2]});
        //cout << cnt[0] << ' ' << cnt[1] << ' ' << cnt[2] << '\n';
        cnt[p[i].se]--;
    }

    int res=0;
    for(int i=n;i>=0;i--){
        for(auto [x,y]:add[i]) update(0,n,1,x,y+1);
        res+=sum[1];
        //cout << '*' << i << ' ' << sum[1] << '\n';
    }
    cout << res-1 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}