#include<bits/stdc++.h>
using namespace std; 
#define ll long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int maxn = 1e5+5;
const int MB = 350;
const int B = 340;

int n,p[maxn];
int cnt[maxn][MB];

struct Block{
    int L,R;
    vector<pii> P;
    int f[maxn],ss[maxn];
    int C[MB][MB];

    void build(){
        for(int i=L;i<=R;i++) P.push_back({p[i],i}),f[p[i]]++;
        sort(P.begin(),P.end());
        for(int i=1;i<=n;i++) f[i]+=f[i-1],ss[i]=f[i];
        
        for(int i=L;i<=R;i++){
            if(i>L){
                for(int j=0;j<=f[n];j++) cnt[i][j]=cnt[i-1][j];
            }
            for(int j=f[p[i]];j<=f[n];j++) cnt[i][j]++;
        }

        for(int i=L;i<=R;i++) for(int j=L;j<i;j++){
            if(p[j]<p[i]) C[f[p[j]]][f[p[i]]]++;
        }
        for(int i=R-L+1;i>=1;i--) for(int j=i+1;j<=R-L+1;j++) C[i][j]+=C[i+1][j]+C[i][j-1]-C[i+1][j-1];
    }

}S[MB];
int T[MB][MB][MB];

void init(){
    int sz=(n-1)/B;
    for(int i=0;i<=sz;i++){
        S[i].L=i*B;S[i].R=min((i+1)*B,n)-1;
        S[i].build();
        if(i){
            for(int j=0;j<=n;j++) S[i].ss[j]+=S[i-1].ss[j];
        }
        for(int j=0;j<i;j++){
            for(int k=S[i].L;k<=S[i].R;k++) T[i][j][S[i].f[p[k]]]+=S[j].f[p[k]];
            for(int k=1;k<=S[i].f[n];k++) T[i][j][k]+=T[i][j][k-1];
            if(j){
                for(int k=1;k<=S[i].f[n];k++) T[i][j][k]+=T[i][j-1][k];
            }
        }
    }
}

ll G(int l,int r,int x,int y){
    ll res=0;
    int id=l/B;
    for(int i=l;i<=r;i++){
        if(x<p[i] && p[i]<=y){
            res+=cnt[i][S[id].f[p[i]]]-cnt[i][S[id].f[x]]-1;
            if(l!=S[id].L) res-=(cnt[l-1][S[id].f[p[i]]]-cnt[l-1][S[id].f[x]]);
        }
    }
    return res;
}

int cal_rec(int x,int y,int u,int v){
    return S[u].ss[v]-S[x].ss[v]-S[u].ss[y]+S[x].ss[y];
}

ll cal_merge(vector<int> &a,vector<int> &b){
    ll res=0;
    int i=0,j=0,sa=(int)a.size(),sb=(int)b.size();
    while(i<sa && j<sb){
        if(a[i]<b[j]) i++,res+=sb-j;
        else j++;
    }
    return res;
}

ll F(int l,int r,int x,int y){
    int lid=l/B,rid=r/B;

    ll res=G(l,S[lid].R,x,y)+G(S[rid].L,r,x,y);

    vector<int> lt,rt;
    for(auto t:S[lid].P){
        if(t.fi>x && t.fi<=y && t.se>=l){
            lt.push_back(t.fi);
            res+=cal_rec(lid,t.fi,rid-1,y);
        }
    }
    for(auto t:S[rid].P){
        if(t.fi>x && t.fi<=y && t.se<=r){
            rt.push_back(t.fi);
            res+=cal_rec(lid,x,rid-1,t.fi);
        }
    }
    res+=cal_merge(lt,rt);rid--;

    ll num=0;
    for(int i=lid+1;i<=rid;i++){
        res+=S[i].C[S[i].f[x]+1][S[i].f[y]];
        res+=T[i][i-1][S[i].f[y]]-T[i][lid][S[i].f[y]]-T[i][i-1][S[i].f[x]]+T[i][lid][S[i].f[x]];
        res-=num*(S[i].f[y]-S[i].f[x]);
        num+=S[i].f[x];
    }
    return res;
}

void solve(){   
    int q;cin >> n >> q;
    for(int i=0;i<n;i++) cin >> p[i];
    init();
    for(int i=0;i<q;i++){
        int l,r,x,y;cin >> l >> r >> x >> y;
        l--;r--;x--;
        if(l/B != r/B) cout << F(l,r,x,y) << '\n';
        else cout << G(l,r,x,y) << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}