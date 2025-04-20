#include "artclass.h"
#include <bits/stdc++.h>
using namespace std;
int style(int H, int W, int R[500][500], int G[500][500], int B[500][500]){
    int s=0;
    for(int i=0;i<H;i++) for(int j=0;j<W-1;j++) s+=abs(R[i][j]-R[i][j+1])+abs(G[i][j]-G[i][j+1])+abs(B[i][j]-B[i][j+1]);
    s/=H*(W-1);
    return (s<9?4:(s<23?1:(s<58?2:3)));
}
