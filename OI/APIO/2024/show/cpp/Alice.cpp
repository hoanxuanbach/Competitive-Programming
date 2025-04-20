#include <bits/stdc++.h>
#include "Alice.h"
using namespace std;

std::vector<std::pair<int,int>> Alice(){
    long long x = setN(5000);
    vector<pair<int,int>> G;
    for(int i=2;i<=5000;i++) G.emplace_back(x%(i-1)+1,i);
    return G;
}
