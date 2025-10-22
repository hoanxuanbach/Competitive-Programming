#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 1e9+7;
const int maxn = 1e5+5;

const int S = 1e5;
const int L = 50; 

int T,root[maxn];
int cnt[maxn*L],lc[maxn*L],rc[maxn*L];
int sum[maxn*L];

int build(int l,int r){
    int id=++T;
    if(l==r) return id;
    int mid=(l+r)>>1;
    lc[id]=build(l,mid);
    rc[id]=build(mid+1,r);
    return id;
}
int update(int l,int r,int id,int x,int val){
    if(l==r){
        T++;
        cnt[T]=1-cnt[id];
        sum[T]=val-sum[id];
        return T;
    }
    int mid=(l+r)>>1;

    int nid=++T;
    rc[nid]=rc[id];lc[nid]=lc[id];
    if(x<=mid) lc[nid]=update(l,mid,lc[id],x,val);
    else rc[nid]=update(mid+1,r,rc[id],x,val);
    sum[nid]=sum[lc[nid]]+sum[rc[nid]];
    cnt[nid]=cnt[lc[nid]]+cnt[rc[nid]];
    return nid;
}

int query(int l,int r,int id,int k){
    if(l==r) return sum[id];
    int mid=(l+r)>>1;
    if(cnt[lc[id]]<k) return sum[lc[id]]+query(mid+1,r,rc[id],k-cnt[lc[id]]);
    else return query(l,mid,lc[id],k);
}

void solve(){
    int n,m;cin >> n >> m;
    vector<vector<pair<int,int>>> f(S+2);
    vector<pair<int,int>> P;
    for(int i=1;i<=n;i++){
        int l,r,x;cin >> l >> r >> x;
        f[l].push_back({x,i});
        f[r+1].push_back({x,i});
        P.push_back({x,i});
    }
    sort(P.begin(),P.end());

    root[0]=build(1,n);
    //cout << '*' << root[0] << '\n';
    for(int i=1;i<=S;i++){
        root[i]=root[i-1];
        for(auto [x,id]:f[i]){
            int p=lower_bound(P.begin(),P.end(),make_pair(x,id))-P.begin()+1;
            //cout << "add " << x << ' ' << id << ' ' << p << '\n';
            root[i]=update(1,n,root[i],p,x);
        }
        //cout << root[1] << ' ' << sum[root[1]] << '\n';
    }

    int res=1;
    for(int i=1;i<=m;i++){
        int t,D,A,F;cin >> t >> D >> A >> F;
        int k=1+(res*D+A)%F;
        cout << (res=query(1,n,root[t],k)) << '\n'; 
    }
}   

signed main(){
    ios_base::sync_with_stdio(false);
    int test=1;//cin >> test;
    while(test--) solve();
}