#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const int maxn = 20005;
int n,m,k,p[maxn];
int rand_int(int l,int r){
    return l+(int)(rng()%(r-l+1));
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> k;
    vector<pair<int,int>> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i].first;
        a[i].second=i;
    }

    sort(a.begin(),a.end());
    for(int i=0;i<n;i++) p[a[i].second]=i;
    vector<vector<pair<int,int>>> res;

    for(int t=0;t<=(n-1)/(k-1);t++){
        bool check=false;
        vector<pair<int,int>> cur;
        int cnt=k;
        for(int i=0;i<n;i++){
            if(!cnt || p[i]==i) continue;
            check=true;
            vector<int> cycle;
            int u=i;
            do{
                cycle.push_back(u);
                u=p[u];
            }while(u!=i);

            int sz=(int)cycle.size();
            if(sz<=cnt){
                cnt-=sz;
                for(int x:cycle) cur.push_back({x,p[x]}),p[x]=x;
            }
            else{
                for(int j=0;j<cnt-1;j++) cur.push_back({cycle[j],cycle[j+1]});
                if(cnt>1){
                    p[cycle[0]]=p[cycle[cnt-1]];
                    cur.push_back({cycle[cnt-1],cycle[0]});
                    for(int j=0;j<cnt-1;j++){
                        p[cycle[j+1]]=cycle[j+1];
                    }
                }
                cnt=0;
            }
        }
        if(!check) break;
        res.push_back(cur);
    }
    cout << (int)res.size() << '\n';
    for(auto v:res){
        cout << (int)v.size() << ' ';
        for(auto [x,y]:v) cout << x+1 << ' ' << y+1 << ' ';
        cout << '\n';
    }
}
