#include "molecules.h"
#include "bits/stdc++.h"
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second

vector<int> find_subset(int l, int u, vector<int> w) {
    int n=(int)w.size();
    vector<pii> p;
    for(int i=0;i<n;i++) p.push_back({w[i],i});
    sort(p.begin(),p.end());
    int pos=0;
    long long sum=0;
    for(int i=0;i<n;i++){
        while(pos<n && sum<l) sum+=p[pos++].fi;
        if(sum>=l && sum<=u){
            vector<int> res;
            for(int j=i;j<pos;j++) res.push_back(p[j].se);
            sort(res.begin(),res.end());
            return res;
        }
        sum-=p[i].fi;
    }
    return {};
}
