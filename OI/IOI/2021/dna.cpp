#include "dna.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
int cnt[maxn][6],n,num[6];
map<string,int> mp;
void init(std::string a, std::string b) {
    mp["AC"]=0;mp["CA"]=1;
    mp["TA"]=2;mp["AT"]=3;
    mp["CT"]=4;mp["TC"]=5;
    n=(int)a.length();
    a="#"+a;b="#"+b;
    for(int i=1;i<=n;i++){
        string cur;cur+=a[i];cur+=b[i];
        int d=mp[cur];
        for(int j=0;j<6;j++) cnt[i][j]=cnt[i-1][j]+(d==j && a[i]!=b[i]);
    }
}

int get_distance(int x, int y) {
    int res=0;x++;y++;
    for(int i=0;i<6;i++) num[i]=cnt[y][i]-cnt[x-1][i];
    for(int i=0;i<6;i+=2){
        int d=min(num[i],num[i+1]);
        res+=d;num[i]-=d;num[i+1]-=d;
    }
    if(num[0]!=num[2] || num[0]!=num[4] || num[1]!=num[3] || num[1]!=num[5]) return -1;
    res+=2*(num[0]+num[1]);
	return res;
}
