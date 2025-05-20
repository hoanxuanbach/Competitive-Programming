#include<bits/stdc++.h>
#include"testlib.h"
using namespace std;
 
#define f first
#define s second
 
const int maxn = 100'000;
const int maxa = 1e9;
 
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, maxn, "n");inf.readSpace();
    int q=inf.readInt(1,maxn,"q");
    inf.readEoln();
    inf.readInts(n,0,1,"c");
    inf.readEoln();
    for(int i=1;i<n;i++){
        int u=inf.readInt(1,n,"u");inf.readSpace();
        int v=inf.readInt(1,n,"v");inf.readSpace();
        int w=inf.readInt(-maxa,maxa,"w");
        inf.readEoln();
    }
    for(int i=1;i<=q;i++){
        int op=inf.readInt(1,2,"op");inf.readSpace();
        if(op==1){
            int u=inf.readInt(1,n,"u");
        }
        else{
            int u=inf.readInt(1,n,"u");inf.readSpace();
            int v=inf.readInt(1,n,"v");inf.readSpace();
            int t=inf.readInt(0,1,"t");inf.readSpace();
            int k=inf.readInt(1,3,"k");
        }
        inf.readEoln();
    }
    inf.readEof();
}
