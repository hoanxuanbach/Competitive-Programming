#include "rainbow.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 2e5+5;

int R,C;

struct BIT{
    vector<int> com[maxn],pre[maxn];
    BIT(){}
    void update(int x,int y){
        for(int i=x;i<=R;i+=(i&(-i))) com[i].push_back(y);
    }
    void build(int x){
        sort(com[x].begin(),com[x].end());
        vector<int> cur=com[x];com[x].clear();
        for(int y:cur){
            if(com[x].empty() || com[x].back()!=y){
                com[x].push_back(y);
                pre[x].push_back(1);
            }
            else pre[x].back()++;
        }
        for(int i=1;i<(int)com[x].size();i++) pre[x][i]+=pre[x][i-1];
    }
    void init(vector<pii> &A){
        sort(A.begin(),A.end());
        A.erase(unique(A.begin(),A.end()),A.end());
        for(auto [x,y]:A) update(x,y);
        for(int i=1;i<=R;i++) build(i);
    }
    int query(int x,int y){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))){
            int pos=upper_bound(com[i].begin(),com[i].end(),y)-com[i].begin()-1;
            res+=(pos<0?0:pre[i][pos]);
        }
        return res;
    }
    int get(int sx,int sy,int tx,int ty){
        return query(tx,ty)-query(tx,sy-1)-query(sx-1,ty)+query(sx-1,sy-1);
    }
}g,p,cc,rw;

void init(int _R, int _C, int x, int y, int M, char *S) {
    vector<pii> row,col,G,P;
    R=_R+1;C=_C+1;
    for(int i=0;i<=M;i++){
        G.push_back({x,y});
        for(int a=0;a<=1;a++) for(int b=0;b<=1;b++){
            P.push_back({x+a,y+b});
            if(!b) row.push_back({x+a,y+b});
            if(!a) col.push_back({x+a,y+b});
        }
        //cout << x << ' ' << y << '\n';
        if(i==M) break;
        if(S[i]=='N') x--;
        else if(S[i]=='S') x++;
        else if(S[i]=='W') y--;
        else y++;
    }
    g.init(G);p.init(P);
    rw.init(row);cc.init(col);
}

int colour(int ar, int ac, int br, int bc) {
    int V=p.get(ar+1,ac+1,br,bc);
    int E=rw.get(ar+1,ac,br,bc)+cc.get(ar,ac+1,br,bc);
    int total=g.get(ar,ac,br,bc),mid=0;
    if(ar+2<=br && ac+2<=bc) mid=g.get(ar+1,ac+1,br-1,bc-1);
    int CC=1;
    if(V>=1 && total==mid) CC++;
    //cout << E << ' ' << V << ' ' << CC << ' ' << total << '\n';
    return E-V+CC-total;
 }

