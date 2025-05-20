#include<bits/stdc++.h>
#include "testlib.h"
using namespace std;
 
int main(int argc, char* argv[]){
	registerGen(argc, argv, 1);
	int min_n = atoi(argv[1]), max_n = atoi(argv[2]);
	int n = rnd.next(min_n,max_n);
    cout << n << '\n';
    for(int i=1;i<=n;i++){
        int a=rnd.next(1,13);
        cout << a;
        if(i!=n) cout << ' ';
    }
    cout << '\n';
}
