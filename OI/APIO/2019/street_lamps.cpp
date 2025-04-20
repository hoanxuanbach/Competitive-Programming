#include<bits/stdc++.h>
using namespace std;
#define maxn 300005
#define fi first
#define se second
typedef pair<int,int> pii;
typedef vector<int> vi;
struct query{
    int t,a,b,id,pt;
    bool operator<(query o){
        if(a!=o.a) return a>o.a;
        else return t>o.t;
    }
};
bool cmp(query x,query y){
    if(x.b!=y.b) return x.b<y.b;
    else return x.t>y.t;
}
struct segtre{
    int tree[4*maxn],lazy[4*maxn];
    void pushdown(int l,int r,int id){
        if(lazy[id]==0) return;
        int mid=(l+r)>>1,lz=lazy[id];lazy[id]=0;
        lazy[id<<1]+=lz;lazy[id<<1|1]+=lz;
        tree[id<<1]+=lz*(mid-l+1);tree[id<<1|1]+=lz*(r-mid);
    }
    int query(int l,int r,int id,int p){
        if(l==r) return tree[id];
        pushdown(l,r,id);
        int mid=(l+r)>>1;
        if(p<=mid) return query(l,mid,id<<1,p);
        else return tree[id<<1]+query(mid+1,r,id<<1|1,p);
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            lazy[id]+=val;tree[id]+=val*(r-l+1);
            return;
        }
        pushdown(l,r,id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
}st;
map<pii,vector<int>> mp;
set<pii> s;
int n,q,f[maxn],ans[maxn],sz;
query que[maxn],qu[6*maxn];
//For each pair(l,r) find all time that l->r is all 1s and l-1,r+1 are 0s
void get(int p,int t){
    if(f[p]==1){
        pii x=*(--s.upper_bound({p,n+2}));
        mp[x].push_back(t);s.erase(x);
        if(x.first==p && x.second>p+1){
            x.first++;s.insert(x);
            mp[x].push_back(t);
        }
        else if(x.second==p+1 && x.first<p){
            x.second--;s.insert(x);
            mp[x].push_back(t);
        }
        else if(x.second>p+1 && p>x.first){
            s.insert({x.first,p});mp[{x.first,p}].push_back(t);
            s.insert({p+1,x.second});mp[{p+1,x.second}].push_back(t);
        }
    }
    else{
        if(f[p-1]==0 && f[p+1]==0){
            s.insert({p,p+1});mp[{p,p+1}].push_back(t);
        }
        else if(f[p-1]==1 && f[p+1]==0){
            pii x=*(--s.lower_bound({p,n}));
            s.erase(x);mp[x].push_back(t);
            s.insert({x.first,p+1});mp[{x.first,p+1}].push_back(t);
        }
        else if(f[p-1]==0 && f[p+1]==1){
            pii x=*s.upper_bound({p,n});
            s.erase(x);mp[x].push_back(t);
            s.insert({p,x.second});mp[{p,x.second}].push_back(t);
        }
        else{
            pii x1=*(--s.lower_bound({p,n})),x2=*s.upper_bound({p,n});
            s.erase(x1);mp[x1].push_back(t);
            s.erase(x2);mp[x2].push_back(t);
            s.insert({x1.first,x2.second});mp[{x1.first,x2.second}].push_back(t);
        }
    }
    f[p]^=1;
}
void dnc(int l,int r){
    if(l==r) return;
    int mid=(l+r)>>1;
    dnc(l,mid);dnc(mid+1,r);
    for(int i=l;i<=mid;i++) qu[i].pt=1;
    for(int i=mid+1;i<=r;i++) qu[i].pt=2;
    sort(qu+l,qu+r+1,cmp);
    //cout << l << ' ' << r << '\n';
    for(int i=r;i>=l;i--){
        if(qu[i].pt==2 && qu[i].t==1){
            int k=0,pre=0;
            for(int x:mp[{qu[i].a,qu[i].b}]){
                k++;
                if(k&1) pre=x;
                else{
                    st.update(1,q+1,1,pre,x-1,1);
                }
            }
        }
        else if(qu[i].pt==1 && qu[i].t==2) ans[qu[i].id]+=st.query(1,q+1,1,qu[i].id);
        //cout << "{ " << qu[i].t << ' ' << qu[i].a << ' ' << qu[i].b << ' ' << qu[i].id << ' ' << qu[i].pt << ' ' << ans[qu[i].id] << "}\n";
    }
    for(int i=l;i<=r;i++){
        if(qu[i].pt==2 && qu[i].t==1){
            int k=0,pre=0;
            for(int x:mp[{qu[i].a,qu[i].b}]){
                k++;
                if(k&1) pre=x;
                else st.update(1,q+1,1,pre,x-1,-1);
            }
        }
    }
}
//Main
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> q;
    int l=-1;
    for(int i=1;i<=n;i++){
        char c;cin >> c;
        f[i]=c-'0';
        if(f[i]==1){
            if(l==-1) l=i;
        }
        else if(l!=-1){s.insert({l,i});l=-1;}
    }
    if(l!=-1) s.insert({l,n+1});
    for(auto x:s) mp[x].push_back(1);
    //for(pii x:s) cout << "{ " << x.first << ' ' << x.second << "} ";
    //cout << '\n';
    for(int i=1;i<=q;i++){
        string ss;cin >> ss;
        if(ss[0]=='t'){
            que[i].t=1;que[i].id=i;
            cin >> que[i].a;
            get(que[i].a,i+1);
        }
        else{
            que[i].t=2;que[i].id=i;
            cin >> que[i].a >> que[i].b;
        }
        //for(pii x:s) cout << "{ " << x.first << ' ' << x.second << "} ";
        //cout << '\n';
    }
    for(auto &x:mp){
        qu[++sz]={1,x.fi.fi,x.fi.se,0,0};
        if((int)x.second.size()&1) x.second.push_back(q+2);
        //cout << x.fi.fi << '*' <<  x.fi.se << '\n';
        //for(int v:x.second) cout << v << ' ';
        //cout << '\n';
    }
    for(int i=1;i<=q;i++){
        if(que[i].t==2) qu[++sz]=que[i];
    }
    sort(qu+1,qu+sz+1);
    /*
    for(int i=1;i<=sz;i++){
        cout << "{ " << qu[i].t << ' ' << qu[i].a << ' ' << qu[i].b << ' ' << qu[i].id << ' ' << qu[i].pt << "}\n";
    }
    */
    dnc(1,sz);
    for(int i=1;i<=q;i++){
        if(que[i].t==2) cout << ans[i] << '\n';
    }
}
