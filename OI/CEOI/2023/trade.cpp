#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 250005;
const int inf = 1e18;
int n,k,s[maxn],c[maxn];

int sz;
vector<int> com;
vector<int> f[maxn];

namespace ST{
    int sum[4*maxn],cnt[4*maxn];
    void update(int l,int r,int id,int x,int val){
        if(l==r){
            cnt[id]+=val;
            sum[id]+=com[l-1]*val;
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) update(l,mid,id<<1,x,val);
        else update(mid+1,r,id<<1|1,x,val);
        sum[id]=sum[id<<1]+sum[id<<1|1];
        cnt[id]=cnt[id<<1]+cnt[id<<1|1];
    }
    pii query(int l,int r,int id,int x){
        if(l==r) return {l,x*com[l-1]};
        int mid=(l+r)>>1;
        if(cnt[id<<1|1]<x){
            pii res=query(l,mid,id<<1,x-cnt[id<<1|1]);
            res.se+=sum[id<<1|1];
            return res;
        }
        else return query(mid+1,r,id<<1|1,x);
    }
}

int L=1,R=0;
void add(int x,int val){
    ST::update(1,sz,1,s[x],val);    
}

pii query(int l,int r){
    while(l<L) add(--L,1);
    while(R<r) add(++R,1);
    while(L<l) add(L++,-1);
    while(r<R) add(R--,-1); 
    pii res=ST::query(1,sz,1,k);
    res.se-=(c[r]-c[l-1]);
    return res;
}

void update(int l,int r,int val){
    f[l].push_back(val);
    f[r+1].push_back(-val);
}

int ans[maxn],pos[maxn];
void dnc(int l,int r,int optl,int optr){
    int x=(l+r)>>1;
    ans[x]=-inf,pos[x]=-1;
    for(int i=max(optl,x+k-1);i<=optr;i++){
        int val=query(x,i).se;
        if(val>ans[x]) ans[x]=val,pos[x]=i;
    }
    if(l<x) dnc(l,x-1,optl,pos[x]);
    if(x<r) dnc(x+1,r,pos[x],optr);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> c[i],c[i]+=c[i-1];
    for(int i=1;i<=n;i++) cin >> s[i],com.push_back(s[i]);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();
    for(int i=1;i<=n;i++) s[i]=lower_bound(com.begin(),com.end(),s[i])-com.begin()+1;
    dnc(1,n-k+1,k,n);
    int Ans=*max_element(ans+1,ans+n-k+2);
    
    int x=0;
    for(int i=1;i<=n-k+1;i++){
        if(ans[i]!=Ans) continue;
        if(x){
            for(int j=pos[x]+1;j<=pos[i];j++){
                pii val=query(x,j);
                if(val.se==Ans) update(x,j,val.fi);
            }
        }
        update(i,pos[i],query(i,pos[i]).fi);
        x=i;
    }
    for(int i=pos[x]+1;i<=n;i++){
        pii val=query(x,i);
        if(val.se==Ans) update(x,i,val.fi);
    }
    cout << Ans << '\n';
    set<pii> ss;
    int T=0;
    for(int i=1;i<=n;i++){
        for(int x:f[i]){
            if(x>0) ss.insert({x,++T});
            else ss.erase(ss.lower_bound({-x,0}));
        }
        if(!ss.empty() && s[i]>=ss.begin()->fi) cout << 1;
        else cout << 0;
    }
    cout << '\n';
}
