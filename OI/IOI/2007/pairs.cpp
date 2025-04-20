#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
int B,N,D,M;

namespace B1{
    void solve(){
        vector<int> X(N);
        for(int i=0;i<N;i++) cin >> X[i];
        sort(X.begin(),X.end());
        int p=0;
        long long total=0;
        for(int i=0;i<N;i++){
            while(p<N && X[i]-X[p]>D) p++;
            total+=i-p;
        }
        cout << total << '\n';
    }
}
namespace B2{
    const int maxn = 150005;
    int bit[maxn];
    void update(int x,int val){
        for(int i=x;i<=2*M;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }

    void solve(){
        vector<pii> P(N);
        for(int i=0;i<N;i++){
            cin >> P[i].fi >> P[i].se;
            P[i]={P[i].fi+P[i].se,P[i].fi-P[i].se+M};
        }
        sort(P.begin(),P.end());
        int p=0;
        long long total=0;
        for(int i=0;i<N;i++){
            while(p<N && P[i].fi-P[p].fi>D) update(P[p++].se,-1);
            int l=max(1,P[i].se-D),r=min(2*M,P[i].se+D);
            total+=query(r)-query(l-1);
            update(P[i].se,1);
        }
        cout << total << '\n';
    }
}
namespace B3{
    const int maxn = 155;
    vector<pii> p[maxn];
    int cnt[maxn][maxn];

    void solve(){
        for(int i=0;i<N;i++){
            int x,y,z;cin >> x >> y >> z;
            p[x].push_back({y+z,y-z+M});
        }
        long long total=0;
        for(int i=1;i<=M;i++){
            for(int a=1;a<=2*M;a++) for(int b=1;b<=2*M;b++) cnt[a][b]=0;
            for(auto [x,y]:p[i]) cnt[x][y]++;
            for(int a=1;a<=2*M;a++) for(int b=1;b<=2*M;b++) cnt[a][b]+=cnt[a-1][b]+cnt[a][b-1]-cnt[a-1][b-1];
            for(int j=i;j<=M;j++){
                int d=D-(j-i);
                if(d<0) continue;
                long long add=0;
                for(auto [x,y]:p[j]){
                    int u=min(2*M,x+d),v=min(2*M,y+d);
                    x=max(1,x-d);y=max(1,y-d);
                    add+=cnt[u][v]-cnt[x-1][v]-cnt[u][y-1]+cnt[x-1][y-1];
                }
                if(j==i) add=(add-(int)p[i].size())/2;
                total+=add;
            }
        }
        cout << total << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> B >> N >> D >> M;
    if(B==1) B1::solve();
    else if(B==2) B2::solve();
    else B3::solve();
}
