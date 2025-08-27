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
const int inf = 1e18;
 
struct line{
    int a,b,p;
    bool operator<(line o){return a<o.a;}
    bool operator<(int o){return p<o;}
};
struct cvht{
    int pos=0;
    vector<line> x;
    int div(int a,int b){
        return a/b-((a^b)<0 && a%b);
    }
    void isect(line &y,line &l){
        if(y.a==l.a) y.p=(y.b>l.b)?inf:-inf;
        else y.p=div(y.b-l.b,l.a-y.a);
        return;
    }
    void add_line(line l){
        if(!x.empty()) isect(x.back(),l);
        while((int)x.size()>=2 && x[(int)x.size()-2].p>=x.back().p){
            x.pop_back();
            isect(x.back(),l);
        }
        x.push_back(l);
    }
    int query(int v){
        while(x[pos].p<v) pos++;
        return x[pos].a*v+x[pos].b;
    }
}cht[4*maxn];
int total[4*maxn],len[4*maxn];
 
int s[maxn],res[maxn];
void build(int l,int r,int id){
    cht[id].x.clear();
    cht[id].pos=0;
 
    len[id]=r-l+1;
    total[id]=0;
    for(int i=l;i<=r;i++) total[id]+=s[i],cht[id].add_line({i-l+1,-total[id],inf});
 
    if(l==r) return;
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
}
 
int lt[maxn],rt[maxn];
vector<int> f[maxn];
 
void query(int l,int r,int id,int tl,int tr,int x){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        f[x].push_back(id);
        return;
    }
    int mid=(l+r)>>1;
    query(l,mid,id<<1,tl,tr,x);query(mid+1,r,id<<1|1,tl,tr,x);
}
 
 
 
void cal(int n,vector<array<int,4>> qq){
 
    //cout << "cal\n";
    //for(int i=1;i<=n;i++) cout << s[i] << ' ';
    //cout << '\n';
 
    build(1,n,1);
    vector<pii> cur;
    for(int i=0;i<(int)qq.size();i++){
        //cout << "query " << qq[i][0] << ' ' << qq[i][1] << ' ' << qq[i][2] << ' ' << qq[i][3] << '\n';
        lt[i]=0,rt[i]=qq[i][2];f[i].clear();
        query(1,n,1,qq[i][0],qq[i][1],i);
        if(lt[i]<rt[i]) cur.push_back({(lt[i]+rt[i]+1)/2,i});
    }
    while(!cur.empty()){
        sort(cur.begin(),cur.end());
        for(int i=1;i<=4*n;i++) cht[i].pos=0;
        for(auto &[x,i]:cur){
            pii P={x-qq[i][2],x-qq[i][2]};
            for(int id:f[i]){
                P.second=max(P.second,P.first+cht[id].query(x));
                P.first+=x*len[id]-total[id];
            }
            if(P.second<=0) lt[i]=x;
            else rt[i]=x-1;
        }
        cur.clear();
        for(int i=0;i<(int)qq.size();i++) if(lt[i]<rt[i]) cur.push_back({(lt[i]+rt[i]+1)/2,i});
    }
 
    for(int i=0;i<(int)qq.size();i++) res[qq[i][3]]=lt[i];
}
 
int n,a[maxn];
 
void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    
    int q;cin >> q;
    vector<array<int,4>> qq[2];
    for(int i=1;i<=q;i++){
        int l,r;cin >> l >> r;
        int val=a[l++];r--;
        if(l>r) res[i]=val;
        else qq[l&1].push_back({l/2,(r-1)/2,val,i});
    }
 
    for(int i=0;i<=1;i++){
        for(int j=1;2*j+i<n;j++) s[j]=a[2*j+i]+a[2*j+i+1];
        cal((n-i-1)/2,qq[i]);
    }
 
    for(int i=1;i<=q;i++) cout << res[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
