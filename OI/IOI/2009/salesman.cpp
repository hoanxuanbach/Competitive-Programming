#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 5e5+5;
const int inf = 1e18;
int N,D,U,S,T,M;
vector<pii> F[maxn];

struct BIT{
    int bit[maxn];
    BIT(){}
    void init(){
        for(int i=1;i<=M;i++) bit[i]=-inf;
    }
    void update(int x,int val){
        for(int i=x;i<=M;i+=(i&(-i))) bit[i]=max(bit[i],val);
    }
    int query(int x){
        int res=-inf;
        for(int i=x;i>=1;i-=(i&(-i))) res=max(res,bit[i]);
        return res;
    }
}lt,rt;

int d[maxn],mx[maxn];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> U >> D >> S;M=S;
    for(int i=1;i<=N;i++){
        int t,l,m;cin >> t >> l >> m;
        F[t].push_back({l,m});
        T=max(T,t);M=max(M,l);
    }
    lt.init();rt.init();
    lt.update(S,U*S);
    rt.update(M-S+1,-D*S);
    int res=0;
    for(int i=1;i<=T;i++){
        if(F[i].empty()) continue;
        sort(F[i].begin(),F[i].end());
        int sz=(int)F[i].size();
        for(int j=0;j<sz;j++){
            d[j]=max(lt.query(F[i][j].fi)-U*F[i][j].fi,rt.query(M-F[i][j].fi+1)+D*F[i][j].fi);

            mx[j]=d[j];
        }
        int v1=-inf,v2=-inf;
        for(int j=0;j<sz;j++){
            if(!j) v1=d[j]+F[i][j].se,v2=F[i][j].se;
            else{
                v2=max(v2-(U+D)*(F[i][j].fi-F[i][j-1].fi),0LL)+F[i][j].se;
                v1=max(v1-U*(F[i][j].fi-F[i][j-1].fi)+F[i][j].se,d[j]+v2);
            }
            mx[j]=max(mx[j],v1);
        }
        v1=-inf,v2=-inf;
        for(int j=sz-1;j>=0;j--){
            if(j==sz-1) v1=d[j]+F[i][j].se,v2=F[i][j].se;
            else{
                v2=max(v2-(U+D)*(F[i][j+1].fi-F[i][j].fi),0LL)+F[i][j].se;
                v1=max(v1-D*(F[i][j+1].fi-F[i][j].fi)+F[i][j].se,d[j]+v2);
            }
            mx[j]=max(mx[j],v1);
        }
        for(int j=0;j<sz;j++){
            if(F[i][j].fi>S) res=max(res,mx[j]-D*(F[i][j].fi-S));
            else res=max(res,mx[j]-U*(S-F[i][j].fi));
            //cout << F[i][j].fi << ' ' << F[i][j].se << ' ' << d[j] << ' ' << mx[j] << '\n';
            lt.update(F[i][j].fi,mx[j]+U*F[i][j].fi);
            rt.update(M-F[i][j].fi+1,mx[j]-D*F[i][j].fi);
        }
    }
    cout << res << '\n';
}
