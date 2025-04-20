#include "shoes.h"
#include<bits/stdc++.h>
using namespace std;
namespace BIT{
    int n;
    vector<int> bit;
    void init(int N){
        n=N;bit.assign(n+1,0);
    }
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
};
long long count_swaps(std::vector<int> s) {
    int n=(int)s.size();
    BIT::init(n);
    vector<vector<vector<int>>> pos(2,vector<vector<int>>(n+1,vector<int>()));
    for(int i=n-1;i>=0;i--){
        pos[s[i]<0][abs(s[i])].push_back(i+1);
        BIT::update(i+1,1);
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        int t=(s[i-1]<0),x=abs(s[i-1]);
        if(pos[t][x].empty() || pos[t][x].back()!=i) continue;
        int p=pos[t^1][x].back();
        pos[t][x].pop_back();pos[t^1][x].pop_back();
        ans+=BIT::query(p)-t-1;
        BIT::update(i,-1);BIT::update(p,-1);
    }
    return ans;
}
