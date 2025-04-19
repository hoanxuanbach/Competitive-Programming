#include "minerals.h"
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int lst=0;
int query(int x){
    int cur=Query(x);
    int dif=(lst!=cur);lst=cur;
    return dif;
}
void dnc(vector<int> l,vector<int> r,bool f){
    int n=(int)l.size(),m=ceil(n*0.36);
    if(n==1) return Answer(l[0],r[0]);
    if(f) m=n-m;
    if(f) for(int i=n-1;i>=m;i--) query(l[i]);
    else for(int i=0;i<m;i++) query(l[i]);
    vector<int> lt,rt;
    shuffle(r.begin(),r.end(),rng);
    for(int x:r){
        if((int)lt.size()==m) rt.push_back(x);
        else if((int)rt.size()==n-m) lt.push_back(x);
        else if(query(x)) rt.push_back(x);
        else lt.push_back(x);
    }
    dnc(vector<int>(l.begin(),l.begin()+m),lt,true);
    dnc(vector<int>(l.begin()+m,l.end()),rt,false);
}
void Solve(int N) {
    vector<int> l,r;
    for(int i=1;i<=2*N;i++){
        if(query(i)) l.push_back(i);
        else r.push_back(i);
    }
    dnc(l,r,true);
}
