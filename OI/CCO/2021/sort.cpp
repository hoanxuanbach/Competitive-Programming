#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 1e5+5;
const int maxq = 1e6+5;
const int B = 100;
const int D = 330;

int n,k,q,a[maxn],p[maxn],cnt[maxn];

vector<pii> f[maxn],g[maxn];
vector<int> pos[maxn];
int res[maxq];

namespace BIT{
    int bit[maxn];
    void update(int x){
        for(int i=x;i<=k;i+=(i&(-i))) bit[i]++;
    }
    int query(int x){
        int sum=0;
        for(int i=x;i>=1;i-=(i&(-i))) sum+=bit[i];
        return sum;
    }
}

int total[maxn];
namespace Block{
    int sum[maxn],lazy[maxn];
    void update(int x,int val){
        for(int i=x;i<=min(n,(x/D+1)*D-1);i++) sum[i]+=val;
        for(int i=(x/D)+1;i<=n/D;i++) lazy[i]+=val;
    }
    int query(int x){
        return sum[x]+lazy[x/D];
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k >> q;
    iota(p+1,p+k+1,1);
    for(int i=1;i<=n;i++){
        cin >> a[i],cnt[a[i]]++;
        pos[a[i]].push_back(i);
    }
    for(int i=n;i>=1;i--) res[0]+=BIT::query(a[i]-1),BIT::update(a[i]);
    for(int i=1;i<=q;i++){
        int t;cin >> t;
        int x=p[t],y=p[t+1];
        swap(p[t],p[t+1]);
        if(cnt[x]<=B) res[i]=cnt[x]*cnt[y],f[y].push_back({x,-i});
        else if(cnt[y]<=B) res[i]=-cnt[x]*cnt[y],f[x].push_back({y,i});
        else res[i]=-cnt[x]*cnt[y],g[x].push_back({y,i});
    }

    for(int x=1;x<=k;x++){
        if(cnt[x]<=B) continue;
        for(int i=1;i<=k;i++) total[i]=0;
        int cur=0;
        for(int i=1;i<=n;i++){
            if(a[i]==x) cur++;
            else total[a[i]]+=cur;
        }
        for(auto [y,id]:g[x]) res[id]+=2*total[y];
    }
    for(int x=1;x<=k;x++){
        for(int i:pos[x]) Block::update(i,1);
        for(auto [y,id]:f[x]){
            int val=0;
            for(int i:pos[y]) val+=Block::query(i);
            if(id>0) res[id]+=2*val;
            else res[-id]-=2*val;
        }
        for(int i:pos[x]) Block::update(i,-1);
    }
    for(int i=1;i<=q;i++){
        res[i]+=res[i-1];
        cout << res[i] << '\n';
    }
}
