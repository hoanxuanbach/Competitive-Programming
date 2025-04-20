#include<bits/stdc++.h>
using namespace std;

// you may define some global variables, but it does not work if you try to transfer any information from function Alice to function Bob through these variables.
// you had better not use the same global variables in function Alice and in function Bob.

/*
p:              The original permutation owned by Alice. You can get its length by p.size().
				It is guaranteed that p.size()<=20 and each integers in [0, p.size()) appears exactly once in p.
return value:   The integer passed from Alice to Bob (64-bit unsigned).
*/

namespace ALICE{
    long long fac[25];
    unsigned long long solve(vector<int> p){
        fac[0]=1;
        for(int i=1;i<=20;i++) fac[i]=fac[i-1]*i;
        int N=(int)p.size();
        unsigned long long x=0;
        for(int i=N+1;i<=20;i++) x+=fac[i];
        vector<int> c(N);
        iota(c.begin(),c.end(),0);
        for(int i=0;i<N;i++){
            int pos=find(c.begin(),c.end(),p[i])-c.begin();
            x+=pos*fac[N-i-1];
            c.erase(c.begin()+pos);
        }
        return x;
    }
}

unsigned long long Alice(const std::vector<int> p){
	return ALICE::solve(p);
}

namespace BOB{
    long long fac[25];
    vector<int> solve(unsigned long long x){
        fac[0]=1;
        for(int i=1;i<=20;i++) fac[i]=fac[i-1]*i;
        int N=20;
        while(x>=fac[N]) x-=fac[N--];
        vector<int> p(N);
        iota(p.begin(),p.end(),0);
        vector<int> res;
        for(int i=N;i>=1;i--){
            int pos=x/fac[i-1];x%=fac[i-1];
            res.push_back(p[pos]);
            p.erase(p.begin()+pos);
        }
        return res;
    }
}

std::vector<int> Bob(const unsigned long long x){
	return BOB::solve(x);
}

