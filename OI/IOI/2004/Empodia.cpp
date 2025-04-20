#include<bits/stdc++.h>
using namespace std;
const int maxn = 2000005;
vector<int> pos[2*maxn],dd[maxn];
int n,a[maxn],l[maxn],r[maxn],p[maxn];
bool del[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    vector<int> v;
    for(int i=1;i<=n;i++){
        while(!v.empty() && a[v.back()]<a[i]) v.pop_back();
        l[i]=(v.empty()?0:v.back());
        v.push_back(i);
        //cout << l[i] << ' ';
    }
    //cout << '\n';
    v.clear();
    for(int i=n;i>=1;i--){
        while(!v.empty() && a[v.back()]>a[i]) v.pop_back();
        r[i]=(v.empty()?n+1:v.back());
        v.push_back(i);
        //cout << r[i] << ' ';
    }
    //cout << '\n';
    for(int i=1;i<=n;i++){
        for(int x:dd[i]) del[x]=true;
        dd[r[i]].push_back(i);
        int k=a[i]-i+n;
        while(!pos[k].empty() && del[pos[k].back()]) pos[k].pop_back();
        int mx=0;
        if(!pos[k].empty()) mx=pos[k].back();
        if(mx>l[i]) p[i]=mx;
        pos[k].push_back(i);
    }
    v.clear();
    vector<pair<int,int>> ans;
    for(int i=1;i<=n;i++){
        if(!p[i]) continue;
        bool check=false;
        while(!v.empty() && p[i]<=p[v.back()]) check=true,v.pop_back();
        v.push_back(i);
        if(!check) ans.push_back({p[i],i});
    }
    cout << (int)ans.size() << '\n';
    for(auto x:ans) cout << x.first << ' ' << x.second << '\n';
}
