#include<bits/stdc++.h>
using namespace std;
#define int unsigned int
#define pii pair<int,int>
#define fi first
#define se second
const int inf=(1U<<31);
const int maxn=2e5+5;
bool cmp(pii a,pii b){
    return make_pair(a.fi+a.se,a.fi)<make_pair(b.fi+b.se,b.fi);
}
pii x[maxn];
struct node{
    int cnt=0,sum=0;
    node *cl=nullptr,*cr=nullptr;
};
void update(node *p,int l,int r,int pos,int val){
    if(l==r){
        p->cnt+=val;p->sum+=val*pos;
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid){
        if(!(p->cl)) p->cl=new node();
        update(p->cl,l,mid,pos,val);
    }
    else{
        if(!(p->cr)) p->cr=new node();
        update(p->cr,mid+1,r,pos,val);
    }
    p->cnt=p->sum=0;
    if(p->cl){p->cnt+=p->cl->cnt;p->sum+=p->cl->sum;}
    if(p->cr){p->cnt+=p->cr->cnt;p->sum+=p->cr->sum;}
}
int query(node *p,int l,int r,int pos){
    if(l==r) return min(p->cnt,pos/l);
    int mid=(l+r)>>1;
    if(p->cl){
        if(p->cl->sum<=pos) return p->cl->cnt+(p->cr?query(p->cr,mid+1,r,pos-p->cl->sum):0);
        else return query(p->cl,l,mid,pos);
    }
    else return (p->cr?query(p->cr,mid+1,r,pos):0);
}
int query1(node *p,int l,int r,int pos){
    if(l==r) return p->cnt;
    int mid=(l+r)>>1;
    if(pos<=mid) return (p->cl?query1(p->cl,l,mid,pos):0);
    else return (p->cl?p->cl->cnt:0)+(p->cr?query1(p->cr,mid+1,r,pos):0);
}
int query2(node *p,int l,int r,int pos){
    if(pos==0) return 0;
    if(l==r) return l;
    int mid=(l+r)>>1;
    if(p->cl && p->cl->cnt>=pos) return query2(p->cl,l,mid,pos);
    else return query2(p->cr,mid+1,r,pos-(p->cl?p->cl->cnt:0));
}
signed main(){
    //freopen("input.in","r",stdin);
    //freopen("output.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,sz=0;cin >> n;
    for(int i=1;i<=n;i++){
        cin >> x[i].fi >> x[i].se;
        //x[i].fi=i;x[i].se=i;
    }
    sort(x+1,x+n+1,cmp);
    node *root=new node();
    for(int i=1;i<=n;i++){
        int r=query(root,1,inf,x[i].fi),l=query1(root,1,inf,x[i].se);
        //cout << r << ' ' << query2(root,1,inf,r) << '\n';
        if(l<=r){
            if(r==sz) sz++;
            else{
                int val=query2(root,1,inf,r+1);
                update(root,1,inf,val,-1);
                //cout << val << '\n';
                if(r+2<=sz){
                    int d=query2(root,1,inf,r+2);
                    update(root,1,inf,d,-1);
                    update(root,1,inf,val+d-x[i].se,1);
                }
            }
            update(root,1,inf,x[i].se,1);
        }
        //cout << l << ' ' << r << ' ' << x[i].fi << ' ' << x[i].se << ' ' << sz << ' ' << root->sum << '\n';
    }
    cout << sz << '\n' << (root->sum) << '\n';
}
