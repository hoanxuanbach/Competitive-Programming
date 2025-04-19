#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
const int inf = 1e9;
#define pii pair<int,int>
#define fi first
#define se second
int N,M,S;
int A[maxn],B[maxn],T[maxn],W[maxn];
int ans[maxn],ok[maxn];

struct BIT{
    int bit[2*maxn];
    void init(){
        for(int i=1;i<=S;i++) bit[i]=0;
    }
    void update(int x,int val){
        for(int i=x;i<=S;i+=(i&(-i))) bit[i]=max(bit[i],val);
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res=max(res,bit[i]);
        return res;
    }
}b0,b1;

void solve0(){
    map<pair<int,int>,int> mp;
    for(int i=0;i<N;i++){
        ok[i]=(!i || S+1-b0.query(A[i])<=B[i] || b1.query(S+1-A[i])>=B[i]);
        b0.update(A[i],S+1-B[i]);
        b1.update(S+1-A[i],B[i]);
    }
    b0.init();b1.init();
    for(int i=N-1;i>=0;i--){
        ok[i]&=(i==N-1 || S+1-b0.query(A[i])<=B[i] || b1.query(S+1-A[i])>=B[i]);
        b0.update(A[i],S+1-B[i]);
        b1.update(S+1-A[i],B[i]);
        mp[{A[i],B[i]}]|=ok[i];
    }
    for(int i=0;i<M;i++) ans[i]=mp[{T[i],W[i]}];
}

struct BIT2{
    pii bit[2*maxn];
    void init(){
        for(int i=1;i<=S;i++) bit[i]={N,N};
    }
    pii add(pii x,int y){
        if(y<x.fi) x.se=x.fi,x.fi=y;
        else if(y<x.se) x.se=y;
        return x;
    };
    pii add2(pii x,pii y){
        return add(add(x,y.fi),y.se);
    };
    void update(int x,int val){
        for(int i=x;i<=S;i+=(i&(-i))) bit[i]=add(bit[i],val);
    }
    pii query(int x){
        pii res={inf,inf};
        for(int i=x;i>=1;i-=(i&(-i))) res=add2(res,bit[i]);
        return res;
    }
}cc;
vector<int> f[maxn];
vector<pii> solve(bool suffix,bool upper,bool larger){
    if(suffix){
        reverse(A,A+N);
        reverse(B,B+N);
    }
    if(upper){
        for(int i=0;i<N;i++) swap(A[i],B[i]);
        for(int i=0;i<M;i++) swap(T[i],W[i]);
    }
    if(larger){
        for(int i=0;i<N;i++) B[i]=S-B[i]+1,A[i]=S-A[i]+1;
        for(int i=0;i<M;i++) W[i]=S-W[i]+1,T[i]=S-T[i]+1;
    }


    vector<pii> res(M);
    map<int,int> mp;
    for(int i=N-1;i>=0;i--) mp[A[i]]=i;
    b0.init();b1.init();
    for(int i=0;i<N;i++){
        b0.update(S+1-A[i],N-i);
        b1.update(B[i],N-i);
    }
    for(int i=0;i<M;i++) res[i].fi=N-max(b0.query(S+1-T[i]),b1.query(W[i]))+1;

    cc.init();
    vector<int> pp(N);
    vector<int> qq(M);
    iota(pp.begin(),pp.end(),0);
    iota(qq.begin(),qq.end(),0);
    sort(pp.begin(),pp.end(),[&](int x,int y){return A[x]>A[y];});
    sort(qq.begin(),qq.end(),[&](int x,int y){return T[x]>T[y];});
    int p=0;



    for(int id:qq){
        while(p<N && A[pp[p]]>=T[id]) cc.update(B[pp[p]],pp[p]),p++;
        pii cur=cc.query(W[id]);
        res[id].fi=min(N,(res[id].fi<=cur.fi || !cur.fi?cur.fi:cur.se));
        res[id].se=res[id].fi+1;
    }

    for(int i=0;i<=N;i++) f[i].clear();
    for(int i=0;i<M;i++) f[res[i].se].push_back(i);
    b0.init();b1.init();
    for(int i=N-1;i>=0;i--){
        b0.update(S+1-A[i],N-i);
        b1.update(B[i],N-i);
        for(int id:f[i]) res[id].se=N-max(b0.query(S+1-T[id]),b1.query(W[id]));
    }
    for(int i=0;i<M;i++){
        auto it=mp.find(T[i]);
        int pos=(it==mp.end()?N:it->se);
        if(pos>res[i].fi) res[i].fi=N;
        res[i].se=max(res[i].se,pos);
    }
    /*
    cout << suffix << ' ' << upper << ' ' << larger << endl;
    for(int i=0;i<N;i++) cout << A[i] << ' ' << B[i] << endl;
    for(int i=0;i<M;i++) cout << T[i] << ' ' << W[i] << ' ' << res[i].fi << ' ' << res[i].se << endl;
    cout << '\n';
    */
    if(larger){
        for(int i=0;i<N;i++) B[i]=S-B[i]+1,A[i]=S-A[i]+1;
        for(int i=0;i<M;i++) W[i]=S-W[i]+1,T[i]=S-T[i]+1;
    }
    if(upper){
        for(int i=0;i<N;i++) swap(A[i],B[i]);
        for(int i=0;i<M;i++) swap(T[i],W[i]);
    }
    if(suffix){
        reverse(A,A+N);
        reverse(B,B+N);
    }
    return res;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> M;S=N+M;
    vector<int> cu,cd;
    for(int i=0;i<N;i++){
        cin >> A[i] >> B[i];
        cu.push_back(A[i]);
        cd.push_back(B[i]);
    }
    for(int i=0;i<M;i++){
        cin >> T[i] >> W[i];
        cu.push_back(T[i]);
        cd.push_back(W[i]);
    }
    sort(cu.begin(),cu.end());
    cu.erase(unique(cu.begin(),cu.end()),cu.end());
    sort(cd.begin(),cd.end());
    cd.erase(unique(cd.begin(),cd.end()),cd.end());
    for(int i=0;i<N;i++){
        A[i]=lower_bound(cu.begin(),cu.end(),A[i])-cu.begin()+1;
        B[i]=lower_bound(cd.begin(),cd.end(),B[i])-cd.begin()+1;
        //cout << A[i] << ' ' << B[i] << '\n';
    }
    for(int i=0;i<M;i++){
        T[i]=lower_bound(cu.begin(),cu.end(),T[i])-cu.begin()+1;
        W[i]=lower_bound(cd.begin(),cd.end(),W[i])-cd.begin()+1;
        //cout << T[i] << ' ' << W[i] << '\n';
    }
    solve0();
    vector<vector<pii>> d(8);
    for(int i=0;i<8;i++) d[i]=solve(i>>2,i>>1&1,i&1);
    auto check = [&](pii x,pii y){
        if(x.fi+y.fi==N-2) return true;
        int val=min({x.fi+y.se,x.se+y.fi,x.se+y.se});
        return (val<N-1);
    };
    for(int i=0;i<M;i++){
        ans[i]|=check(d[0][i],d[6][i]);
        ans[i]|=check(d[1][i],d[7][i]);
        ans[i]|=check(d[2][i],d[4][i]);
        ans[i]|=check(d[3][i],d[5][i]);
    }
    for(int i=0;i<M;i++) if(ans[i]) cout << i+1 << ' ';
    cout << '\n';
}
