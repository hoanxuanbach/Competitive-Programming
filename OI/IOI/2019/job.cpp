#include "job.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct frac{
    ll a,b;
	int id;
    frac(ll a=-1,ll b=-1,int id=-1):a(a),b(b),id(id){}
    friend bool operator<(frac x,frac y){
        if(x.a*y.b!=x.b*y.a) return x.a*y.b<x.b*y.a;
        else return x.id<y.id;
    }
    friend bool operator>(frac x,frac y){
        if(x.a*y.b!=x.b*y.a) return x.a*y.b>x.b*y.a;
        else return x.id>y.id;
    }
};

ll scheduling_cost(std::vector<int> p, std::vector<int> U, std::vector<int> D){
	int n=(int)p.size();
	vector<ll> A(n),B(n);
	for(int i=0;i<n;i++) A[i]=D[i],B[i]=U[i];

	vector<int> par(n);
	iota(par.begin(),par.end(),0);
	function<int(int)> findpar = [&](int u){
		if(u!=par[u]) return par[u]=findpar(par[u]);
		return u;
	};

	ll ans=A[0]*B[0];
	set<frac> ss;
	for(int i=1;i<n;i++) ss.insert(frac(A[i],B[i],i)),ans+=A[i]*B[i];

	while(!ss.empty()){
		int u=ss.begin()->id;ss.erase(ss.begin());
		int x=findpar(p[u]);
		if(x) ss.erase(frac(A[x],B[x],x));
		ans+=A[x]*B[u];
		B[x]+=B[u];A[x]+=A[u];par[u]=x;
		if(x) ss.insert(frac(A[x],B[x],x));
	}
	return ans;
}
