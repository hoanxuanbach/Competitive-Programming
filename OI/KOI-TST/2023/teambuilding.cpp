#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define se second
#define fi first
const int maxn = 1e5+5;
const int B = 330;
int N,M,Q;
using ll = long long;
using ld = long double;

#if __cplusplus < 202002L
template <class T> int ssize(const T& a){ return a.size(); }
#endif
template <class T1, class T2> istream& operator>> (istream& in, pair <T1, T2>& a){ in >> a.first >> a.second; return in; }
template <class T> istream& operator>> (istream& in, vector <T>& a){ for (auto &x: a){ in >> x; } return in; }



template<class T, class F>
struct sparse_table{
#ifdef LOCAL
	#define ASSERT(x) assert(x)
#else
	#define ASSERT(x) 42
#endif
	int n;
	vector<vector<T>> data;
	F TT;
	T T_id;
	sparse_table(F TT, T T_id): TT(TT), T_id(T_id){ }
	sparse_table &operator=(const sparse_table &st){
		n = st.n;
		data = st.data;
		return *this;
	}
	friend void swap(sparse_table &stl, sparse_table &str){
		swap(stl.n, str.n);
		swap(stl.data, str.data);
	}
	// O(n * log(n))
	void build(const vector<T> &a){
		n = (int)a.size();
		if (ssize(data) < 1){
			data.resize(1);
		}
		data[0] = a;
		for(auto p = 1, i = 1; p << 1 <= n; p <<= 1, ++ i){
			if (ssize(data) <= i){
				data.resize(i + 1);
			}
			data[i].resize(n - (p << 1) + 1);
			for(auto j = 0; j < (int)data[i].size(); ++ j) data[i][j] = TT(data[i - 1][j], data[i - 1][j + p]);
		}
	}
	// O(1)
	T query(int l, int r) const{
		ASSERT(0 <= l && l <= r && r <= n);
		if(l == r) return T_id;
		int d = __lg(r - l);
		return TT(data[d][l], data[d][r - (1 << d)]);
	}
};
template<class T, class F>
auto make_sparse_table(F TT, T T_id){
	return sparse_table(TT, T_id);
}
template<class T>
auto make_rminq(T inf = numeric_limits<T>::max()){
	return sparse_table([&](const T &x, const T &y){ return min(x, y); }, inf);
}
template<class T>
auto make_rmaxq(T minf = numeric_limits<T>::min()){
	return sparse_table([&](const T &x, const T &y){ return max(x, y); }, minf);
}

vector<ll> build_teams(vi A1,vi B1,vi A2,vi B2,vi L1,vi R1,vi L2,vi R2) {


    N=(int)A1.size();
    M=(int)A2.size();
    Q=(int)L1.size();

    vector<ll> res(Q);
    vector<pair<ll,int>> opt(max(N,M));
    auto S = make_rmaxq(numeric_limits <pair <ll, int>>::min());

    auto C = [&](int i,int j){
        return 1LL*(A1[i]+A2[j])*(B1[i]+B2[j]);
    };
    function<void(int,int,int,int)> dnc = [&](int l,int r,int optl,int optr){
        int mid=(l+r)>>1;opt[mid]={0,-1};
        for(int i=optl;i<=optr;i++) opt[mid]=max(opt[mid],{C(mid,i),i});
        if(l<mid) dnc(l,mid-1,opt[mid].se,optr);
        if(mid<r) dnc(mid+1,r,optl,opt[mid].se);
    };
    auto solve = [&]{
        N=(int)A1.size();
        M=(int)A2.size();
        for(int l=0;l<M;l+=B){
            int r=min(l+B,M)-1;
            dnc(0,N-1,l,r);
            S.build(opt);
            for(int i=0;i<Q;i++) if(L2[i]<=l && r<=R2[i]) res[i]=max(res[i],(ll)S.query(L1[i],R1[i]+1).fi);
        }
    };
    solve();
    swap(A1,A2);
    swap(B1,B2);
    swap(L1,L2);
    swap(R1,R2);
    solve();
    for(int t=0;t<Q;t++){
        vector<int> a,b;
        for(int j=L1[t];j<=R1[t];j++){
            if(j%B==0 && j+B-1<=R1[t]) j+=B-1;
            else a.push_back(j);
        }
        for(int j=L2[t];j<=R2[t];j++){
            if(j%B==0 && j+B-1<=R2[t]) j+=B-1;
            else b.push_back(j);
        }
        if(!b.empty() && !a.empty()){
            function<void(int,int,int,int)> dnc = [&](int l,int r,int optl,int optr){
                int mid=(l+r)>>1;
                pair<ll,int> val={0,-1};
                for(int i=optl;i<=optr;i++)val=max(val,{C(a[mid],b[i]),i});
                res[t]=max(res[t],val.fi);
                if(l<mid) dnc(l,mid-1,val.se,optr);
                if(mid<r) dnc(mid+1,r,optl,val.se);
            };
            dnc(0,(int)a.size()-1,0,(int)b.size()-1);
        }
    }
	return res;
}

#undef int