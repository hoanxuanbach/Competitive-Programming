#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 1500005;
struct Query{
    int t,id,x,y;
    Query(){}
    Query(int t=-1,int id=-1,int x=-1,int y=-1):t(t),id(id),x(x),y(y){}
};

int n,m,q;

int val[2*maxn],p[2*maxn],sz,f[maxn];
vector<int> cc[2*maxn];

int ss;
pii ans[maxn];

int add(int i,int v){
    val[++sz]=v,p[i]=sz;
    cc[sz]={i};
    return sz;
}
int unions(int a,int b){
    if((int)cc[a].size()<(int)cc[b].size()) swap(a,b);
    for(int id:cc[b]) p[id]=a,cc[a].push_back(id);
    cc[b].clear();
    return a;
}

void dnc(int l,int r,vector<Query> &qq){
    if(qq.empty()) return;
    int mid=(l+r)>>1;
    int X=mid,Y=n-mid;
    vector<Query> lq,rq;
    priority_queue<pii,vector<pii>,greater<pii>> px,py;
    sz=0;
    for(auto cq:qq){
        auto [t,id,x,y]=cq;
        if(t==1){
            if(f[id]==1) lq.push_back(cq);
            else if(f[id]==2) rq.push_back(cq);
            else ans[x]={val[p[id<<1]],val[p[id<<1|1]]};
        }
        else if(t==2){
            int d=x;
            if(d<Y){
                rq.push_back(cq);
                while(!py.empty() && py.top().fi<=d){
                    int cur=py.top().se;py.pop();
                    for(int id:cc[cur]){
                        if(!f[id>>1]){
                            f[id>>1]=2;
                            rq.push_back(Query(4,id>>1,n-d,val[cur]));
                        }
                    }
                }
            }
            else{
                int rt=0;
                while(!px.empty() && px.top().fi<=n-d){
                    int cur=px.top().se;px.pop();
                    rt=(rt?unions(rt,cur):cur);
                }
                if(rt) val[rt]=n-d,px.push({n-d,rt});
                lq.push_back(cq);
            }
        }
        else if(t==3){
            int d=x;
            if(d<X){
                lq.push_back(cq);
                while(!px.empty() && px.top().fi<=d){
                    int cur=px.top().se;px.pop();
                    for(int id:cc[cur]){
                        if(!f[id>>1]){
                            f[id>>1]=1;
                            lq.push_back(Query(4,id>>1,val[cur],n-d));
                        }
                    }
                }
            }
            else{
                int rt=0;
                while(!py.empty() && py.top().fi<=n-d){
                    int cur=py.top().se;py.pop();
                    rt=(rt?unions(rt,cur):cur);
                }
                if(rt) val[rt]=n-d,py.push({n-d,rt});
                rq.push_back(cq);
            }
        }
        else{

            if(x>X) f[id]=2,rq.push_back(cq);
            else if(y>Y) f[id]=1,lq.push_back(cq);
            else{
                f[id]=0;
                px.push({x,add(id<<1,x)});
                py.push({y,add(id<<1|1,y)});
            }
        }
    }
    if(l==r) return;
    if(l+1==r) dnc(r,r,rq);
    else dnc(l,mid,lq),dnc(mid,r,rq);

}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> q;
    vector<Query> qq;
    for(int i=1;i<=m;i++){
        int x,y;cin >> x >> y;
        qq.push_back(Query(4,i,x,y));
    }
    for(int i=1;i<=q;i++){
        int t;cin >> t;
        if(t==1){
            int id;cin >> id;
            qq.push_back(Query(1,id,++ss,-1));
        }
        else if(t<=3){
            int d;cin >> d;
            qq.push_back(Query(t,-1,d,-1));
        }
        else{
            int x,y;cin >> x >> y;
            qq.push_back(Query(4,++m,x,y));
        }
    }
    dnc(0,n,qq);
    for(int i=1;i<=ss;i++) cout << ans[i].fi << ' ' << ans[i].se << '\n';
}
