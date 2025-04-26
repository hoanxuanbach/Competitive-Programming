#include <bits/stdc++.h>
using namespace std;
const int maxn=2e7+5;
int p[maxn];
int seed, n, k, S;
int getrand() {
	seed = ((seed * 12321) ^ 9999) % 32768;
	return seed;
}
void generateData() {
	cin >> k >> seed >> S;
	int t = 0;
	n = k * 2 + 1;
	memset(p, 0, sizeof(p));
	for( int i = 1; i <= n; ++i ) {
		p[i] = (getrand() / 128) % 2;
		t += p[i];
	}
	int i = 1;
	while( t > k ) {
		while ( p[i] == 0 ) ++i;
		p[i] = 0;
		--t;
	}
	while( t < k ) {
		while( p[i] == 1 ) ++i;
		p[i] = 1;
		++t;
	}
}
int cnt[maxn*2],sum[maxn];
int CalA(int s){
    int cur=0,num=0;
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+(p[i]?1:-1);
        if(p[i]){
            cnt[sum[i]+maxn]++;
            num+=(sum[i]>0);
        }
    }
    int res=0;
    for(int i=1;i<=n;i++){
        if(p[i]){
            cur++;
            num-=cnt[cur+maxn];
        }
        else{
            num+=cnt[cur+maxn];
            cur--;
        }
        if(p[i]){
            cnt[-1+cur+maxn]++;cnt[sum[i]+maxn]--;
            if(sum[i]>cur) num--;
        }
        if(num==s && !p[i]) res=i;
    }
    for(int i=1;i<=n;i++){
        if(p[i]) cnt[sum[i]-1+maxn]--;
    }
    return res;
}
int CalB(int s){
    int cur=0,num=-1;
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+(p[i]?-1:1);
        if(!p[i]){
            cnt[sum[i]+maxn]++;
            num+=(sum[i]>0);
        }
    }
    int res=0;
    for(int i=1;i<=n;i++){
        if(!p[i]){
            cur++;
            num-=cnt[cur+maxn];
        }
        else{
            num+=cnt[cur+maxn];
            cur--;
        }
        if(!p[i]){
            cnt[1+cur+maxn]++;cnt[sum[i]+maxn]--;
            if(sum[i]<=cur) num++;
        }
        if(num==s && !p[i]) res=i;
    }
    for(int i=1;i<=n;i++){
        if(!p[i]) cnt[sum[i]+1+maxn]--;
    }
    return res;
}
int main() {
	generateData();
    cout << CalA(0) << '\n' << CalA(S) << '\n' << CalB(S) << '\n';
	return 0;
}
