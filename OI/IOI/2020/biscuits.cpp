#include "biscuits.h"
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second

long long count_tastiness(long long x, std::vector<long long> a) {
	int k=60;a.resize(k);
    for(int i=1;i<k;i++) a[i]=a[i]*(1LL<<i)+a[i-1];
    for(int i=0;i<k;i++) a[i]/=x,a[i]=min(a[i],(1LL<<(i+1))-1);
    vector<pii> cur;cur.push_back({min(a[k-1],(1LL<<k)-1),1});
    for(int i=k-1;i>=0;i--){
        vector<pii> nw;
        int sum=0;
        for(pii x:cur){
            nw.push_back({min(x.fi&((1LL<<i)-1),(i==0?0:a[i-1])),x.se});
            if(x.fi>=(1LL<<i)) sum+=x.se;
        }
        if(sum!=0) nw.push_back({min((1LL<<i)-1,(i==0?0:a[i-1])),sum});
        cur.clear();sort(nw.begin(),nw.end());
        for(pii x:nw){
            if(cur.empty() || x.fi!=cur.back().fi) cur.push_back(x);
            else cur.back().se+=x.se;
        }
    }
    return (cur.empty()?0:cur[0].se);
}
