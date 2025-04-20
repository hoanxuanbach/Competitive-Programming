#include<bits/stdc++.h>
#include "grader.h"
#include "lang.h"
using namespace std;
const int M = 604069;
const int B = 65536;
const int S = 100;
const int L = 4;
const int K = 56;

int a[S+5][L+5],c[K+5][M+5];
int w[]={1,6,1,9};

void excerpt(int *E){
    pair<int,int> mx={0,0};
    for(int i=0;i<=S-L;i++){
        a[i][0]=E[i];
        for(int j=1;j<L;j++) a[i][j]=(1LL*a[i][j-1]*B+E[i+j])%M;
    }
    for(int t=0;t<K;t++){
        int cnt=0;
        for(int i=0;i<=S-L;i++) for(int j=0;j<L;j++) cnt+=min(c[t][a[i][j]],j)*w[j];
        mx=max(mx,{cnt,t});
    }
    int A=language(mx.second);
    for(int i=0;i<=S-L;i++) for(int j=0;j<L;j++) c[A][a[i][j]]++;
}
