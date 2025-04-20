#include "rect.h"
#include<bits/stdc++.h>
using namespace std;
const int maxl=12;
struct BIT{
    int n;
    vector<int> bit;
    BIT(int N):n(N){
        bit.assign(n+1,0);
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
struct range{
    int id,up,down;
    range(int _id,int _up,int _down):id(_id),up(_up),down(_down){}
};
/*
6 5
4 8 7 5 6
7 4 10 3 5
9 7 20 14 2
9 14 7 3 6
5 7 5 2 7
4 5 13 5 6
*/
long long count_rectangles(std::vector<std::vector<int> > a) {
    int n=(int)a.size(),m=(int)a[0].size();
    vector<vector<int>> down(n,vector<int>(m,0)),up(n,vector<int>(m,0));
    for(int i=0;i<m;i++){
        vector<int> v={0};
        for(int j=1;j<n;j++){
            while(!v.empty() && a[j][i]>a[v.back()][i]) v.pop_back();
            if(v.empty()) up[j-1][i]=0;
            else up[j-1][i]=v.back()+1;
            v.push_back(j);
        }
        v={n-1};
        for(int j=n-2;j>=0;j--){
            while(!v.empty() && a[j][i]>a[v.back()][i]) v.pop_back();
            if(v.empty()) down[j+1][i]=n-1;
            else down[j+1][i]=v.back()-1;
            v.push_back(j);
        }
    }
	vector<vector<vector<range>>> pos(m,vector<vector<range>>(m,vector<range>()));
    for(int i=1;i<n-1;i++){
        vector<int> l(m),r(m),upl(m),upr(m),downl(m),downr(m),v;
        for(int j=0;j<m;j++){
            downl[j]=down[i][j];upl[j]=up[i][j];
            while(!v.empty() && a[i][v.back()]<=a[i][j]){
                downl[j]=min(downl[j],downl[v.back()]);
                upl[j]=max(upl[j],upl[v.back()]);
                v.pop_back();
            }
            if(!v.empty()) l[j]=v.back();
            else l[j]=-1;
            v.push_back(j);
        }
        v.clear();
        for(int j=m-1;j>=0;j--){
            downr[j]=down[i][j];upr[j]=up[i][j];
            while(!v.empty() && a[i][v.back()]<=a[i][j]){
                downr[j]=min(downr[j],downr[v.back()]);
                upr[j]=max(upr[j],upr[v.back()]);
                v.pop_back();
            }
            if(!v.empty()) r[j]=v.back();
            else r[j]=m;
            v.push_back(j);
        }
        for(int j=0;j<m;j++){
            if(l[j]>=0 && r[j]<m){
                int lt=l[j]+1,rt=r[j]-1;
                if(pos[lt][rt].empty() || pos[lt][rt].back().id!=i) pos[lt][rt].push_back(range(i,max(upl[j],upr[j]),min(downl[j],downr[j])));
            }
        }
    }

    /*
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cout << down[i][j][0] << ' ';
        cout << '\n';
    }
    */
    long long ans=0;
    vector<vector<int>> lst(n+1,vector<int>());
    BIT bit(n+1);
    auto cal = [&](int l,int r,vector<range> cur){
        int cnt=0,Max=cur.back().id,Min=cur.front().id;
        //cout << '*' << l << ' ' << r << '\n';
        for(auto [id,lt,rt]:cur){
            lt=max(Min,lt);rt=min(Max,rt);
            //cout << id << ' ' << lt << ' ' << rt << '\n';
            lst[rt+1].push_back(id);
            bit.update(id,1);cnt++;
            for(int x:lst[id]) bit.update(x,-1),cnt--;
            ans+=cnt-bit.query(lt-1);
        }
        for(int x:lst[Max+1]) bit.update(x,-1);
        for(int i=Min;i<=Max+1;i++) lst[i].clear();
        //cout << ans << '\n';
    };
    for(int l=1;l<m-1;l++){
        for(int r=l;r<m-1;r++){
            if(pos[l][r].empty()) continue;
            vector<range> cur;
            for(auto st:pos[l][r]){
                if(cur.empty() || cur.back().id+1==st.id) cur.push_back(st);
                else cal(l,r,cur),cur={st};
            }
            if(!cur.empty()) cal(l,r,cur);
        }
    }
    return ans;
}
