#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
#define pii pair<int,int>
#define fi first
#define se second
int n,h[maxn],sz=0;
vector<pii> com;
vector<vector<pii>> ans;
bool check(){
    for(int i=1;i<=n;i++){
        if(h[i]!=i) return true;
    }
    return false;
}
bool vis[maxn];
void solve(){
    for(int i=1;i<=n;i++) vis[i]=false;
    ans.push_back({});
    for(int i=1;i<=n;i++){
        if(h[i]==i || vis[i]) continue;
        vector<int> nxt;
        int u=i;
        do{
            vis[u]=true;
            nxt.push_back(u);u=h[u];

        }while(u!=i);
        if((int)nxt.size()==2) ans[sz].push_back({i,h[i]});
        else{
            int r=(int)nxt.size()-1,l=0;
            while(l<r-1){
                ans[sz].push_back({nxt[l+1],nxt[r]});
                l++;r--;
            }
        }
    }
    for(pii x:ans[sz]) swap(h[x.fi],h[x.se]);
    sz++;
}
signed main(){
    //freopen("FOT.INP","r",stdin);
    //freopen("FOT.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++){cin >> h[i];com.push_back({h[i],i});}
    sort(com.begin(),com.end());
    for(int i=0;i<n;i++) h[com[i].se]=i+1;
    while(check()) solve();
    cout << sz << '\n';
    for(int i=0;i<sz;i++){
        cout << (int)ans[i].size()*2 << '\n';
        for(pii x:ans[i]) cout << x.fi << ' ';
        reverse(ans[i].begin(),ans[i].end());
        for(pii x:ans[i]) cout << x.se << ' ';
        cout << '\n';
    }
}
