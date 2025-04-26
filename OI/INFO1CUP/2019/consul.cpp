#include "grader.h"
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve(int n)
{
    vector<int> p(n);
    iota(p.begin(),p.end(),1);
    shuffle(p.begin(),p.end(),rng);
    set<int> ss;
    int num=0;
    for(int i=0;i<n && num<min(60,n);i++){
        int x=p[i];
        int k=kth(x);num++;
        if(ss.find(k)!=ss.end()) continue;
        if(num==60) break;
        int d=cnt(k);num++;
        if(3*d>n){
            say_answer(k);
            return;
        }
        ss.insert(k);
    }
    say_answer(-1);
}
