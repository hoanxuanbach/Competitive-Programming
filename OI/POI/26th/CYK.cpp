#include "cyklib.hpp"
#include<bits/stdc++.h>
using namespace std;
#define int long long
/*
int circular_shift(int x){
    cout << x << endl;
    int a;cin >> a;
    return a;
}
void give_answer(int x){
    cout << x << endl;
    exit(0);
}
*/
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int a=circular_shift(0),d=1,f=a,nxt=-1;
    while(true){
        nxt=circular_shift(d);
        if(nxt==a){
            give_answer(d);
            return 0;
        }
        if(nxt<a) break;
        a=nxt;d<<=1;
    }
    int l,r;
    if(nxt>=f){l=d;r=2*d;}
    else{
        a=nxt;d<<=1;
        while(true){
            nxt=circular_shift(d);
            if(nxt==a){
                give_answer(d);
                return 0;
            }
            if(nxt>=f || nxt<a) break;
            a=nxt;d<<=1;
        }
        l=d;r=2*d;
    }
    a=nxt;
    while(r-l>1){
        d=(r-l)>>1;nxt=circular_shift(l);
        if(nxt==a){
            give_answer(l);
            return 0;
        }
        int nxt2=circular_shift(d);
        if(nxt2==a){
            give_answer(l+d);
            return 0;
        }
        if(nxt>a){
            if(nxt2>nxt || nxt2<a) l+=d;
            else r-=d;
        }
        else{
            if(nxt2<a && nxt2>nxt) l+=d;
            else r-=d;
        }
        a=nxt2;
    }
    give_answer(l);
}
