#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 2e9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

const int L = 18;

void solve(){
    int n,q;cin >> n >> q;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];

    vector<int> lg2(n+1);
    for(int i=2;i<=n;i++) lg2[i]=lg2[i/2]+1;

    vector<vector<int>> f(n+1,vector<int>(L));
    for(int i=1;i<=n;i++) f[i][0]=a[i];
    for(int j=1;j<L;j++) for(int i=1;i+(1<<j)<=n+1;i++) f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
    auto query_min = [&](int l,int r){
        if(l>r) return inf;
        int k=lg2[r-l+1];
        return min(f[l][k],f[r-(1<<k)+1][k]);
    };

    vector<int> nxt(n+1),pre(n+1);
    for(int i=1;i<=n;i++) nxt[i]=i%n+1,pre[i%n+1]=i;

    vector<int> ord(n);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return a[x]>a[y];
    });
    vector<vector<array<int,3>>> g(n);
    auto get = [&](int l,int r){
        return max(a[l],a[r])+query_min(l+1,r-1);
    };

    vector<array<int,3>> S;
    for(int i=0;i<n;i++){
        int x=ord[i];
        int l=pre[x],r=nxt[x];
        if(l+1<x) g[i].push_back({l,x,-1});
        if(x+1<r) g[i].push_back({x,r,-1});
        if(l+1<r){
            g[i].push_back({l,r,1});
            S.push_back({get(l,r),l,r});
        }
        nxt[l]=r;pre[r]=l;
    }

    int m=(int)S.size();
    sort(S.begin(),S.end());
    for(int i=0;i<n;i++){
        //cout << ord[i] << ' ' << a[ord[i]] << '\n';
        for(int j=0;j<(int)g[i].size();j++){
            auto [l,r,d]=g[i][j];
            //cout << l << ' ' << r << ' ' << d << '\n';
            array<int,3> cur={get(l,r),l,r};
            g[i][j][0]=m-1-(lower_bound(S.begin(),S.end(),cur)-S.begin());
        }
    }
    reverse(S.begin(),S.end());

    vector<pii> qq;
    vector<int> L(q),R(q),K(q),lt(q),rt(q);
    for(int i=0;i<q;i++){
        cin >> L[i] >> R[i] >> K[i];
        lt[i]=0;rt[i]=inf;
        qq.push_back({(lt[i]+rt[i])/2,i});
    }

    
    while(!qq.empty()){

        vector<pii> nq;

        sort(qq.begin(),qq.end(),greater<pii>());
        
        vector<int> s(n+1),f(n+1);
        auto update = [&](vector<int> &bit,int x,int val){
            for(int i=x;i<(int)bit.size();i+=(i&(-i))) bit[i]+=val;
        };
        auto query = [&](vector<int> &bit,int x){
            int cnt=0;
            for(int i=x;i>=1;i-=(i&(-i))) cnt+=bit[i];
            return cnt;
        };

        set<int> ss;
        for(int i=1;i<=n;i++) ss.insert(i),update(f,i,1);

        vector<bool> ins(m);
        
        int pos=0,t=0;
        for(auto [W,id]:qq){
            while(t<m && S[t][0]>W){
                if(ins[t]) update(s,S[t][1],-1);
                t++;
            }
            while(pos<n && a[ord[pos]]>W/2){
                for(auto [i,_,d]:g[pos]){
                    if(i<t) continue;
                    if(d==1) ins[i]=true,update(s,S[i][1],1);
                    else ins[i]=false,update(s,S[i][1],-1);
                }
                update(f,ord[pos],-1);
                ss.erase(ord[pos]);
                //cout << "erase " << ord[pos] << '\n';
                pos++;
            }
            int cnt=query(f,R[id])-query(f,L[id]-1);
            //cout << W << ' ' << id << ' ' << cnt << '\n';

            auto it=ss.lower_bound(L[id]);
            int ll=n+1;
            if(it!=ss.end()) ll=*it;

            it=ss.upper_bound(R[id]);
            int rr=0;
            if(it!=ss.begin()){
                it=prev(it);
                rr=*it;
            }
            //cout << ll << ' ' << rr << '\n';
            if(ll<=rr){
                int add=query(s,rr-1)-query(s,ll-1);cnt+=add;
                int val=min(query_min(rr+1,R[id]),query_min(L[id],ll-1));
                //cout << add << ' ' << val << ' ' << val+max(a[ll],a[rr]) << '\n';
                if(val+max(a[ll],a[rr])<=W) cnt++;
            }

            if(cnt>=K[id]) rt[id]=W;
            else lt[id]=W+1;
            if(lt[id]<rt[id]) nq.push_back({(lt[id]+rt[id])/2,id});
        }
        swap(qq,nq);
    }

    for(int i=0;i<q;i++) cout << lt[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
