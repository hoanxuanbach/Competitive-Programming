#include "art.h"
//
// --- Sample implementation for the task art ---
//
// To compile this program with the sample grader, place:
//     art.h art_sample.cpp sample_grader.cpp
// in a single folder, then open the terminal in this directory (right-click onto an empty spot in the directory,
// left click on "Open in terminal") and enter e.g.:
//     g++ -std=c++17 art_sample.cpp sample_grader.cpp
// in this folder. This will create a file a.out in the current directory which you can execute from the terminal
// as ./a.out
// See task statement or sample_grader.cpp for the input specification
//
#include<bits/stdc++.h>
using namespace std;
 
void solve(int N) {
    vector<int> ord(N),num(N);
    iota(ord.begin(),ord.end(),1);
    iota(num.begin(),num.end(),1);
    vector<int> p(N,0);
    int cc=publish(ord);
    for(int i=1;i<N;i++){
        ord.erase(ord.begin()+i-1);
        ord.push_back(i);
        int d=(cc+N-i-publish(ord))/2;
        ord.pop_back();
        ord.insert(ord.begin()+i-1,i);
        p[num[d]-1]=i;num.erase(num.begin()+d);
    }
    for(int i=0;i<N;i++) if(!p[i]) p[i]=N;
    answer(p);
}