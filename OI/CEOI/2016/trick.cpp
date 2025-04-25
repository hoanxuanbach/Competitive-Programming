#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define mpp make_pair
#define fi first
#define se second
const int maxn=2500005;
bool check[maxn];
int R;

void solve(){
    int n;cin >> n;
    int Mod=2*n+1;
    vector<pii> p={{0,1},{0,2*n},{2*n-1,n},{2,n},{n+1,4},{n+1,2*n-3}};
    if(n&1) for(int i=2;i<6;i++) swap(p[i].fi,p[i].se);
    for(int i=1;i<n;i++) p.push_back({i,Mod-i});
    for(int i=0;i<=2*n;i++) check[i]=false;
    if(R^3){
        int S=0;
        for(int i=1;i<=n;i++){
            int x;cin >> x;
            check[x]=true;
            S=(S+x)%Mod;
        }
        for(auto [x,y]:p){
            x=(S+x)%Mod;y=(S+y)%Mod;
            if(check[x] && check[y]){
                cout << x << ' ' << y << '\n';
                return;
            }
        }
    }
    else{
        int x1,y1,x2,y2,res=0;
        cin >> x1 >> y1 >> x2 >> y2;
        for(auto [x,y]:p){
            if((x1-x-y1+y)%Mod==0) res-=(x1-x);
            if((x2-x-y2+y)%Mod==0) res-=(x2-x);
        }
        cout << (res%Mod+Mod)%Mod << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test >> R;
    while(test--) solve();
}