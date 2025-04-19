#include<bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
*/
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
//#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
//int mod=998244353;
const int maxn=100005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=101;

int rand(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn],p2[maxn];

void combi(int n){
    fac[0]=p2[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod,p2[i]=p2[i-1]*2%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

int C(int n,int k){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

int N,M,cnt[maxn],L[maxn],R[maxn],res[maxn];

struct Linked_List{
    bool use[maxn];
    int sz,nxt[maxn],pre[maxn];
    void build(int _sz){
        sz=_sz;
        for(int i=0;i<=sz;i++) nxt[i]=i+1,pre[i+1]=i,use[i]=true;
    }
    void del(int x){
        //cout << "del " << x << '\n';
        use[x]=false;
        int u=pre[x],v=nxt[x];sz--;
        nxt[u]=v,pre[v]=u;
    }
    int jmp(int x){
        return nxt[x];
    }
}X;
struct Segtree{
    vector<pii> tree;
    vector<int> pp;
    vector<piii> val;
    Segtree(){}
    Segtree(vector<piii> _val):val(_val){
        tree.assign(4*M,{-inf,-1});
        sort(val.begin(),val.end());
        build(0,M-1,1);
    }
    void reset(){
        pp.clear();
        for(int i=1;i<4*M;i++) tree[i]={-inf,-1};
    }
    void clear(){
        for(int i:pp) update(0,M-1,1,i);
        pp.clear();
    }
    void build(int l,int r,int id){
        if(l==r){
            tree[id]=val[l].se;
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    }
    pii query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return {-inf,-1};
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return max(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    }
    pii get(int l,int r){
        l=lower_bound(val.begin(),val.end(),piii{l,{-inf,-inf}})-val.begin();
        r=upper_bound(val.begin(),val.end(),piii{r,{inf,inf}})-val.begin()-1;
        if(l>r) return {-inf,-1};
        return query(0,M-1,1,l,r);
    }
    void update(int l,int r,int id,int x){
        if(l==r){
            if(tree[id].fi!=-inf) tree[id]={-inf,-1};
            else tree[id]=val[l].se;
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) update(l,mid,id<<1,x);
        else update(mid+1,r,id<<1|1,x);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    }
    void del(piii x){
        int pos=lower_bound(val.begin(),val.end(),x)-val.begin();
        pp.push_back(pos);
        update(0,M-1,1,pos);
    }
};

void solve(){
    cin >> N >> M;
    //if(M>400) return;
    for(int i=0;i<N;i++){int x;cin >> x;cnt[x]++;}
    for(int i=1;i<=M;i++) cin >> L[i] >> R[i];
    
    vector<piii> val(M);
    for(int i=1;i<=M;i++) val[i-1]={L[i],{-i,i}};
    Segtree sL(val);
    for(int i=1;i<=M;i++) val[i-1]={R[i],{-i,i}};
    Segtree sR(val);
    for(int i=1;i<=M;i++) val[i-1]={L[i],{R[i],i}};
    Segtree sval(val);
    for(int i=1;i<=M;i++) val[i-1]={L[i],{-R[i],i}};
    Segtree sLt(val);
    sLt.reset();
    for(int i=1;i<=M;i++) val[i-1]={R[i],{L[i],i}};
    Segtree sRt(val);
    sRt.reset();
    
    X.build(M);
    for(int k=N;k>=1;k--){
        if(!cnt[k]) continue;
        
        auto del = [&](int u){
            res[u]=k;
            sL.del({L[u],{-u,u}});
            sR.del({R[u],{-u,u}});
            sval.del({L[u],{R[u],u}});
            X.del(u);
            sLt.del({L[u],{-R[u],u}});
            sRt.del({R[u],{L[u],u}});     
        };

        auto get = [&](int d){
            int u=0;
            vector<pii> P;
            for(int i=0;i<d;i++){
                u=X.jmp(u);
                P.push_back({R[u],L[u]});
            }
            sort(P.begin(),P.end());
            int num=0,pos=0;
            for(auto [r,l]:P) if(l>pos) pos=r,num++;
            return num;
        };
        
        
        int d=1;
        while(2*d<=X.sz && get(2*d)<=cnt[k]) d<<=1;
        int ld=d,rd=min(2*d-1,X.sz);
        while(ld<rd){
            int mid=(ld+rd+1)>>1;
            if(get(mid)<=cnt[k]) ld=mid;
            else rd=mid-1;
        }
        

        /*
        int ld=1;
        while(ld+1<=X.sz && get(ld+1)<=cnt[k]) ld++;
        */
        if(ld==X.sz){
            int u=0;
            for(int i=0;i<ld;i++){
                u=X.jmp(u);
                res[u]=k;
            }
            break;
        }

        vector<pii> P;
        for(int i=0;i<ld;i++){
            int u=X.jmp(0);
            del(u);
            P.push_back({R[u],L[u]});       
        }

        int sz=cnt[k];
        vector<int> sl,sr;

        auto build_range = [&]{
            sl.clear();
            sr.clear();
            sort(P.begin(),P.end());
            for(auto [r,l]:P) if(sr.empty() || l>sr.back()) sr.push_back(r);
            
            sort(P.begin(),P.end(),[&](pii x,pii y){
                return x.se>y.se;
            });
            for(auto [r,l]:P) if(sl.empty() || r<sl.back()) sl.push_back(l);
            
            if(sz!=(int)sl.size() || sz!=(int)sr.size()){
                assert(false);
                return;
            }
            
            reverse(sl.begin(),sl.end());

        };
        build_range();

        //cout << '*' << k << ' ' << ld << '\n';
        //for(int i=0;i<sz;i++) cout << sl[i] << ' ' << sr[i] << '\n';

        
        auto add = [&](int lt,int rt){
            //cout << "add " << lt << ' ' << rt << '\n';
            while(true){
                auto [r,id] = sval.get(1,lt);
                //cout << r << ' ' << id << '\n';
                if(r>=rt) del(id);
                else return;
            }
        };

        for(int i=0;i<sz;i++) add(sl[i],sr[i]);

        vector<int> f(sz,-1);
        set<pii> ss;

        auto get_id = [&](int i){
            pii x=max(sL.get(sl[i],sr[i]),sR.get(sl[i],sr[i]));
            f[i]=(x.fi!=-inf?-x.fi:-1LL);
            //cout << i << ' ' << f[i] << '\n';
            if(f[i]!=-1) ss.insert({f[i],i});
        };

        for(int i=0;i<sz;i++) get_id(i);
        
        while(!ss.empty()){
            auto [id,t]=*ss.begin();ss.erase(ss.begin());
            if(!X.use[id]){
                get_id(t);
                continue;
            }
            int pl=lower_bound(sr.begin(),sr.end(),L[id])-sr.begin();
            int pr=lower_bound(sr.begin(),sr.end(),R[id])-sr.begin();
            bool cl=(pl<sz && sl[pl]<=L[id]),cr=(pr<sz && sl[pr]<=R[id]);
            assert(cl || cr);
            //cout << "pq " << id << ' ' << cl << ' ' << cr << '\n';
            del(id);
            get_id(t);
            //build_range();
            if(cr){

                int i=pr;
                while(i<sz){
                    int x=(i>0?sr[i-1]+1:0);
                    int nx=-sLt.get(x,inf).fi;
                    if(nx==sr[i]) break;
                    sr[i]=nx,i++;
                }
                i--;
                
                //int i=sz-1;
                for(int j=pr;j<=i;j++) add(sl[j],sr[j]);
                for(int j=pr;j<=i;j++){
                    if(f[j]!=-1) ss.erase({f[j],j});
                    get_id(j);
                }
            }
            if(cl){
                
                int i=pl;
                while(i>=0){
                    int x=(i+1<sz?sl[i+1]-1:inf);
                    int nx=sRt.get(1,x).fi;
                    if(nx==sl[i]) break; 
                    //cout << "cl " << i << ' ' << nx << '\n';
                    sl[i]=nx,i--;
                }
                i++;
                
                //int i=0;
                for(int j=i;j<=pl;j++) add(sl[j],sr[j]);
                for(int j=i;j<=pl;j++){
                    if(f[j]!=-1) ss.erase({f[j],j});
                    get_id(j);
                }
            }
        }   
        
        sLt.clear();
        sRt.clear();
        if(!X.sz) break;
    }
    for(int i=1;i<=M;i++) cout << res[i] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
