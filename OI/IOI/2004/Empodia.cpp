#include<bits/stdc++.h>
using namespace std;
const int maxn = 1100005;
int n,a[maxn],l[maxn],r[maxn],p[maxn];

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
    v.clear();
    vector<pair<int,int>> P;
    for(int i=1;i<=n;i++) P.push_back({a[i]-i+n,i});
    sort(P.begin(),P.end());

    int lst=-1;
    for(auto [k,i]:P){
        if(k!=lst) v.clear();
        while(!v.empty() && r[v.back()]<=i) v.pop_back();
        int mx=0;
        if(!v.empty()) mx=v.back();
        if(mx>l[i]) p[i]=mx;
        v.push_back(i);
        lst=k;
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
