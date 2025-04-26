#include<bits/stdc++.h>
#include "grader.h"
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define pii pair<int,int>
#define fi first
#define se second

void solve(int n) {
    rng.seed(998244353);
    vector<int> p(n);
    iota(p.begin(),p.end(),1);
    if(n==1){
        query(p);
        return;
    }
    while(true){
        int cnt=query(p);
        if(cnt==n) return;
        if(!cnt) break;
        shuffle(p.begin(),p.end(),rng);
    }

    //for(int x:p) cout << x << ' ';
    //cout << '\n';

    vector<int> c(n);
    iota(c.begin(),c.end(),0);
    int m=(n+1)/2;
    if(n&1) c.push_back(n);

    vector<int> res=p;
    vector<bool> used(n,false);
    vector<vector<int>> edge(n);

    for(int _=0;_<n;_++){
        vector<pii> s;
        for(int i=0;i<m;i++) if(c[i]<n && c[2*m-i-1]<n) s.push_back({c[i],c[2*m-i-1]});
        vector<int> pp=p;
        for(auto [x,y]:s) swap(pp[x],pp[y]);
        int cnt=query(pp);
        if(cnt==n) return;
        while(cnt){
            int l=0,r=(int)s.size()-2,val=0;
            while(l<=r){
                int mid=(l+r)>>1;pp=p;
                for(int i=0;i<=mid;i++) swap(pp[s[i].fi],pp[s[i].se]);
                int x=query(pp);
                if(x==n) return;
                if(x) val=x,r=mid-1;
                else l=mid+1;
            }
            if(!val) val=cnt;
            cnt-=val;
            auto [x,y]=s[l];
            if(val==2){
                swap(res[x],res[y]);
                used[x]=used[y]=false;
                //cout << "val " << x << ' ' << y << '\n';
            }
            else{
                //cout << "edge " << x << ' ' << y << '\n';
                edge[x].push_back(y);
                edge[y].push_back(x);
            }
            s.erase(s.begin(),s.begin()+l+1);
        }
        rotate(c.begin()+1,c.begin()+2,c.end());
    }
    for(int i=0;i<n;i++){
        if(used[i]) continue;
        int u=i;
        vector<int> v;
        do{
            used[u]=true;
            v.push_back(u);
            for(int x:edge[u]) if(!used[x]){u=x;break;}
            if(u==v.back()) break;
        }while(u!=i);
        int sz=(int)v.size();
        vector<int> pp=p;
        for(int i=0;i<sz-1;i++) swap(pp[v[i]],pp[v[i+1]]);
        int x=query(pp);
        if(x==n) return;
        if(x){
            for(int i=0;i<sz-1;i++) swap(res[v[i]],res[v[i+1]]);
        }
        else{
            for(int i=sz-2;i>=0;i--) swap(res[v[i]],res[v[i+1]]);
        }
    }
    int x=query(res);
    assert(x==n);
}
