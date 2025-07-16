#include<bits/stdc++.h>
#include "messy.h"
using namespace std;

vector<int> restore_permutation(int n, int w, int r) {
    vector<int> res(n);
    string s(n,'0');
    function<void(int,int)> add = [&](int l,int r){
        if(l==r-1) return;
        int mid=(l+r)>>1;
        for(int i=l;i<r;i++) s[i]='0';
        for(int i=l;i<mid;i++) s[i]='1',add_element(s),s[i]='0';
        for(int i=mid;i<r;i++) s[i]='1';
        add(l,mid);
        for(int i=l;i<mid;i++) s[i]='1';
        add(mid,r);
    };
    add(0,n);
    compile_set();
    s=string(n,'0');
    function<void(int,int,vector<int>)> check = [&](int l,int r,vector<int> p){
        if(l==r-1){
            res[p[0]]=l;
            return;
        }
        int mid=(l+r)>>1;
        for(int x:p) s[x]='0';
        vector<int> lt,rt;
        for(int x:p){
            s[x]='1';
            if(check_element(s)) lt.push_back(x);
            else rt.push_back(x);
            s[x]='0';
        }
        for(int x:rt) s[x]='1';
        check(l,mid,lt);
        for(int x:lt) s[x]='1';
        check(mid,r,rt);
    };
    vector<int> pos(n);
    for(int i=0;i<n;i++) pos[i]=i;
    check(0,n,pos);
    return res;
}
