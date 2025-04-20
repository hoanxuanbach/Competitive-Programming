#include<bits/stdc++.h>
using namespace std;
#define maxn 300005
#define pii pair<int,int>
int n,d,a[maxn],Min[maxn],rr[maxn],dp[maxn];
vector<int> p,pos[maxn];
namespace ST{
    int tree[4*maxn];
    void build(int l,int r,int id){
        if(l==r){
            tree[id]=-1;
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    }
    int query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return -1;
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return max(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    }
    void update(int l,int r,int id,int p,int val){
        if(l==r){
            tree[id]=val;
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,val);
        else update(mid+1,r,id<<1|1,p,val);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> d;
    //Compress numbers
    for(int i=1;i<=n;i++){
        cin >> a[i];
        p.push_back(a[i]);
    }
    sort(p.begin(),p.end());
    p.erase(unique(p.begin(),p.end()),p.end());
    for(int i=1;i<=n;i++) a[i]=lower_bound(p.begin(),p.end(),a[i])-p.begin()+1;
    //calculate Min[i] is the minimum number from i->i+d-1
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    for(int i=n;i>=n-d+1;i--){pq.push({a[i],i});rr[i]=n;}
    for(int i=n-d+1;i>=1;i--){
        while(!pq.empty() && pq.top().second>=i+d) pq.pop();
        Min[i]=pq.top().first;
        pq.push({a[i-1],i-1});
    }
    // calculate r[i] is the farthest that i can go to
    vector<int> v;v.push_back(n-d+1);
    for(int i=n-d;i>=1;i--){
        while(!v.empty() && Min[i]>=Min[v.back()]) v.pop_back();
        v.push_back(i);
        rr[i]=n;
        int lt=0,rt=(int)v.size()-1;
        while(rt>=lt){
            int mid=(lt+rt)>>1;
            if(Min[v[mid]]>a[i]){rr[i]=v[mid]+d-1;lt=mid+1;}
            else rt=mid-1;
        }
    }
    //calculate dp with sort a[i]
    for(int i=1;i<=n;i++) pos[a[i]].push_back(i);
    int ans=0;
    ST::build(1,n,1);
    ST::update(1,n,1,n,0);
    for(int i=n;i>=1;i--){
        for(int x:pos[i]){
            dp[x]=ST::query(1,n,1,x,rr[x])+1;
            ans=max(ans,dp[x]);
        }
        for(int x:pos[i]) ST::update(1,n,1,x,dp[x]);
    }
    cout << ans << '\n';
}

