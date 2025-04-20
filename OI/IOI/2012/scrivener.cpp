#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
const int maxl=20;

char c[maxn];
vector<int> node;
int cnt=0,cur=0;
int dep[maxn],par[maxn][maxl];

void Init() {}

void TypeLetter(char L) {
    cnt++;par[cnt][0]=cur;
    for(int i=1;i<maxl;i++) par[cnt][i]=par[par[cnt][i-1]][i-1];
    dep[cnt]=dep[cur]+1;c[cnt]=L;
    cur=cnt;node.push_back(cur);
    //cout << cur << '\n';
}

void UndoCommands(int U) {
    cur=node[(int)node.size()-U-1];
    node.push_back(cur);
    //cout << cur << '\n';
}

char GetLetter(int k) {
    k=dep[cur]-k-1;
    int cc=cur;
    for(int i=0;i<maxl;i++) if(k&(1<<i)) cc=par[cc][i];
    return c[cc];
}
