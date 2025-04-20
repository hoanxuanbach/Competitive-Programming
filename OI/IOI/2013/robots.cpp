#include "robots.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {
    vector<pii> p(T);
    for(int i=0;i<T;i++) p[i]={W[i],S[i]};
    sort(p.begin(),p.end());
    sort(X,X+A);sort(Y,Y+B);
    auto check = [&](int mid){
        priority_queue<int> pq;
        int pos=0;
        for(int i=0;i<A;i++){
            while(pos<T && p[pos].fi<X[i]) pq.push(p[pos++].se);
            for(int j=0;j<mid;j++){
                if(pq.empty()) break;
                pq.pop();
            }
        }
        while(pos<T) pq.push(p[pos++].se);
        for(int i=B-1;i>=0;i--){
            if(pq.empty()) return true;
            if(pq.top()>=Y[i]) return false;
            for(int j=0;j<mid;j++){
                pq.pop();
                if(pq.empty()) return true;
            }
        }
        if(pq.empty()) return true;
        else return false;
    };

    int l=1,r=T,res=-1;
    while(r>=l){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    return res;
}
