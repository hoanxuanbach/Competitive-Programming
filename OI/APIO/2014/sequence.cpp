#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 100005
#define maxk 205
#define pii pair<int,int>
const ll inf=LLONG_MAX;
int trace[maxn][maxk];
struct line{
    ll a,b,p;
    int id;
    bool operator<(line l){return a<l.a;}
    bool operator<(ll k){return p<k;}
};
struct cvht{
    line x[maxn];
    ll res[maxn];
    int pos=0,sz=0;
    ll div(ll a,ll b){
        return a/b-((a^b)<0 && a%b);
    }
    bool isect(line &l,line &y){
        if(l.a==y.a) l.p=(l.b>y.b)?inf:-inf;
        else l.p=div(y.b-l.b,l.a-y.a);
        return l.p>=y.p;
    }
    void add(line l){
        if(sz!=0) isect(x[sz],l);
        while(sz>=2 && x[sz-1].p>=x[sz].p){
            sz--;
            isect(x[sz],l);
        }
        x[++sz]=l;
    }
    ll query(ll &v,int &i,int &j){
        pos=lower_bound(x+1,x+sz+1,v)-x;
        trace[i][j]=x[pos].id;
        return x[pos].a*v+x[pos].b;
    }
}dp[2];
int n,k,t=0;
ll x[maxn];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    for(int i=1;i<=n;i++){cin >> x[i];x[i]+=x[i-1];}
    for(int i=1;i<=k;i++){
        t^=1;dp[t^1].sz=0;
        dp[t^1].add({x[i],dp[t^1].res[i]-x[i]*x[i],inf,i});
        for(int j=i+1;j<=n;j++){
            dp[t].res[j]=dp[t^1].query(x[j],j,i);
            dp[t^1].add({x[j],dp[t^1].res[j]-x[j]*x[j],inf,j});
        }
    }
    int c=n,d=k;
    cout << dp[t].res[n] << '\n';
    while(trace[c][d]!=0){
        cout << trace[c][d] << ' ';
        c=trace[c][d];d--;
    }
}
