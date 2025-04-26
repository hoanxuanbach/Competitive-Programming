#include "onetwothree.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 15005;
#define pii pair<int,int>
#define fi first
#define se second

int N,M;
vector<int> x,y,z,A;
vector<vector<int>> cur,ans;

bool check(int c0,int c1){
    if(c0+c1>M) return false;
    int p0=0,p1=0;
    cur.clear();
    for(int i=0;i<N;i++){
        if(A[i]==2){
            if(p0==c0 && p1==c1) continue;
            else if(p0==c0){
                if(x[p1]<i && i<z.end()[-c1+p1]){
                    cur.push_back({x[p1],i,z.end()[-c1+p1]});
                    p1++;
                }
            }
            else if(p1==c1){
                if(z[p0]<i && i<x.end()[-c0+p0]){
                    cur.push_back({z[p0],i,x.end()[-c0+p0]});
                    p0++;
                }
            }
            else{
                int l0=z[p0],r0=x.end()[-c0+p0];
                int l1=x[p1],r1=z.end()[-c1+p1];
                if(i<l0 || r0<i){
                    if(l1<i && i<r1){
                        cur.push_back({l1,i,r1});
                        p1++;
                    }
                }
                else if(i<l1 || r1<i){
                    cur.push_back({l0,i,r0});
                    p0++;
                }
                else if(r0<r1){
                    cur.push_back({l0,i,r0});
                    p0++;
                }
                else{
                    cur.push_back({l1,i,r1});
                    p1++;
                }
            }
        }
    }
    if(p0<c0 || p1<c1) return false;
    return true;
};

void maximize(vector<int> a){
    N=(int)a.size();A=a;
    for(int i=0;i<N;i++){
        if(A[i]==1) x.push_back(i);
        else if(A[i]==2) y.push_back(i);
        else z.push_back(i);
    }
    M=min({(int)x.size(),(int)y.size(),(int)z.size()});
    int pos=M;
    for(int i=0;i<=M;i++){
        while(pos>=0 && !check(i,pos)) pos--;
        if(pos>=0 && i+pos>(int)ans.size()) ans=cur;
    }
    for(auto d:ans) answer(d[0],d[1],d[2]);
}
