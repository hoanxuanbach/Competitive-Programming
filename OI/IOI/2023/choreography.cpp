#include "choreography.h"
#include <bits/stdc++.h>
using namespace std;

int p0,p1,i0,i1;

int N;
bool S=false;
vector<int> P,I;

void init(int _N, std::vector<int> _P) {
    N=_N;P=_P;
    I.assign(N,0);
    for(int i=0;i<N;i++) I[P[i]]=i;
    return;
} 

void move_right(int K) {
    p0=(p0+K)%N;
    p1=(p1+K)%N;
}

void move_left(int K) {
    move_right(N-K);
}

void swap_places() {
    p0=(p0+(p0&1 ? N-1 : 1))%N;
    p1=(p1+(p1&1 ? 1 : N-1))%N;
}

void move_around() {
    S=!S;
    swap(p0,i0);
    swap(p1,i1);
    return;
}

int get_position(int D){
    int i=(((D-i0)&1 ? D-i1 : D-i0)+N)%N;
    i=(S?P[i]:I[i]);
    return (i&1 ? (i+p1)%N : (i+p0)%N);
}
