#include "islands.h"
#include<bits/stdc++.h>
using namespace std;

std::variant<bool, std::vector<int>> find_journey(
    int N, int M, std::vector<int> U, std::vector<int> V) {
    vector<vector<int>> e(N),re(N);
    vector<int> d(N);
    for(int i=0;i<M;i++){
        d[U[i]]++;
        e[U[i]].push_back(i);
        re[V[i]].push_back(U[i]);
    }

    int x=0;
    vector<int> path;

    queue<int> q;
    for(int i=0;i<N;i++) if(!d[i]) q.push(i);
    while(true){
        if(!q.empty()){
            int u=q.front();q.pop();e[u].clear();
            for(int v:re[u]) if(!(--d[v])) q.push(v);
        }
        else{
            vector<int> ne;
            for(int id:e[x]) if(d[V[id]]>0) ne.push_back(id);
            e[x]=ne;
            if(ne.empty()) return false;
            else if((int)ne.size()==1){
                path.push_back(ne[0]);
                q.push(x);d[x]=0;x=V[ne[0]];
            }
            else break;
        }
    }

    for(int i=0;i<N;i++){
        vector<int> ne;
        for(int id:e[i]) if(d[V[id]]>0) ne.push_back(id);
        e[i]=ne;
    }

    vector<vector<int>> c(2);
    vector<int> s(N);s[x]=3;
    function<void(int,int)> dfs = [&](int id,int t){
        int u=V[id];c[t].push_back(id);
        if(s[u]) return;
        s[u]=t+1;dfs(e[u][0],t);
    };
    //cout << e[x][0] << ' ' << e[x][1] << '\n';
    dfs(e[x][0],0);dfs(e[x][1],1);

    vector<int> res;
    auto add = [&](vector<int> p,int rev){
        if(rev) reverse(p.begin(),p.end());
        res.insert(res.end(),p.begin(),p.end());
    };
    add(path,0);
    int a=V[c[0].back()],b=V[c[1].back()];
    if(s[b]==1){
        vector<int> p0,c0;
        for(int id:c[0]){
            if(U[id]==a || a==-1) a=-1,c0.push_back(id);
            else p0.push_back(id);
        }
        add(p0,0);add(c0,0);add(p0,1);
        for(int i=0;i<(int)c0.size();i++){
            if(U[c0[i]]==b){
                rotate(c0.begin(),c0.begin()+i,c0.end());
                break;
            }
        }
        vector<int> p1=c[1];
        for(int id:p0) if(U[id]==b || b==-1) b=-1,p1.push_back(id);
        add(p1,0);add(c0,1);add(p1,1);
    }
    else{

        vector<int> p0,c0;
        for(int id:c[0]){
            if(U[id]==a || a==-1) a=-1,c0.push_back(id);
            else p0.push_back(id);
        }
        vector<int> p1,c1;
        for(int id:c[1]){
            if(U[id]==b || b==-1) b=-1,c1.push_back(id);
            else p1.push_back(id);
        }
        add(p0,0);add(c0,0);add(p0,1);
        add(p1,0);add(c1,0);add(p1,1);
        add(p0,0);add(c0,1);add(p0,1);
        add(p1,0);add(c1,1);add(p1,1);
    }
    add(path,1);
    return res;
}
