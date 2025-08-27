#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int maxn = 5e5;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n=inf.readInt(1, maxn, "n");inf.readEoln();
    for(int i=1;i<=n;i++){
        int a=inf.readInt(0,mod-1,"a");
        if(i<n) inf.readSpace();
        else inf.readEoln();
    }
    int q=inf.readInt(1,maxn,"q");inf.readEoln();
    for(int i=1;i<=q;i++){
        int id=inf.readInt(1,2,"id");inf.readSpace();
        int l=inf.readInt(1,n,"l");inf.readSpace();
        int r=inf.readInt(l,n,"r");inf.readEoln();
    }
    inf.readEof();
}