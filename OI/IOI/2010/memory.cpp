#include "grader.h"
#include "memory.h"
#include<bits/stdc++.h>
using namespace std;

void play() {
   vector<vector<int>> c(25);
   for(int i=1;i<=50;i++){
        char a=faceup(i);
        c[a-'A'].push_back(i);
   }
   for(int i=0;i<25;i++){
        faceup(c[i][0]);
        faceup(c[i][1]);
   }
}
