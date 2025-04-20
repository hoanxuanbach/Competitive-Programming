#include "monster.h"
//#include "grader.cpp"
#include<bits/stdc++.h>
using namespace std;

std::vector<int> Solve(int N) {
    vector<int> res(N);
    function<vector<int>(int,int)> dnc = [&](int l,int r){
        if(l==r-1){
            vector<int> res={l};
            return res;
        }
        int mid=(l+r)>>1;
        vector<int> lt=dnc(l,mid),rt=dnc(mid,r);
        vector<int> cc;
        for(int i=0,j=0;i+j<r-l;){
            if(i<mid-l && (j==r-mid || Query(rt[j],lt[i]))) cc.push_back(lt[i++]);
            else cc.push_back(rt[j++]);
        }
        return cc;
    };
    vector<int> a=dnc(0,N);

    int k=min(N,12);
    vector<int> cnt(k,0);
    for(int i=0;i<k;i++) for(int j=i+1;j<k;j++){
        if(Query(a[i],a[j])) cnt[i]++;
        else cnt[j]++;
    }
    int p=-1;
    for(int i=0;i<k;i++) if(cnt[i]==1){
        if(p==-1 || Query(a[i],a[p])) p=i;
    }
    int pre=0;
    while(p<N){
        for(int i=pre;i<=p;i++) res[a[i]]=pre+p-i;
        int c=++p;
        while(p<N && Query(a[p],a[pre])) p++;
        pre=c;
    }
    return res;
}
