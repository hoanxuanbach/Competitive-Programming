#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e18;
const int maxn = 200015;

int n,m,d,a[maxn],b[maxn];

struct node{
    int lt=-inf,rt=-inf,val=0,cnt=0;
    node(){}
    node(int x){
        lt=x,rt=d-x;
        val=0,cnt=d;
    }
    friend node operator+(node a,node b){
        node res;
        res.lt=max(a.lt+b.cnt,b.lt);
        res.rt=max(a.rt,a.cnt+b.rt);
        res.val=max({a.val,b.val,a.lt+b.rt});
        res.cnt=a.cnt+b.cnt;
        return res;
    }
}tree[4*maxn];
void update(int l,int r,int id,int x,int val){
    if(l==r){
        tree[id]=node(val);
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) update(l,mid,id<<1,x,val);
    else update(mid+1,r,id<<1|1,x,val);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> d;
    vector<pair<int,int>> com;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        com.push_back({a[i],i});
    }
    for(int i=1;i<=m;i++){
        cin >> b[i];
        com.push_back({b[i],n+i});
    }
    sort(com.begin(),com.end());
    int sz=(int)com.size();
    for(int i=1;i<=n;i++){
        int pos=lower_bound(com.begin(),com.end(),make_pair(a[i],i))-com.begin()+1;
        update(1,sz,1,pos,a[i]);
    }
    for(int i=1;i<=m;i++){
        int pos=lower_bound(com.begin(),com.end(),make_pair(b[i],n+i))-com.begin()+1;
        update(1,sz,1,pos,b[i]);
        int k=max(0LL,tree[1].val);
        cout << k/2;
        if(k&1) cout << ".5 ";
        else cout << " ";
    }
    cout << '\n';
}
