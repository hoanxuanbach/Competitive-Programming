#include "highest.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5+5;
const int LG = 20;

int lg2[maxn];
pair<int,int> W[maxn][LG],V[maxn][LG],S[maxn][LG];



vector<int> solve(vector<int> &cV, vector<int> &cW, vector<pair<int, int>> &queries) {
    int n=(int)cV.size(),q=(int)queries.size();
    for(int i=2;i<=n;i++) lg2[i]=lg2[i/2]+1;
    for(int i=0;i<n;i++){
        V[i][0]={min(i+cV[i],n-1),i};
        W[i][0]={min(i+cW[i],n-1),i};
        S[i][0].first=min(i+cV[i],n-1);
        S[i][0].second=i;
        //cout << "S " << i << ' ' << S[i][0].first << ' ' << S[i][0].second << endl;
    }
    for(int j=1;j<LG;j++) for(int i=0;i<=n-(1<<j);i++){
        V[i][j]=max(V[i][j-1],V[i+(1<<(j-1))][j-1]);
        W[i][j]=max(W[i][j-1],W[i+(1<<(j-1))][j-1]);
    }
    auto getV = [&](int l,int r){
        int k=lg2[r-l+1];
        return max(V[l][k],V[r-(1<<k)+1][k]).second;
    };
    auto getW = [&](int l,int r){
        int k=lg2[r-l+1];
        return max(W[l][k],W[r-(1<<k)+1][k]).second;
    };
    auto nxt = [&](int i,int x,int y,int j){
        int a=getV(i,x),b=getW(i,x);
        //if(t) cout << "nxt " << i << ' ' << x << ' ' << y << ' ' << a << ' ' << b << endl;
        int nx=max({x,S[a][j].first,S[b][j].first}),ny=max({y,S[a][j].second,S[b][j].second});
        a=getW(i,y);
        //if(t) cout << a << endl;
        ny=max(ny,S[a][j].first);
        a=min(a+cW[a],n-1);nx=max(nx,a);
        b=getW(i,a);a=getV(i,a);
        nx=max(nx,max(S[a][j].second,S[b][j].second));
        return pair<int,int>{nx,ny};
    };
    for(int j=1;j<LG;j++) for(int i=0;i<n;i++){
        int x=S[i][j-1].first,y=S[i][j-1].second;
        S[i][j]=nxt(i,x,y,j-1);
        //cout << "val " << i << ' ' << j << ' ' << x << ' ' << y << ' ' << S[i][j].first << ' ' << S[i][j].second << endl;
    }

    vector<int> res(q);
    for(int i=0;i<q;i++){
        auto [s,t]=queries[i];
        if(s==t) continue;
        int x=min(s+cV[s],n-1),y=s;
        res[i]++;
        if(x>=t) continue;
        for(int j=LG-1;j>=0;j--){
            auto [nx,ny]=nxt(s,x,y,j);
            if(nx<t) res[i]+=(1<<j),x=nx,y=ny;
            //cout << j << ' ' << x << ' ' << y << '\n';
        }
        res[i]++;
    }
    return res;
}
