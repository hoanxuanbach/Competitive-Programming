#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
const int inf = 2e9;
const int B = 455;
const int maxn = 2e5+5;
const int mod = 998244353;

int n,m,a[maxn];

vector<pii> com;
int A[maxn],C[maxn];

struct Segment_tree{
    int mn[4*maxn],mx[4*maxn];
    void build(int l,int r,int id){
        if(l==r){
            mn[id]=mx[id]=a[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        mx[id]=max(mx[id<<1],mx[id<<1|1]);
        mn[id]=min(mn[id<<1],mn[id<<1|1]);
    }
    pii query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return {-inf,inf};
        if(tl<=l && r<=tr) return {mx[id],mn[id]};
        int mid=(l+r)>>1;
        pii a=query(l,mid,id<<1,tl,tr);
        pii b=query(mid+1,r,id<<1|1,tl,tr);
        return pii{max(a.first,b.first),min(a.second,b.second)};
    }
}ST;

int q,res[maxn],val[maxn],init[maxn];
struct Query{
    int l,r,v;
}queries[maxn];

int lt[maxn],rt[maxn],f[maxn];

#define range vector<array<int,3>>
#define matrix vector<range>

matrix build(vector<int> X){
    int sz=(int)X.size();
    if(sz==1){
        matrix ret(sz,range(sz));
        ret[0][0]={X[0],X[0],0};
        return ret;
    }
    vector<int> f(sz);

    vector<pii> P;
    for(int i=0;i<sz;i++) P.push_back({X[i],i});
    sort(P.begin(),P.end());

    for(int i=0;i<sz/2;i++) f[P[i].second]=1;

    vector<int> A,B;
    vector<int> clA(sz,sz),clB(sz,sz),crA(sz,-1),crB(sz,-1);
    for(int i=0;i<sz;i++){
        if(f[i]){
            clA[i]=crA[i]=(int)A.size();
            A.push_back(X[i]);
        }
        else{
            clB[i]=crB[i]=(int)B.size();
            B.push_back(X[i]);
        }
    }
    for(int i=1;i<sz;i++){
        if(crA[i]==-1) crA[i]=crA[i-1];
        if(crB[i]==-1) crB[i]=crB[i-1];
    }
    for(int i=sz-2;i>=0;i--){
        if(clA[i]==sz) clA[i]=clA[i+1];
        if(clB[i]==sz) clB[i]=clB[i+1];
    }

    matrix fA=build(A),fB=build(B);
    matrix ret(sz,range(sz));
    for(int l=0;l<sz;l++){
        ret[l][l]={X[l],X[l],0};
        for(int r=l+1;r<sz;r++){
            int lA=clA[l],rA=crA[r];
            int lB=clB[l],rB=crB[r];
            if(lA>rA) ret[l][r]=fB[lB][rB];
            else if(lB>rB) ret[l][r]=fA[lA][rA];
            else{
                ret[l][r][0]=fA[lA][rA][0];
                ret[l][r][1]=fB[lB][rB][1];
                ret[l][r][2]=max({fA[lA][rA][2],fB[lB][rB][2],fB[lB][rB][0]-fA[lA][rA][1]});
            }
        }
    }
    return ret;
}

void cal(int t){
    int L=t*B,R=min((t+1)*B,n);
    for(int i=0;i<n;i++) lt[i]=n,rt[i]=-1;

    vector<int> S;
    for(int i=L;i<R;i++) S.push_back(A[i]),f[A[i]]=i;
    sort(S.begin(),S.end());

    int sz=R-L;
    for(int i=0;i<sz;i++){
        lt[S[i]]=i;
        rt[S[i]]=i;
    }
    for(int i=1;i<n;i++) if(rt[i]==-1) rt[i]=rt[i-1];
    for(int i=n-2;i>=0;i--) if(lt[i]==n) lt[i]=lt[i+1];

    vector<int> P;
    for(int i=0;i<sz;i++){
        int x=S[i];x=f[x];
        P.push_back(C[x]);
    }
    matrix T=build(P);
    
    for(int i=0;i<q;i++){
        auto [l,r,v]=queries[i];
        if(v<C[R-1]){
            for(int j=L;j<R;j++){
                if(v<C[j]){
                    if(val[i]!=-1) res[i]=max(res[i],v-val[i]);
                    val[i]=v;v=inf;
                }
                if(A[j]<l || A[j]>r) continue;
                if(val[i]!=-1) res[i]=max(res[i],C[j]-val[i]);
                val[i]=C[j];
            }
            queries[i].v=inf;
        }
        else{
            
            l=lt[l];r=rt[r];
            if(l>r) continue;
            auto [x,y,t]=T[l][r];
            if(val[i]!=-1) res[i]=max(res[i],x-val[i]);
            res[i]=max(res[i],t);val[i]=y;
        }
    }
}

void solve(){
    cin >> n >> q >> m;
    for(int i=0;i<n;i++){
        cin >> a[i];
        com.push_back({a[i],i});
    }
    sort(com.begin(),com.end());
    for(int i=0;i<n;i++) A[i]=com[i].second,C[i]=com[i].first;

    ST.build(0,n-1,1);
    for(int i=0;i<q;i++){
        int l,r,v;cin >> l >> r >> v;l--;r--;
        queries[i]={l,r,v};val[i]=-1;
        pii P=ST.query(0,n-1,1,l,r);
        P.first=max(P.first,v);
        P.second=min(P.second,v);
        init[i]=P.first-P.second;
    }
    for(int i=0;i<=(n-1)/B;i++) cal(i);

    for(int i=0;i<q;i++){
        auto [l,r,v]=queries[i];
        if(v==inf) continue;
        if(val[i]!=-1) res[i]=max(res[i],v-val[i]);
    }
    for(int i=0;i<q;i++){
        auto [l,r,v]=queries[i];
        res[i]=min(m-res[i],init[i]);
        cout << res[i] << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
