#include<bits/stdc++.h>
using namespace std;
#define maxn 200005
#define int long long
#define pii pair<int,int>
struct node{
    int cnt,l,r;
};
int n,n1,h1,n2,h2,ans,ht;
vector<pii> p;
namespace st{
    int tree[4*maxn],cnt[4*maxn];
    void build(int l,int r,int id){
        tree[id]=cnt[id]=0;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    }
    void update(int l,int r,int id,int p,int val){
        if(l==r){
            tree[id]+=val;
            if(val<0) cnt[id]--;
            else cnt[id]++;
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,val);
        else update(mid+1,r,id<<1|1,p,val);
        tree[id]=tree[id<<1]+tree[id<<1|1];
        cnt[id]=cnt[id<<1]+cnt[id<<1|1];
    }
    int query(int l,int r,int id,int x){
        if(l==r){
            if(cnt[id]==0) return 0;
            else return (tree[id]*x/cnt[id]);
        }
        int mid=(l+r)>>1;
        if(cnt[id<<1]<x) return tree[id<<1]+query(mid+1,r,id<<1|1,x-cnt[id<<1]);
        else return query(l,mid,id<<1,x);
    }
};
int num1,num2,sz;
vector<int> cm;
void add(int x,int val){
    int d=(x-1)/h1+1;
    num1+=val*(d%ht);num2+=val*(d/ht);
    int pos=sz-(lower_bound(cm.begin(),cm.end(),d%ht)-cm.begin());
    if(d%ht!=0) st::update(1,sz,1,pos,val*(d%ht));
}
bool check(){
    if(n2>num2){
        if(num1-st::query(1,sz,1,n2-num2)<=n1) return true;
        else return false;
    }
    else{
        if((num2-n2)*ht+num1<=n1) return true;
        else return false;
    }
}
void solve(){
    vector<pii> v;
    cm.clear();num1=num2=0;
    cm.push_back(0);
    for(auto x:p){
        int cur=x.first-x.second;
        while(!v.empty() && cur<=v.back().first){
            cur=min(cur,v.back().second);
            v.pop_back();
        }
        if(!v.empty()){
            int d=(cur-v.back().first-1)/h1+1;
            if(d%ht!=0) cm.push_back(d%ht);
        }
        v.push_back({x.first,cur});
    }
    sort(cm.begin(),cm.end());
    cm.erase(unique(cm.begin(),cm.end()),cm.end());
    sz=cm.size();
    st::build(1,sz,1);
    deque<node> dq;
    int total=0;
    for(auto x:p){
        int cur=x.first-x.second,c=1;total++;
        while(!dq.empty() && cur<=dq.back().r){
            int l=dq.back().l;cur=min(cur,l);c+=dq.back().cnt;
            dq.pop_back();
            if(!dq.empty()) add(l-dq.back().r,-1);
        }
        if(!dq.empty()) add(cur-dq.back().r,1);
        dq.push_back({c,cur,x.first});
        while(!check()){
            int r=dq.front().r;
            total-=dq.front().cnt;dq.pop_front();
            add(dq.front().l-r,-1);
        }
        ans=max(ans,total);
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++){
        int x,h;cin >> x >> h;
        p.push_back({x,h});
    }
    cin >> n1 >> h1 >> n2 >> h2;
    if(h1%h2==0){swap(n1,n2);swap(h1,h2);}
    ht=h2/h1;
    solve();
    int lst=p.back().second;
    for(auto &x:p) x.first=lst-x.first+1;
    reverse(p.begin(),p.end());
    solve();
    cout << ans+n1+n2 << '\n';
}
