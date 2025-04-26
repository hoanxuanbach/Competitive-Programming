#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5+5;
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
vector<ll> pos[maxn];
map<ll,ll> mp;

long long findMinClicks(int M, int R, std::vector <std::pair<int, int> > P) {
    int N=(int)P.size();R*=2;
    for(auto x:P) pos[x.fi].push_back(2*x.se);
    ll total=0,pre=0,add=0;
    for(int i=0;i<M;i++){
        sort(pos[i].begin(),pos[i].end());
        for(int j=0;j<(int)pos[i].size()-1;j++){
            int p=(pos[i][j]+pos[i][j+1])/2;
            mp[pos[i][j]]+=2;mp[p]-=2;
        }
        mp[pos[i].back()]+=2;
        ll p=(pos[i].back()+1LL*R+pos[i][0])/2;

        mp[p%R]-=2;
        if(p<R){
            add--;
            total+=pos[i][0];
        }
        else{
            add++;
            total+=R-pos[i].back();
        }
    }
    ll res=total;
    for(auto [p,x]:mp){
        total+=(p-pre)*add;
        res=min(res,total);
        add+=x;pre=p;
    }
    return res/2;
}
