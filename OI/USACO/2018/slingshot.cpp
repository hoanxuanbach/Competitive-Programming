#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 400005
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
const int inf=LLONG_MAX;
struct sling{
    int x,y,t;
    bool operator<(sling o){return x<o.x;}
};
struct query{
    int a,b,id;
    bool operator<(query o){return a<o.a;}
};
int ans[maxn],bitd[maxn],bitu[maxn],n,m,sz;
vector<int> p;
vector<sling> s;
vector<query> q;
void updateu(int x,int val){
    for(int i=x;i<=sz;i+=(i&(-i))) bitu[i]=min(bitu[i],val);
}
void updated(int x,int val){
    for(int i=x;i<=sz;i+=(i&(-i))) bitd[i]=min(bitd[i],val);
}
int queryu(int x){
    int res=inf;
    for(int i=x;i>=1;i-=(i&(-i))) res=min(res,bitu[i]);
    return res;
}
int queryd(int x){
    int res=inf;
    for(int i=x;i>=1;i-=(i&(-i))) res=min(res,bitd[i]);
    return res;
}
signed main(){
    freopen("slingshot.in","r",stdin);
    freopen("slingshot.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        int x,y,t;cin >> x >> y >> t;
        p.push_back(x);p.push_back(y);
        s.push_back({x,y,t});
    }
    for(int i=1;i<=m;i++){
        int a,b;cin >> a >> b;ans[i]=abs(a-b);
        p.push_back(a);p.push_back(b);
        q.push_back({a,b,i});
    }
    sort(p.begin(),p.end());
    p.erase(unique(p.begin(),p.end()),p.end());
    sz=(int)p.size();
    for(auto &v:s){
        v.x=lower_bound(p.begin(),p.end(),v.x)-p.begin();
        v.y=lower_bound(p.begin(),p.end(),v.y)-p.begin();
    }
    for(auto &v:q){
        v.a=lower_bound(p.begin(),p.end(),v.a)-p.begin();
        v.b=lower_bound(p.begin(),p.end(),v.b)-p.begin();
    }
    sort(s.begin(),s.end());sort(q.begin(),q.end());
    for(int i=1;i<=sz;i++) bitu[i]=bitd[i]=inf;
    int l=0;
    for(auto v:q){
        while(l<n && s[l].x<=v.a){
            updated(s[l].y+1,-p[s[l].x]-p[s[l].y]+s[l].t);
            updateu(sz-s[l].y,-p[s[l].x]+s[l].t+p[s[l].y]);
            l++;
        }
        int resd=queryd(v.b+1);
        if(resd!=inf) ans[v.id]=min(ans[v.id],p[v.a]+p[v.b]+resd);
        int resu=queryu(sz-v.b);
        if(resu!=inf) ans[v.id]=min(ans[v.id],p[v.a]+resu-p[v.b]);
    }
    reverse(s.begin(),s.end());reverse(q.begin(),q.end());
    for(int i=1;i<=sz;i++) bitu[i]=bitd[i]=inf;
    l=0;
    for(auto v:q){
        while(l<n && s[l].x>=v.a){
            updated(s[l].y+1,p[s[l].x]-p[s[l].y]+s[l].t);
            updateu(sz-s[l].y,p[s[l].x]+s[l].t+p[s[l].y]);
            l++;
        }
        int resd=queryd(v.b+1);
        if(resd!=inf) ans[v.id]=min(ans[v.id],resd-p[v.a]+p[v.b]);
        int resu=queryu(sz-v.b);
        if(resu!=inf) ans[v.id]=min(ans[v.id],resu-p[v.a]-p[v.b]);
    }
    for(int i=1;i<=m;i++) cout << ans[i] << '\n';
}
