#include<bits/stdc++.h>
using namespace std;
using i32 = int;
#define int long long
const int mod = 1e9+7;
const int base = 998244353;

i32 findP(char T[], char P[], i32 N, i32 M)
{
    int B=1,cnt=0;
    vector<int> h(26,0),cc(26,0);
    for(int i=0;i<M;i++){
        B=B*base%mod;
        for(int j=0;j<26;j++) h[j]=h[j]*base%mod;
        h[P[i]-'a']=(h[P[i]-'a']+1)%mod;
    }
    sort(h.begin(),h.end());
    for(int i=0;i<N;i++){
        for(int j=0;j<26;j++) cc[j]=cc[j]*base%mod;
        cc[T[i]-'a']=(cc[T[i]-'a']+1)%mod;
        if(i>=M) cc[T[i-M]-'a']=(cc[T[i-M]-'a']+mod-B)%mod;
        vector<int> cur=cc;
        sort(cur.begin(),cur.end());
        if(cur==h) cnt++;
    }
	return cnt;
}
#undef int
