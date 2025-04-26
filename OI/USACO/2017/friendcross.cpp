#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int>
#define se second
#define fi first
int n,k,p[maxn],bit[maxn];
pii a[maxn];
void update(int x,int val){
    for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
}
int query(int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
    return res;
}
int solve(int l,int r){
    if(l==r) return 0;
    int mid=(l+r)>>1,res=solve(l,mid)+solve(mid+1,r);
    vector<piii> x;
    for(int i=l;i<=mid;i++) x.push_back({a[i],1});
    for(int i=mid+1;i<=r;i++) x.push_back({a[i],0});
    sort(x.begin(),x.end());
    for(auto d:x){
        if(d.se==0) update(d.fi.se,1);
        else res+=query(max(0LL,d.fi.se-k-1))+query(n)-query(min(n+1,d.fi.se+k+1)-1);
    }
    for(auto d:x){
        if(d.se==0) update(d.fi.se,-1);
    }
    return res;
}
signed main(){
    freopen("friendcross.in","r",stdin);
    freopen("friendcross.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    for(int i=1;i<=n;i++){cin >> a[i].se;p[a[i].se]=i;}
    for(int i=1;i<=n;i++){int x;cin >> x;a[p[x]].fi=i;}
    cout << solve(1,n) << '\n';
}
