#include<bits/stdc++.h>
#include "combo.h"
using namespace std;

string guess_sequence(int n){
    char c;string ans;
    vector<char> ch;
    if(press("AB")){
        if(press("A")) c='A';
        else c='B';
    }
    else{
        if(press("X")) c='X';
        else c='Y';
    }
    if(c!='A') ch.push_back('A');
    if(c!='B') ch.push_back('B');
    if(c!='X') ch.push_back('X');
    if(c!='Y') ch.push_back('Y');
    ans.push_back(c);
    if(n==1) return ans;
    for(int i=2;i<=n-1;i++){
        int a=press(ans+ch[0]+ch[0]+ans+ch[0]+ch[1]+ans+ch[0]+ch[2]+ans+ch[1]);
        if(a==i+1) ans.push_back(ch[0]);
        else if(a==i) ans.push_back(ch[1]);
        else ans.push_back(ch[2]);
    }
    if(press(ans+ch[0])==n) return (ans+ch[0]);
    else if(press(ans+ch[1])==n) return (ans+ch[1]);
    else return ans+ch[2];
}
