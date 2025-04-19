#include<bits/stdc++.h>
using namespace std;
#define maxn 300005
#define int long long
#define pii pair<int,int>
int bit[maxn],n,cnt=0;
vector<pii> x;
int query(int a){
    int res=0;
    for(int i=a;i>=1;i-=(i&(-i))) res+=bit[i];
    return res;
}
void update(int a){
    for(int i=a;i<=n;i+=(i&(-i))) bit[i]++;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++){
        int a;cin >> a;
        x.push_back({a,i});
    }
    sort(x.begin(),x.end());
    int ans=0;
    while(!x.empty()){
        pii p=x.back();x.pop_back();
        int sum=query(p.second);sum=min(sum,cnt-sum);
        vector<int> add={p.second};
        while(!x.empty() && x.back().first==p.first){
            int a=query(x.back().second);
            sum+=min(a,cnt-a);add.push_back(x.back().second);
            x.pop_back();
        }
        //cout << cnt << ' ' << sum << '\n';
        ans+=sum;cnt+=(int)add.size();
        for(int v:add) update(v);
    }
    cout << ans << '\n';
}
