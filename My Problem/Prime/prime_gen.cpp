#include<bits/stdc++.h>
#include "testlib.h"
using namespace std;
const int maxa=1e6;
 
int main(int argc,char* argv[]){
    registerGen(argc,argv,1);
    int sub=atoi(argv[1]),n;
    if(sub==1) n=20;
    else if(sub==2) n=5000;
    else n=1000000;
    cout << n << '\n';
    for(int i=1;i<=n;i++){
        int x=rnd.next(1,maxa);
        cout << x;
        if(i!=n) cout << ' ';
    }
    cout << '\n';
}
