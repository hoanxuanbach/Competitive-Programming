#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int maxn = 2e5;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n=inf.readInt(1,maxn,"n");inf.readEoln();
    for(int i=1;i<=n;i++){
        inf.readInt(0,maxn,"a");
        if(i<n) inf.readSpace();
        else inf.readEoln();
    }
    int q=inf.readInt(1,maxn,"q");inf.readEoln();
    for(int i=1;i<=q;i++){
        int l=inf.readInt(1,n,"l");inf.readSpace();
        int r=inf.readInt(l,n,"r");inf.readEoln();
        assert((r-l)&1);
    }
    inf.readEof();
}