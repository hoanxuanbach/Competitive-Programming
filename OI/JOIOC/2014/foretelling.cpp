#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 200005
#define pii pair<int,int>
int n,k,a[maxn],b[maxn],bit[2*maxn],t[maxn],f[maxn],cnt[maxn],ans;
pii p[maxn];
vector<pii> que[maxn],l[maxn];
vector<int> com;
int query(int x){
    if(x==0) return 0;
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
    return res;
}
void update(int x){
    for(int i=x;i<=n+k;i+=(i&(-i))) bit[i]++;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> a[i] >> b[i];
    for(int i=1;i<=k;i++){cin >> t[i];p[i]={t[i],i};com.push_back(t[i]);}
    sort(p+1,p+k+1);
    for(int i=1;i<=n;i++){
        int mn=min(a[i],b[i]),mx=max(a[i],b[i]);
        int pos=lower_bound(p+1,p+k+1,make_pair(mn,0LL))-p;
        que[pos].push_back({mx-1,i});com.push_back(mx);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    deque<pii> v;
    for(int i=k;i>=1;i--){
        while(!v.empty() && v.front().second<=p[i].second) v.pop_front();
        v.push_front(p[i]);
        for(pii x:que[i]){
            int pos=upper_bound(v.begin(),v.end(),make_pair(x.first,k))-v.begin()-1;
            if(pos>=0) f[x.second]=v[pos].second;
        }
    }
    for(int i=1;i<=n;i++) l[f[i]+1].push_back({i,max(a[i],b[i])});
    for(int i=k;i>=1;i--){
        int pos=lower_bound(com.begin(),com.end(),t[i])-com.begin()+1;
        update(pos);
        for(pii x:l[i]){
            int pos2=lower_bound(com.begin(),com.end(),x.second)-com.begin()+1;
            cnt[x.first]=k-i+1-query(pos2-1);
        }
    }
    for(int i=1;i<=n;i++){
        //cout << f[i] << ' ' << cnt[i] << '\n';
        if(f[i]==0){
            if(cnt[i]%2==0) ans+=a[i];
            else ans+=b[i];
        }
        else{
            if(cnt[i]%2==0) ans+=max(a[i],b[i]);
            else ans+=min(a[i],b[i]);
        }
    }
    cout << ans << '\n';
}
