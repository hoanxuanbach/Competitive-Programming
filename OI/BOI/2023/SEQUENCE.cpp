#include<bits/stdc++.h>
using namespace std;
const int maxn = 30005;
#define int long long
const int inf = 1e18;

int n,w[maxn];
vector<int> f[maxn];
map<vector<int>,int> mp;

int g(vector<int> x){
    if(x.empty()) return w[1]+w[2];
    if(mp.find(x)!=mp.end()) return mp[x];
    vector<int> c=x;
    int a=c.back();c.pop_back();

    int res=inf;
    for(int i:f[a]){
        int j=a/i;
        vector<int> nx=c;
        if(i>2) nx.push_back(i);
        if(j>2) nx.push_back(j);
        sort(nx.begin(),nx.end());
        nx.erase(unique(nx.begin(),nx.end()),nx.end());
        res=min(res,g(nx));
    }
    if(a>3) c.push_back(a-1);
    sort(c.begin(),c.end());
    c.erase(unique(c.begin(),c.end()),c.end());
    res=min(res,g(c));
    return mp[x]=res+w[a];
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> w[i];
    for(int i=2;i<=n;i++) for(int j=i*i;j<=n;j+=i) f[j].push_back(i);

    cout << w[1] << '\n';
    if(n>=2) cout << w[1]+w[2] << '\n';
    if(n<=2) return 0;
    for(int i=3;i<=n;i++) cout << g({i}) << '\n';
    cout << '\n';
}
