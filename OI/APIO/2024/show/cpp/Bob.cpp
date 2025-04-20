#include <bits/stdc++.h>
#include "Bob.h"
using namespace std;

long long Bob(std::vector<std::pair<int,int>> V){
    long long ans=0,L=1;
    for(auto [x,y]:V){
        x--;y--;
        while(ans%y!=x) ans+=L;
        L*=y/__gcd((long long)y,L);
    }
    return ans;
}
