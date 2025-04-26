#include "interactive.h"
#include<bits/stdc++.h>
using namespace std;

vector<int> guess(int n) {
    //cout << n << '\n';
	vector <int> ans(n);
    ans[0]=ask(1);
    //cout << ans[0] << '\n';
    vector<set<int>> ss(7);
    for(int i=0;i<7;i++){
        vector<int> p;
        for(int j=2;j<=n;j++) if((j-1)>>i&1) p.push_back(j);
        if(p.empty()) continue;
        map<int,int> mp;
        vector<int> a=get_pairwise_xor(p);
        p.push_back(1);
        vector<int> b=get_pairwise_xor(p);
        for(int x:b) mp[x]++;
        for(int x:a) mp[x]--;
        for(auto [x,cnt]:mp) if(x && cnt) ss[i].insert(x^ans[0]);
    }
    function<void(int,vector<int>,vector<int>)> dnc = [&](int t,vector<int> pos,vector<int> val){
        if(pos.empty()) return;
        if(t==7){
            ans[pos.back()]=val.back();
            return;
        }
        vector<int> lpos,rpos;
        for(int x:pos){
            if(x>>t&1) lpos.push_back(x);
            else rpos.push_back(x);
        }
        vector<int> lval,rval;
        for(int x:val){
            if(ss[t].find(x)!=ss[t].end()){
                ss[t].erase(x);
                lval.push_back(x);
            }
            else rval.push_back(x);
        }
        dnc(t+1,lpos,lval);dnc(t+1,rpos,rval);
    };
    set<int> all;
    all.insert(ans[0]);
    for(int i=0;i<7;i++) for(int x:ss[i]) all.insert(x);
    vector<int> val;
    for(int x:all){
        val.push_back(x);
        //cout << x << ' ';
    }
    //cout << '\n';
    vector<int> pos(n,0);
    iota(pos.begin(),pos.end(),0);
    dnc(0,pos,val);
    return ans;
}
