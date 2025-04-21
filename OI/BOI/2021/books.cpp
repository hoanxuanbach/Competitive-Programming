#include <bits/stdc++.h>
#include "books.h"
using namespace std;
//#define ll long long
//
// --- Sample implementation for the task books ---
//
// To compile this program with the sample grader, place:
//     books.h books_sample.cpp sample_grader.cpp
// in a single folder and run:
//     g++ books_sample.cpp sample_grader.cpp
// in this folder.
//
 
map<int,long long> mp;
long long query(int x){
    if(mp.find(x)!=mp.end()) return mp[x];
    else return mp[x]=skim(x);
}
 
void solve(int N, int K, long long A, int S) {
    vector<int> ans(K);
    int l=1,r=N,pos=N+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(query(mid)>=A) pos=mid,r=mid-1;
        else l=mid+1;
    }
    vector<pair<long long,int>> d;
    for(int i=1;i<=min(K,pos-1);i++) d.push_back({query(i),i});
    for(int i=pos-1;i>=max(min(K,pos-1)+1,pos-K);i--) d.push_back({query(i),i});
    sort(d.begin(),d.end());
    if((int)d.size()>=K-1 && pos!=N+1){
        long long total=0;
        for(int i=0;i<K-1;i++) total+=d[i].first;
        total+=query(pos);
        if(total>=A && total<=2*A){
            for(int i=0;i<K-1;i++) ans[i]=d[i].second;
            ans[K-1]=pos;
            answer(ans);
            return;
        }
    }
    int sz=(int)d.size();
    for(int i=0;i<(1<<sz);i++){
        if(__builtin_popcount(i)!=K) continue;
        long long total=0;
        for(int j=0;j<sz;j++) if(i>>j&1) total+=d[j].first;
        if(A<=total && total<=2*A){
            ans.clear();
            for(int j=0;j<sz;j++) if(i>>j&1) ans.push_back(d[j].second);
            answer(ans);
            return;
        }
    }
    impossible();
}