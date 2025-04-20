#include "towns.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=115;
#define pii pair<int,int>
#define fi first
#define se second

int d[maxn][maxn],b[maxn];

int get(int u,int v){
    if(u==v) return 0;
    if(d[u][v]) return d[u][v];
    return d[u][v]=d[v][u]=getDistance(u,v);
}

int hubDistance(int N, int sub) {
    memset(d,0,sizeof(d));
	pii a={0,0};
    for(int i=0;i<N;i++) a=max(a,{get(0,i),i});
    int D=0,R=1e6;
    for(int i=0;i<N;i++) D=max(D,get(a.se,i));
    map<int,vector<int>> mp;
    for(int i=0;i<N;i++){
        b[i]=(get(a.se,i)+get(0,i)-get(a.se,0))/2;
        int k=get(a.se,i)-b[i];
        mp[k].push_back(i);
        R=min(R,max(k,D-k));
    }
    int sl=0,sr=N;
    for(auto [k,x]:mp){
        sr-=(int)x.size();
        if(max(k,D-k)==R && sl<=N/2 && sr<=N/2){
            //cout << a.se << ' ' << k << '\n';
            vector<vector<int>> u,v;
            for(int i:x){
                if(!u.empty() && (int)u.back().size()>(int)v.back().size()){
                    if(get(u.back()[0],i)<b[u.back()[0]]+b[i]) u.back().push_back(i);
                    else v.back().push_back(i);
                }
                else{
                    u.push_back({i});
                    v.push_back({});
                }
            }
            int S=(int)u.back().size();
            for(int i=0;i<(int)u.size()-1;i++){
                if(get(u[i][0],u.back()[0])<b[u[i][0]]+b[u.back()[0]]) S+=(int)u[i].size();
                else{
                    for(int j:v[i]) if(get(j,u.back()[0])<b[j]+b[u.back()[0]]) S++;
                }
            }
            //cout << S << '\n';
            if(S<=N/2) R=-R;
        }
        sl+=(int)x.size();
    }

	return -R;
}
