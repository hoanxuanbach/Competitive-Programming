#include "grader.h"
#include "cluedo.h"
#include<bits/stdc++.h>
using namespace std;

void Solve(){
   vector<int> c(4,1);
   while(int t=Theory(c[1],c[2],c[3])) c[t]++;
}
