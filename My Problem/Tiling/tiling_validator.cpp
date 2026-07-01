#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
const int maxT = 10000;
const int maxN = 100;
const int maxA = 1'000'000'000;

void setTestCase(){
    int n=inf.readInt(1,maxN,"n");inf.readSpace();
    int m=inf.readInt(1,maxN,"m");inf.readEoln();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(j) inf.readSpace();
            inf.readInt(0,maxA,"a");
        }
        inf.readEoln();
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int test = inf.readInt(1,maxT,"test");inf.readEoln();
    while(test--) setTestCase();
    inf.readEof();
}