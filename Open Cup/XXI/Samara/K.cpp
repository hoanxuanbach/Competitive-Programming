#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int maxn=200005;
pii p[maxn];
int n,m;
bool cmp(pii a,pii b){
    if(a.first<=a.second && b.first<=b.second) return a.first<b.first;
    else if(a.first<=a.second || b.first<=b.second) return a.first<=a.second;
    if(a.second!=b.second) return a.second>b.second;
    else return a.first>b.first;
}
bool solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){cin >> p[i].first >> p[i].second;p[i].second=min(p[i].second,m);}
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<=n;i++){
        //cout << p[i].first << ' ' << p[i].second << '\n';
        if(m<p[i].first) return false;
        m-=p[i].first-p[i].second;
    }
    return true;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t;cin >> t;
    while(t--){
        if(solve()) cout << "YES\n";
        else cout << "NO\n";
    }
}
