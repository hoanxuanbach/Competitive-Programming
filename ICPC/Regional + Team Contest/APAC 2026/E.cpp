#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pii pair<int,int>
const int inf = 1e18;

const int B = 400;

void solve() {
    int n,m;cin >> n >> m;
    vector<int> s(n+1),d(n+1),p(n+1),pre(n+1);
    for(int i=1;i<=n-m+1;i++){
        cin >> s[i];
        if(i>1) d[i-1]=s[i]-s[i-1];
    }
    for(int i=m+1;i<=n;i++) p[i]=p[i-m]+d[i-m];
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+p[i];

    int q;cin >> q;

    vector<bool> unb(q);
    vector<int> res(q);
    vector<vector<pii>> qq(n+1);
    for(int i=0;i<q;i++){
        int l,r;cin >> l >> r;
        if(r-l+1>=m) qq[r].push_back({l,i}),res[i]=s[l];
        else unb[i]=true;
    }

    if(m>B){
        vector<int> val(n+1),total(n+1);
        auto update = [&](int x,int d){
            total[x/B]+=d-val[x];
            val[x]=d;
        };
        auto query = [&](int l,int r){
            int sum=0;
            for(int i=l;i<=r;i++){
                if(i%B==0 && i+B-1<=r) sum+=total[i/B],i+=B-1;
                else sum+=val[i];
            }
            return sum;
        };

        for(int r=1;r<=n;r++){
            for(int j=r;j>=1;j-=m) p[j]=max(p[j],p[r]),update(j,p[j]);
            for(auto [l,id]:qq[r]) res[id]+=query(l,l+m-1)-pre[l+m-1]+pre[l-1];
        }
    }
    else{

        int S=n/m+10;
        vector<vector<int>> g(m+1),lazy(m+1);
        for(int i=1;i<=m;i++) g[i].assign(S,-inf),lazy[i].assign(S,-inf);

        auto update = [&](int x,int val){
            int k=x%m;
            if(k==0) k+=m;

            int i=(x-k)/m;
            for(int j=i%B;j>=0;j--) g[k][i-j]=max(g[k][i-j],val);
            for(int j=0;j<i/B;j++) lazy[k][j]=max(lazy[k][j],val);
        };
        auto query = [&](int x){
            int k=x%m;
            if(k==0) k+=m;

            int i=(x-k)/m;
            return max(g[k][i],lazy[k][i/B]);
        };
        for(int r=1;r<=n;r++){
            update(r,p[r]);
            for(auto [l,id]:qq[r]){
                for(int i=l;i<=l+m-1;i++) res[id]+=query(i);
                res[id]-=(pre[l+m-1]-pre[l-1]);
            }
        }
    }

    for(int i=0;i<q;i++){
        if(unb[i]) cout << "unbounded\n";
        else{
            int k=res[i]/m;
            while(k*m<res[i]) k++;
            cout << k << '\n';
        }
    }
}

signed main() {
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int num_test = 1;
    //cin >> num_test;
    while (num_test--) {
        solve();
    }
}