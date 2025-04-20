#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 100005;
const int inf = 1e18;
int n,q;
char c[maxn];
int lt[maxn],rt[maxn],dd[maxn];

int sz;
vector<int> com;

struct node{
    int Max=0,sum=0,lazy=inf;
    node(){}
    friend node operator+(node a,node b){
        node res;
        res.sum=a.sum+b.sum;
        res.Max=max(a.Max,a.sum+b.Max);
        return res;
    }
}tree[8*maxn];

void getnew(int l,int r,int id,int val){
    tree[id].sum=(com[r]-com[l-1])*val;
    tree[id].Max=max(0LL,tree[id].sum);
    tree[id].lazy=val;
}

void pushdown(int l,int r,int id){
    if(tree[id].lazy==inf) return;
    int mid=(l+r)>>1;
    getnew(l,mid,id<<1,tree[id].lazy);
    getnew(mid+1,r,id<<1|1,tree[id].lazy);
    tree[id].lazy=inf;
}

void update(int l,int r,int id,int tl,int tr,int val){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        getnew(l,r,id,val);
        return;
    }
    pushdown(l,r,id);
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

int query(int l,int r,int id,int x){
    if(tree[id].Max<=x) return com[r]-1;
    if(l==r){
        int d=tree[id].sum/(com[r]-com[l-1]);
        return com[l-1]+x/d-1;
    }
    pushdown(l,r,id);
    int mid=(l+r)>>1;
    if(tree[id<<1].Max<=x) return query(mid+1,r,id<<1|1,x-tree[id<<1].sum);
    else return query(l,mid,id<<1,x);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    while(true){
        char x;cin >> x;
        if(x=='E') break;
        c[++q]=x;
        if(x=='I'){
            cin >> lt[q] >> rt[q] >> dd[q];
            com.push_back(lt[q]);
            com.push_back(rt[q]+1);
        }
        else cin >> dd[q];
    }
    com.push_back(1);
    com.push_back(n+1);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int sz=(int)com.size()-1;
    for(int i=1;i<=q;i++){
        if(c[i]=='I'){
            int l=lower_bound(com.begin(),com.end(),lt[i])-com.begin()+1;
            int r=lower_bound(com.begin(),com.end(),rt[i]+1)-com.begin();
            update(1,sz,1,l,r,dd[i]);
        }
        else cout << query(1,sz,1,dd[i]) << '\n';
    }
}
