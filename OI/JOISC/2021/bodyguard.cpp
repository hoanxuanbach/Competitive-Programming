#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int inf = 1e9;
const int maxn = 2805;
const int maxq = 3e6+5;

int N,Q;
int X[maxq],Y[maxq],U[maxn],V[maxn],W[maxn];
int ans[maxq];

int sx,sy;
vector<int> cx,cy;
vector<int> f[2*maxn][2*maxn];
int du[2*maxn][2*maxn],dr[2*maxn][2*maxn],dp[2*maxn][2*maxn];

struct line{
    int a,b,p=INF;
    line(int a=0,int b=0):a(a),b(b){}
    bool operator<(line o){return p<o.p;}
    bool operator<(int k){return p<k;}
};

vector<line> cht;

int fdiv(int a,int b){
    return a/b-((a^b)<0 && (a%b));
}

void isect(line &y,line l){
    if(y.a==l.a) y.p=(y.b>l.b?INF:-INF);
    else y.p=fdiv(y.b-l.b,l.a-y.a);
}

void add(int a,int b){
    line l=line(-a,b);
    while(!cht.empty() && cht.back().a>=l.a) cht.pop_back();
    if(!cht.empty()) isect(cht.back(),l);
    while((int)cht.size()>=2 && cht.end()[-2].p>=cht.back().p){
        cht.pop_back();
        isect(cht.back(),l);
    }
    cht.push_back(l);
}
int query(int x){
    x=-x;
    auto it=lower_bound(cht.begin(),cht.end(),x);
    return x*it->a+it->b;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> Q;
    cx.push_back(-inf);
    cy.push_back(-inf);
    for(int i=1;i<=N;i++){
        int t,a,b;cin >> t >> a >> b >> W[i];W[i]/=2;
        X[i]=t-a,Y[i]=t+a,U[i]=t+abs(a-b)-b,V[i]=t+abs(a-b)+b;
        cx.push_back(X[i]);cx.push_back(U[i]);
        cy.push_back(Y[i]);cy.push_back(V[i]);
    }
    sort(cx.begin(),cx.end());
    cx.erase(unique(cx.begin(),cx.end()),cx.end());
    sort(cy.begin(),cy.end());
    cy.erase(unique(cy.begin(),cy.end()),cy.end());
    sx=(int)cx.size();sy=(int)cy.size();
    cx.push_back(3*inf);cy.push_back(3*inf);

    for(int i=1;i<=N;i++){
        X[i]=lower_bound(cx.begin(),cx.end(),X[i])-cx.begin();
        Y[i]=lower_bound(cy.begin(),cy.end(),Y[i])-cy.begin();
        U[i]=lower_bound(cx.begin(),cx.end(),U[i])-cx.begin();
        V[i]=lower_bound(cy.begin(),cy.end(),V[i])-cy.begin();
        if(X[i]==U[i]) for(int j=Y[i];j<V[i];j++) du[X[i]][j]=max(du[X[i]][j],W[i]);
        else for(int j=X[i];j<U[i];j++) dr[j][Y[i]]=max(dr[j][Y[i]],W[i]);
    }
    for(int i=sx-1;i>=0;i--) for(int j=sy-1;j>=0;j--){
        dp[i][j]=max(dp[i+1][j]+dr[i][j]*(cx[i+1]-cx[i]),dp[i][j+1]+du[i][j]*(cy[j+1]-cy[j]));
        //cout << i << ' ' << j << ' ' << du[i][j] << ' ' << dr[i][j] << ' ' << dp[i][j] << '\n';
    }
    for(int i=1;i<=Q;i++){
        int x,y;cin >> x >> y;
        X[i]=x-y,Y[i]=x+y;
        x=lower_bound(cx.begin(),cx.end(),X[i])-cx.begin();
        y=lower_bound(cy.begin(),cy.end(),Y[i])-cy.begin();
        f[x][y].push_back(i);
    }
    for(int i=1;i<=sx;i++){
        cht.clear();
        for(int j=sy;j>=1;j--){
            add(dr[i-1][j],dp[i][j]);
            for(int id:f[i][j]) ans[id]=max(ans[id],query(cx[i]-X[id]));
        }
    }
    for(int j=1;j<=sy;j++){
        cht.clear();
        for(int i=sx;i>=1;i--){
            add(du[i][j-1],dp[i][j]);
            for(int id:f[i][j]) ans[id]=max(ans[id],query(cy[j]-Y[id]));
        }
    }
    for(int i=1;i<=Q;i++) cout << ans[i] << '\n';
}


