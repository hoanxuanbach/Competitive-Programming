#include "perm.h"
#include<bits/stdc++.h>
using namespace std;

vector<int> construct_permutation(long long k){
    if(k==1) return {};
    else if(k==2) return {0};
    else if(k==3) return {1,0};
    vector<int> res=construct_permutation(k>>2);
    int s=(int)res.size();
    if(k%4==0){res.push_back(s);res.push_back(s+1);}
    else if(k%4==1){res.push_back(s);res.push_back(s+1);res.push_back(-1);for(int &x:res) x++;}
    else if(k%4==2){res.push_back(s);res.push_back(-1);res.push_back(s+1);for(int &x:res) x++;}
    if(k%4!=3) return res;
    if((k>>2)<=2 || (k>>2)%4==0){
        res.push_back(s);res.push_back(-1);res.push_back(s+1);res.push_back(-2);
        for(int &x:res) x+=2;
    }
    else{
        res.push_back(s);res.push_back(s+1);
        for(int &x:res){if(x>=2) x++;}
        res.push_back(2);
    }
    return res;
}
/*
signed main(){
    int n;cin >> n;
    vector<int> res=construct_permutation(n);
    for(int v:res) cout << v << ' ';
}
*/
