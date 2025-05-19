#include "rotate.h"
#include <bits/stdc++.h>
using namespace std;

void energy(int n, std::vector<int> v){
    vector<pair<int,int>> p(n);
    for(int i=0;i<n;i++) p[i]={v[i],i};
    sort(p.begin(),p.end());
    for(int i=0;i<n/2;i++) rotate({p[n/2+i].second},(75000+p[i].first-p[n/2+i].first)%50000); 
}