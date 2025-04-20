#include "meetings.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
const ll inf = 1e18;

struct line{
    ll a=0,b=0,p=inf;
    line(ll a=0,ll b=0,ll p=inf):a(a),b(b),p(p){}
    bool operator<(line &o){return a>o.a;}
    bool operator<(ll k){return p<k;}
};
struct cvht{
    vector<line> x;
    cvht(){}
    ll div(ll a,ll b){
        return a/b-((a^b)<0 && a%b);
    }
    void isect(line &l,line &y){
        if(l.a==y.a) l.p=(l.b<y.b?inf:-inf);
        else l.p=div(l.b-y.b,y.a-l.a);
    }
    void add(line l){
        //cout << "add " << l.a << ' ' << l.b << ' ' << l.p << '\n';
        if(!x.empty()) isect(x.back(),l);
        while((int)x.size()>=2 && x[(int)x.size()-2].p>=x.back().p) x.pop_back(),isect(x.back(),l);
        x.push_back(l);
    }
    ll query(ll k){
        if(x.empty()) return inf;
        //cout << x.back().p << '\n';
        auto v=*lower_bound(x.begin(),x.end(),k);
        //cout << "get " << k << ' ' << v.a << ' ' << v.b << '\n';
        return v.a*k+v.b;
    }
};

std::vector<ll> minimum_costs(std::vector<int> H, std::vector<int> L,
                                     std::vector<int> R) {
    int N=(int)H.size(),Q=(int)L.size();
    vector<ll> res(Q,inf);

    vector<int> lt(N,-1),rt(N,-1),p(N,-1);
    vector<vector<int>> f(N);

    vector<int> v;
    for(int i=0;i<N;i++){
        while(!v.empty() && H[v.back()]<=H[i]) v.pop_back();
        lt[i]=(v.empty()?-1:v.back());
        v.push_back(i);
    }
    v.clear();
    for(int i=N-1;i>=0;i--){
        while(!v.empty() && H[v.back()]<H[i]) v.pop_back();
        rt[i]=(v.empty()?-1:v.back());
        v.push_back(i);
    }
    for(int i=0;i<N;i++){
        if(lt[i]==-1 || (rt[i]!=-1 && H[rt[i]]<H[lt[i]])) p[i]=rt[i];
        else p[i]=lt[i];
    }
    for(int i=0;i<N;i++) lt[i]=rt[i]=-1;
    int T=-1;
    for(int i=0;i<N;i++){
        if(p[i]==-1) T=i;
        else if(p[i]<i) rt[p[i]]=i;
        else lt[p[i]]=i;
    }
    {
        vector<pii> mx(4*N);
        function<void(int,int,int)> build = [&](int l,int r,int id){
            if(l==r){mx[id]={H[l],l};return;}
            int mid=(l+r)>>1;
            build(l,mid,id<<1);build(mid+1,r,id<<1|1);
            mx[id]=max(mx[id<<1],mx[id<<1|1]);
        };
        function<pii(int,int,int,int,int)> query = [&](int l,int r,int id,int tl,int tr){
            if(tr<l || r<tl) return make_pair(0,-1);
            if(tl<=l && r<=tr) return mx[id];
            int mid=(l+r)>>1;
            return max(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
        };
        build(0,N-1,1);
        //for(int i=0;i<N;i++) cout << lt[i] << ' ' << rt[i] << '\n';
        for(int i=0;i<Q;i++){
            int u=query(0,N-1,1,L[i],R[i]).se;
            f[u].push_back(i);
            res[i]=1LL*H[u]*(R[i]-L[i]+1);
            //cout << "* " << u << ' ' << i << '\n';
        }
    }
    auto solve = [&]{
        vector<cvht> cht(4*N);
        vector<ll> total(4*N,0);
        function<void(int,int,int,int,int,ll)> update_add = [&](int l,int r,int id,int tl,int tr,ll val){
            if(tr<l || r<tl) return;
            if(tl<=l && r<=tr){
                total[id]+=val;
                return;
            }
            int mid=(l+r)>>1;
            update_add(l,mid,id<<1,tl,tr,val);update_add(mid+1,r,id<<1|1,tl,tr,val);
        };
        function<void(int,int,int,int,int,line)> update_val = [&](int l,int r,int id,int tl,int tr,line ln){
            if(tr<l || r<tl) return;
            if(tl<=l && r<=tr){
                //cout << "update " << l << ' ' << r << ' ' << id << ' ' << ln.a << ' ' << ln.b << '\n';
                ln.b-=total[id];
                cht[id].add(ln);
                return;
            }
            int mid=(l+r)>>1;
            update_val(l,mid,id<<1,tl,tr,ln);update_val(mid+1,r,id<<1|1,tl,tr,ln);
        };
        function<ll(int,int,int,int)> query = [&](int l,int r,int id,int p){
            if(l==r) return total[id]+cht[id].query(-p);
            int mid=(l+r)>>1;
            ll res=cht[id].query(-p);
            if(p<=mid) res=min(res,query(l,mid,id<<1,p));
            else res=min(res,query(mid+1,r,id<<1|1,p));
            //cout << "query " << l << ' ' << r << ' ' << id << ' ' << p << ' ' << res << ' ' << total[id] << '\n';
            return total[id]+res;
        };

        vector<ll> val(N);
        function<void(int,int,int)> dfs = [&](int l,int r,int u){
            val[u]=1LL*(r-l+1)*H[u];

            ll num=H[u];
            if(l<u){
                dfs(l,u-1,lt[u]);num+=val[lt[u]];
                val[u]=min(val[u],val[lt[u]]+1LL*(r-u+1)*H[u]);
            }
            if(u<r){
                dfs(u+1,r,rt[u]);
                val[u]=min(val[u],val[rt[u]]+1LL*(u-l+1)*H[u]);
            }
            for(int id:f[u]) res[id]=min(res[id],query(0,N-1,1,R[id])+1LL*H[u]*(u-L[id]+1));
            update_add(0,N-1,1,u,r,1LL*H[u]*(u-l+1));
            update_val(0,N-1,1,u,r,line(-H[u],num-1LL*H[u]*u,inf));
        };
        dfs(0,N-1,T);
        //cout << '*' << val[T] << '\n';
    };
    solve();
    for(int i=0;i<Q;i++) swap(L[i],R[i]),L[i]=N-1-L[i],R[i]=N-1-R[i];
    reverse(H.begin(),H.end());
    reverse(f.begin(),f.end());
    reverse(lt.begin(),lt.end());
    reverse(rt.begin(),rt.end());
    T=N-1-T;
    //cout << T << '\n';
    for(int i=0;i<N;i++){
        swap(lt[i],rt[i]);
        if(lt[i]!=-1) lt[i]=N-1-lt[i];
        if(rt[i]!=-1) rt[i]=N-1-rt[i];
        //cout << lt[i] << ' ' << rt[i] << '\n';
    }
    solve();
    return res;
}
