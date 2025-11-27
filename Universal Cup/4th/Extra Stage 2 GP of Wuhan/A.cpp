#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int mod = 998244353;

int f(int a,int b,int c,int n){
	if(a<0) {
		int k=(-a+c-1)/c;a+=k*c;
		return f(a,b,c,n)-n*(n+1)/2*k;
	}
	if(b<0) {
		int k=(-b+c-1)/c;
		b+=k*c;
		return f(a,b,c,n)-(n+1)*k;
	}
	int res=n*(n+1)/2*(a/c)+(n+1)*(b/c);a%=c;b%=c;
	if(!a) return res;
	int m=(a*n+b)/c;
	return res+n*m-f(c,c-b-1,a,m-1);
}

void solve(){
    int a,b,c,d,n,m;cin >> a >> b >> c >> d >> n >> m;n--;
    cout << f(a,b,m,n)-f(c,d,m,n)-f(a-c,b-d,m,n) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}