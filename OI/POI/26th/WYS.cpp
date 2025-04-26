#include<bits/stdc++.h>
using namespace std;
#define maxn 300005
#define int long long
struct node{
    int Min,Max,Max2,lazy=0;
    node(int Min=-1,int Max=-1,int Max2=-1):Min(Min),Max(Max),Max2(Max2){}
    friend node operator+(node a,node b){
        a.Max=max(a.Max,b.Max);
        a.Min=min(a.Min,b.Min);
        a.Max2=max(a.Max2,b.Max2);
        a.lazy=0;
        return a;
    }
};
int a[maxn],n,q;
struct segtree{
    node tree[4*maxn];
    void getnew(int id,int val){
        tree[id].Max+=val;
        tree[id].Min+=val;
        tree[id].Max2+=val;
        tree[id].lazy+=val;
    }
    void pushdown(int id){
        if(tree[id].lazy==0) return;
        getnew(id<<1,tree[id].lazy);
        getnew(id<<1|1,tree[id].lazy);
        tree[id].lazy=0;
    }
    void build(int l,int r,int id){
        if(l==r){
            tree[id]=node(a[l],a[l],a[l]+n-l);
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,val);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    int queryMax(int l,int r,int id,int val){
        if(l==r){
            if(tree[id].Max<=val) return l;
            else return l-1;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(tree[id<<1].Max<=val) return queryMax(mid+1,r,id<<1|1,val);
        return queryMax(l,mid,id<<1,val);
    }
    int queryMin(int l,int r,int id,int val){
        if(l==r){
            if(tree[id].Min>=val) return l;
            else return l+1;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(tree[id<<1|1].Min>=val) return queryMin(l,mid,id<<1,val);
        return queryMin(mid+1,r,id<<1|1,val);
    }
    int queryMax2(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return LLONG_MIN;
        if(tl<=l && r<=tr) return tree[id].Max2;
        pushdown(id);
        int mid=(l+r)>>1;
        return max(queryMax2(l,mid,id<<1,tl,tr),queryMax2(mid+1,r,id<<1|1,tl,tr));
    }
    int queryp(int l,int r,int id,int p){
        if(l==r) return tree[id].Min;
        pushdown(id);
        int mid=(l+r)>>1;
        if(p<=mid) return queryp(l,mid,id<<1,p);
        else return queryp(mid+1,r,id<<1|1,p);
    }
    void print(int l,int r,int id){
        cout << l << ' ' << r << ' ' << tree[id].Min << ' ' << tree[id].Max << ' ' << tree[id].Max2 << '\n';
        if(l==r) return;
        pushdown(id);
        int mid=(l+r)>>1;
        print(l,mid,id<<1);print(mid+1,r,id<<1|1);
    }
}st;
bool check(int i){
    int d=st.queryp(1,n,1,i)+n;
    if(i<n && d<=st.queryMax2(1,n,1,i+1,n)) return false;
    return true;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    sort(a+1,a+n+1);
    st.build(1,n,1);
    int l=1;
    for(int i=1;i<=q;i++){
        char c;cin >> c;
        int x,y;
        if(c=='B'){
            cin >> x >> y;
            int p=st.queryMin(1,n,1,x);
            if(p<=n) st.update(1,n,1,p,n,y);
        }
        else if(c=='K'){
            cin >> x >> y;
            int p=st.queryMax(1,n,1,x);
            if(p>=1) st.update(1,n,1,1,p,-y);
        }
        else{
            while(l<=n && !check(l)) l++;
            cout << n-l+1 << '\n';
        }
        //st.print(1,n,1);
        //cout << '\n';
    }
}
