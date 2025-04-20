#include<bits/stdc++.h>
using namespace std;
const int S = 256;

void p(string s){
    cout << s << '\n';
}

signed main(){
    freopen("odometer.txt","w",stdout);
    p("jump A0");
    for(int i=0;i<=14;i++){
        string s=to_string(i),t=to_string(i+1);
        p("X"+s+":");
        p("right");
        p("border A"+t);
        p("move");
        p("right");
        p("Y"+s+":");
        p("border Z"+s);
        p("move");
        p("jump Y"+s);
        p("Z"+s+":");
        p("right");

        p("A"+s+":");
        p("right");
        p("B"+s+":");
        for(int j=0;j<i;j++) p("get");
        p("pebble C"+s);
        p("jump E"+s);
        p("C"+s+":");
        for(int j=0;j<i;j++) p("put");

        p("border X"+s);
        p("move");
        p("jump B"+s);
    }
    for(int i=14;i>0;i--){
        p("E"+to_string(i)+":");
        p("put");
    }
    p("E0:");
    p("A15:");
}
