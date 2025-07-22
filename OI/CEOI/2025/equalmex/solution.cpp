#include "equalmex.h"
#include <bits/stdc++.h>
using namespace std;
const int A = 400001;

std::vector<int> solve(
    int n, std::vector<int>& v,
    int q, std::vector<std::pair<int, int>>& queries) {
    
    vector<int> tree(4*A,-1);
    function<void(int,int,int,int,int)> update = [&](int l,int r,int id,int x,int val){
        if(l==r){
            tree[id]=val;
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) update(l,mid,id<<1,x,val);
        else update(mid+1,r,id<<1|1,x,val);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
    };

    auto cal = [&]{
        vector<int> res(q);
        vector<vector<pair<int,int>>> qq(n);
        for(int i=0;i<q;i++) if(queries[i].first<=queries[i].second) qq[queries[i].second].push_back({queries[i].first,i});

        tree.assign(4*A,-1);
        function<int(int,int,int,int)> get = [&](int l,int r,int id,int x){
            if(l==r) return x;
            int mid=(l+r)>>1;
            if(tree[id<<1]>=x) return get(mid+1,r,id<<1|1,x);
            else return get(l,mid,id<<1,x);
        };

        
        for(int i=0;i<n;i++){
            update(1,A,1,v[i],i);
            for(auto &[l,id]:qq[i]) res[id]=get(1,A,1,l);
        }
        return res;
    };
    
    
    vector<int> mex = cal();

    auto cal2 = [&](){
        vector<int> res(q);
        vector<vector<pair<int,int>>> qq(n);
        for(int i=0;i<q;i++) if(queries[i].first<=queries[i].second) qq[queries[i].second].push_back({queries[i].first,i});

        tree.assign(4*A,-1);
        function<int(int,int,int,int)> get = [&](int l,int r,int id,int x){
            if(l==r) return tree[id];
            int mid=(l+r)>>1;
            if(x>mid) return min(tree[id<<1],get(mid+1,r,id<<1|1,x));
            else return get(l,mid,id<<1,x);
        };

        
        for(int i=0;i<n;i++){
            update(1,A,1,v[i],i);
            for(auto &[l,id]:qq[i]) res[id]=(mex[id]==1?i:get(1,A,1,mex[id]-1));
        }

        return res;
    };


    return res;
}
