#include "mushrooms.h"
#include<bits/stdc++.h>
using namespace std;
#define sz(x) (int)x.size()
const int K=100;

int count_mushrooms(int n) {
    if(n<=450){
        int cnt=1;
        for(int i=1;i<n;i+=2){
            vector<int> x={i};
            x.push_back(0);
            if(i+1<n) x.push_back(i+1);
            cnt+=(int)x.size()-1-use_machine(x);
        }
        return cnt;
    }
    int t=0,res=0;
    vector<vector<int>> a(2);
    a[0].push_back(0);
    a[use_machine({0,1})].push_back(1);
    a[use_machine({0,2})].push_back(2);
    auto update = [&](){
        if(sz(a[0])<sz(a[1])){
            swap(a[0],a[1]),t^=1;
            return true;
        }
        return false;
    };
    update();

    int x=use_machine({3,a[0][0],4,a[0][1]});
    a[x&1].push_back(3);
    a[x>>1].push_back(4);
    update();

    for(int i=5;sz(a[0])<K;){
        x=use_machine({i,a[0][0],i+1,a[0][1],i+2,a[0][2]});
        a[x&1].push_back(i);
        if(!(x&2)){
            x>>=2;
            a[x].push_back(i+1);
            a[x].push_back(i+2);
            i+=3;
        }
        else if(sz(a[1])<2){
            x=use_machine({i+1,a[0][0]});
            a[x].push_back(i+1);
            a[x^1].push_back(i+2);
            i+=3;
        }
        else{
            x=use_machine({i+4,a[0][0],i+3,a[0][1],i+2,a[0][2],a[1][0],i+1,a[1][1]})-1;
            a[x&1].push_back(i+4);x>>=1;
            a[x&1].push_back(i+3);x>>=1;
            a[x].push_back(i+2);
            a[x^1].push_back(i+1);
            i+=5;
        }
        update();
    }
    res=sz(a[1]);
    for(int i=sz(a[0])+sz(a[1]);i<n;){
        int r=min(i+sz(a[0]),n);
        vector<int> m;
        for(int j=i;j<r;j++){
            m.push_back(j);
            m.push_back(a[0][j-i]);
        }
        x=use_machine(m);
        res+=(x+1)/2;
        a[x&1].push_back(i);
        if(update()) res=r-res;
        i=r;
    }
    return (t?res:n-res);
}
