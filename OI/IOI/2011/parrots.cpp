#include "encoder.h"
#include "encoderlib.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxa = 256;
const int Max = 35;
const int Lim = 27;
ll dp[55][55];


void encode(int N, int M[])
{
    for(int i=0;i<=Max;i++){
        for(int j=0;j<Lim;j++){
            dp[i][j]=!(i|j);
            if(i) dp[i][j]+=dp[i-1][j];
            if(j) dp[i][j]+=dp[i][j-1];
        }
    }
    int cur=0;
    for(int i=0;i<N;i+=7){
        ll num=0,mul=1;
        int cnt=0;
        for(int j=i;j<min(i+7,N);j++){
            num+=1LL*M[j]*mul,mul*=maxa,cnt++;
        }
        for(int j=cnt*5;j>=1;j--){
            for(int k=0;k<min(maxa-cur,Lim);k++){
                if(dp[j][k]>num){
                    if(k) num-=dp[j][k-1];
                    send(cur+k);
                    break;
                }
            }
        }
        cur+=Lim;
    }
}
