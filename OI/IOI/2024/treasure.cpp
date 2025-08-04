#include "treasure.h"
#include<bits/stdc++.h>
using namespace std;
const int S = 5e8+1;

std::vector<int> encode(std::vector<std::pair<int, int>> P) {
    int N=(int)P.size();
    vector<int> res,com;
    for(int i=0;i<N;i++){
        res.push_back(P[i].first);
        res.push_back(S+P[i].second);
        com.push_back(P[i].second);
    }
    sort(P.begin(),P.end());
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int sz=(int)com.size();
    vector<int> bit(sz+1),cnt(N);
    auto query = [&](int x){
        int num=0;
        for(int i=x;i>=1;i-=(i&(-i))) num+=bit[i];
        return num;
    };
    auto update = [&](int x){
        for(int i=x;i<=sz;i+=(i&(-i))) bit[i]++;
    };
    for(int i=N-1;i>=0;i--){
        int pos=lower_bound(com.begin(),com.end(),P[i].second)-com.begin()+1;
        cnt[i]=query(pos);update(pos);
    }
    int C=2*S;
    for(int i=0;i<N;i++){
        res.push_back(C+cnt[i]);
        C+=(N-i);
    }
    return res;
}

std::vector<std::pair<int, int>> decode(std::vector<int> E) {
    int N=(int)E.size()/3;
    vector<int> X,Y,cnt(N);
    for(int x:E){
        if(x<S) X.push_back(x);
        else if(x<2*S) Y.push_back(x-S);
        else{
            x-=2*S;
            int l=0,r=N-1;
            while(l<r){
                int m=(l+r)>>1;
                int total=(N+(N-m))*(m+1)/2;
                if(total<=x) l=m+1;
                else r=m;
            }
            cnt[l]=x-(N-l+1+N)*l/2;
        }
    }
    sort(X.begin(),X.end());
    vector<int> com;
    for(int x:Y) com.push_back(x);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int sz=(int)com.size();
    vector<int> bit(sz+1);
    auto update = [&](int x,int val){
        for(int i=x;i<=sz;i+=(i&(-i))) bit[i]+=val;
    };
    for(int i=0;i<N;i++){
        int pos=lower_bound(com.begin(),com.end(),Y[i])-com.begin()+1;
        update(pos,1);
    }
    vector<pair<int,int>> res;
    for(int i=0;i<N;i++){
        int p=0,k=cnt[i]+1;
        for(int i=16;i>=0;i--){
            if(p+(1<<i)<=sz && bit[p+(1<<i)]<k) k-=bit[p+=(1<<i)];
        }
        res.push_back({X[i],com[p]});
        update(p+1,-1);
    }
    return res;
}
