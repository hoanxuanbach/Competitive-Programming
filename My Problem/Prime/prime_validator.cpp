#include<bits/stdc++.h>
#include "testlib.h"
using namespace std;
 
const int maxn=1e6;
 
int main(int argc,char* argv[]){
    registerValidation(argc,argv);
    int n=inf.readInt(1,maxn,"n");
    inf.readEoln();
    for(int i=1;i<=n;i++){
        int a=inf.readInt(1,maxn,"a");
        if(i!=n) inf.readSpace();
    }
    inf.readEoln();
    inf.readEof();
}
