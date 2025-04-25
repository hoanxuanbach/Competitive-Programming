#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int maxn = 2e5+5;
const int inf = 1e18;

int n,mA,mB,K,T,S;
set<int> A[maxn],B[maxn];
map<int,int> cA[maxn],cB[maxn];
int fA[maxn],fB[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> mA >> mB >> K;
    vector<piii> eA,eB;
    for(int i=0;i<mA;i++){
        int u,v,w;cin >> u >> v >> w;
        eA.push_back({w,{u,v}});
    }
    for(int i=0;i<mB;i++){
        int u,v,w;cin >> u >> v >> w;
        eB.push_back({w,{u,v}});
    }
    vector<piii> ne;
    sort(eB.begin(),eB.end());
    for(int i=1;i<=n;i++) B[i].insert(i),fB[i]=i;
    for(auto [w,p]:eB){
        auto [x,y]=p;
        x=fB[x],y=fB[y];
        if(x==y) continue;
        if((int)B[x].size()<(int)B[y].size()) swap(x,y);
        ne.push_back({w,{x,y}});
        for(int u:B[y]) B[x].insert(u),fB[u]=x;
    }
    eB=ne;
    int lst=inf,res=inf;
    for(int i=1;i<=n;i++) A[i].insert(i),fA[i]=i;
    for(int i=1;i<=n;i++){
        cB[fB[i]][fA[i]]++,cA[fA[i]][fB[i]]++;
        if(fB[i]==i) T+=(int)B[i].size()*((int)B[i].size()-1)/2;
    }
    sort(eA.begin(),eA.end());
    for(int i=0;i<=(int)eA.size();i++){
        if(i){
            auto [w,p]=eA[i-1];
            auto [x,y]=p;
            x=fA[x],y=fA[y];
            if(x==y) continue;
            if((int)A[x].size()<(int)A[y].size()) swap(x,y);
            T+=(int)A[x].size()*(int)A[y].size();
            for(int u:A[y]){
                cB[fB[u]][y]--;
                A[x].insert(u),fA[u]=x;
                cB[fB[u]][x]++;
            }
            for(auto [u,cnt]:cA[y]){
                S+=cnt*cA[x][u];
                cA[x][u]+=cnt;
            }
        }
        int val=(i?eA[i-1].fi:0);
        //cout << i << ' ' << lst << ' ' << T << ' ' << S << '\n';
        while(!ne.empty() && T-S>=K){
            lst=ne.back().fi;
            auto [x,y]=ne.back().se;
            ne.pop_back();
            for(int u:B[y]){
                cA[fA[u]][x]--;
                B[x].erase(u),fB[u]=y;
                cA[fA[u]][y]++;
                cB[y][fA[u]]++;
            }
            T-=(int)B[x].size()*(int)B[y].size();
            for(auto [u,cnt]:cB[y]){
                cB[x][u]-=cnt;
                S-=cnt*cB[x][u];
            }
            //cout << i << ' ' << lst << ' ' << T << ' ' << S << '\n';
        }
        val=(val+((T-S)>=K?0:lst));
        res=min(res,val);
    }
    cout << (res==inf?-1:res) << '\n';
}
