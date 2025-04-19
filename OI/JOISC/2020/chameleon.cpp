#include "chameleon.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
vector<int> edge[maxn],lst[2];
bool vis[maxn];
int res[maxn],pos[maxn];
void dfs(int u,int d){
    vis[u]=true;lst[d].push_back(u);
    for(int v:edge[u]){
        if(!vis[v]) dfs(v,d^1);
    }
}
void Solve(int N) {
    for(int i=1;i<=2*N;i++){
        lst[0].clear();lst[1].clear();
        for(int j=1;j<i;j++) vis[j]=false;
        for(int j=1;j<i;j++){
            if(!vis[j]) dfs(j,0);
        }
        //cout << i << endl;
        for(int j=0;j<2;j++){
            //cout << i << ' ' << j << '\n';
            while(true){
                if(lst[j].empty()) break;
                lst[j].push_back(i);
                if(Query(lst[j])==(int)lst[j].size()) break;
                else lst[j].pop_back();
                int l=1,r=(int)lst[j].size();
                while(r>l){
                    int mid=(r+l-1)>>1;
                    vector<int> p;
                    for(int k=0;k<mid;k++) p.push_back(lst[j][k]);
                    p.push_back(i);
                    if(Query(p)!=(int)p.size()) r=mid;
                    else l=mid+1;
                }
                //cout << i << ' ' << j << ' ' << r << '\n';
                edge[lst[j][r-1]].push_back(i);
                edge[i].push_back(lst[j][r-1]);
                lst[j].erase(lst[j].begin()+r-1);
            }
        }
    }
    for(int i=1;i<=2*N;i++){
        if((int)edge[i].size()==1) res[i]=edge[i][0];
        else{
            int a=Query({i,edge[i][0],edge[i][1]});
            int b=Query({i,edge[i][0],edge[i][2]});
            int c=Query({i,edge[i][1],edge[i][2]});
            if(a==1) pos[i]=edge[i][2];
            else if(b==1) pos[i]=edge[i][1];
            else pos[i]=edge[i][0];
        }
    }
    for(int i=1;i<=2*N;i++){
        if((int)edge[i].size()==1) continue;
        for(int v:edge[i]){
            if(v==pos[i]) continue;
            if(pos[v]!=i) res[i]=v;
        }
    }
    for(int i=1;i<=2*N;i++){
        if(i<res[i]) Answer(i,res[i]);
    }
}