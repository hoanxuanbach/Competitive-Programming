#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 2e5+5;

void solve(){   
    int n;cin >> n;

    vector<int> d(n);
    vector<pii> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i].fi >> b[i].fi;
        a[i].se=b[i].se=i;
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    for(int i=0;i<n/2;i++){
        d[a[i].se]+=1;
        d[b[i].se]+=2;
    }
    vector<vector<int>> f(4);
    for(int i=0;i<n;i++){
        if(!f[d[i]^3].empty()){
            int x=f[d[i]^3].back();f[d[i]^3].pop_back();
            cout << x+1 << ' ' << i+1 << '\n';
        }
        else f[d[i]].push_back(i);
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}