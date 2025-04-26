#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define pii pair<int,int>
int n,p[maxn],bit[maxn];
void update(int x,int val){
    for(int i=x;i<=n;i+=(i&(-i))) bit[i]=max(bit[i],val);
}
int query(int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res=max(res,bit[i]);
    return res;
}
signed main(){
    freopen("nocross.in","r",stdin);
    freopen("nocross.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++){int a;cin >> a;p[a]=i;}
    for(int i=1;i<=n;i++){
        int a;cin >> a;
        vector<pii> dp;
        for(int j=max(a-4,1);j<=min(a+4,n);j++) dp.push_back({p[j],query(p[j]-1)+1});
        for(pii v:dp) update(v.first,v.second);
    }
    cout << query(n) << '\n';
}
