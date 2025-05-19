#include<bits/stdc++.h>
#include "testlib.h"
using namespace std;
 
const int maxn=2e5;
 
int main(int argc,char* argv[]){
    registerValidation(argc,argv);
    int n=inf.readInt(1,maxn,"n");
    inf.readEoln();
    vector<int> cur;
    for(int i=0;i<=1;i++){
        for(int j=1;j<=n;j++){
            int p=inf.readInt(1,2*n,"p");
            if(j!=n) inf.readSpace();
            cur.push_back(p);
        }
        inf.readEoln();
    }
    sort(cur.begin(),cur.end());
    for(int i=1;i<=2*n;i++) ensure(cur[i-1]==i);
    int q=inf.readInt(1,maxn,"q");
    inf.readEoln();
    for(int i=1;i<=q;i++){
        int x1=inf.readInt(0,1,"x1");inf.readSpace();
        int y1=inf.readInt(1,n,"y1");inf.readSpace();
        int x2=inf.readInt(0,1,"x2");inf.readSpace();
        int y2=inf.readInt(y1,n,"y2");inf.readSpace();
        int l=inf.readInt(1,2*n,"l");inf.readSpace();
        int r=inf.readInt(l,2*n,"r");inf.readEoln();
    }
    inf.readEof();
}
