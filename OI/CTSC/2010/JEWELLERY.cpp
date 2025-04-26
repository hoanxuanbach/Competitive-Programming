// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define ll long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
const int maxn=50005;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,m;
string C;
vector<int> edge[maxn];
bool used[maxn];
// Each node represents an endpos-equivalent class
// Each class consists of some consecutive suffixes of the longest substring in it
// The suffix corresponding to minlen - 1 can be obtained by following the suffix link and looking at the longest substring in it
// Adjacency_Type: array<int, X> or map<Char_Type, int> where X is the size of the alphabet
template<class Char_Type, class Adjacency_Type>
struct suffix_automaton{
	// Begin States
    vector<Char_Type> S;
	vector<int> max_len{0}; // Length of the longest string in the class.
	vector<int> link{-1};
	vector<int> firstpos{-1}; // Index of the first occurences of the strings in the class.
	vector<int> is_clone{false};
	vector<Adjacency_Type> next{{}};
	// End States
	int new_state(int l, int sl, int fp, bool c, const Adjacency_Type &adj){
		max_len.push_back(l);
		link.push_back(sl);
		firstpos.push_back(fp);
		is_clone.push_back(c);
		next.push_back(adj);
		return (int)max_len.size() - 1;
	}
	int last = 0;
	void extend(const vector<Char_Type> &s){
	    S=s;
		for(auto c: s) extend(c);
	}
	void extend(Char_Type c){
	    S.push_back(c);
		int cur = new_state(max_len[last] + 1, -1, max_len[last], false, {}), p = last;
		while(~p && !next[p][c]) next[p][c] = cur, p = link[p];
		if(!~p) link[cur] = 0;
		else{
			int q = next[p][c];
			if(max_len[p] + 1 == max_len[q]) link[cur] = q;
			else{
				int clone = new_state(max_len[p] + 1, link[q], firstpos[q], true, next[q]);
				while(~p && next[p][c] == q) next[p][c] = clone, p = link[p];
				link[q] = link[cur] = clone;
			}
		}
		last = cur;
		count.clear();
		inv_link.clear();
	}
	int next_state(int u, Char_Type c){
		assert(0 <= u && u < (int)next.size());
		while(u && !next[u][c]) u = link[u];
		if(next[u][c]) u = next[u][c];
		return u;
	}
	pair<int, int> next_state(int u, int len, Char_Type c){
		assert(0 <= u && u < (int)next.size());
		while(u && !next[u][c]) u = link[u], len = max_len[u];
		if(next[u][c]) u = next[u][c], ++ len;
		return {u, len};
	}
	int size() const{ // # of states
		return (int)max_len.size();
	}
	int min_len(int u) const{ // length of the shortest string in the endpos equivalent class
		return u ? max_len[link[u]] + 1 : 0;
	}
	vector<int> terminals() const{
		vector<int> t;
		for(auto u = last; ~u; u = link[u]) t.push_back(u);
		return t;
	}
	vector<int> count; // # of occurrences of substring represented by each states in the string. Calling extend invalidates the array.
	vector<vector<int>> inv_link;
	vector<Adjacency_Type> son;

	void precalc(){
		int sz = (int)size();
		count.assign(sz, 0);
		inv_link.assign(sz, {});
		son.assign(sz,{});
		for(auto u = 1; u < sz; ++ u) inv_link[link[u]].push_back(u);
		auto dfs = [&](auto self, int u)->void{
			count[u] = !is_clone[u];
			for(auto v: inv_link[u]){
				self(self, v);
				count[u] += count[v];
				son[u][S[firstpos[v]-max_len[u]]]=v;
			}
		};
		dfs(dfs, 0);
	}
	vector<int> find_all_occurrences(int u){
		assert(!count.empty() && u < size());
		vector<int> res;
		auto dfs = [&](auto self, int u)->void{
			if(!is_clone[u]) res.push_back(firstpos[u]);
			for(auto v: inv_link[u]) self(self, v);
		};
		dfs(dfs, u);
		return res;
	}

	vector<int> num;
    void reset_num(){
        int sz=(int)size();
        num.assign(sz,0);
    }
    void calc_num(){
        auto dfs = [&](auto self, int u)->void{
			for(auto v: inv_link[u]){
                num[v]+=num[u];
				self(self, v);
			}
		};
		dfs(dfs, 0);
    }
    void dfsB(int u,int p,int pos,int len){
        if(max_len[pos]==len) pos=son[pos][C[u]-'a'];
        else if(S[firstpos[pos]-len]!=C[u]-'a') pos=0;
        if(!pos) return;
        num[pos]++;
        for(int v:edge[u]){
            if(v==p || used[v]) continue;
            dfsB(v,u,pos,len+1);
        }
    }
};

int B;
string S;

ll ans=0;
suffix_automaton<int,array<int,26>> S1,S2;
int P1[maxn],P2[maxn];
int sz,child[maxn];

int par[maxn];
vector<int> cc;
void dfs(int u,int p){
    cc.push_back(u);
    par[u]=p;
    for(int v:edge[u]){
        if(v==p || used[v]) continue;
        dfs(v,u);
    }
}

void dfs2(int u,int p,int pos,int val){
    //cerr << u << ' ' << p << ' ' << pos << ' ' << val << '\n';
    pos=S1.next[pos][C[u]-'a'];
    if(!pos) return;
    ans+=S1.count[pos]*val;
    for(int v:edge[u]){
        if(v==p || used[v]) continue;
        dfs2(v,u,pos,val);
    }
}

void cal(int u,char p){
    cc.clear();
    dfs(u,-1);
    //cerr << "cal " << u << ' ' << p << '\n';
    for(int v:cc){
        int pos=0;
        bool check=true;
        if(p!='#'){
            while(v!=-1){
                pos=S1.next[pos][C[v]-'a'];
                if(!pos) check=false;
                v=par[v];
            }
            pos=S1.next[pos][p-'a'];
            if(!pos) check=false;
            v=u;
        }
        //cerr << v << ' ' << pos << '\n';
        if(check) dfs2(v,-1,pos,(p=='#'?1:-1));
    }
}

void calB(int u,char p){
    S1.reset_num();
    S2.reset_num();
    int pos1=0,pos2=0;
    if(p!='#'){
        pos1=S1.son[0][p-'a'];
        pos2=S2.son[0][p-'a'];
        if(!pos1) return;
    }
    S1.dfsB(u,-1,pos1,p!='#');
    S2.dfsB(u,-1,pos2,p!='#');
    S1.calc_num();
    S2.calc_num();
    int val=(p=='#'?1:-1);
    for(int i=0;i<m;i++) ans+=1LL*val*S1.num[P1[i]]*S2.num[P2[i]];
}

void dfs_sz(int u,int p){
    child[u]=1;
    for(int v:edge[u]){
        if(v==p || used[v]) continue;
        dfs_sz(v,u);
        child[u]+=child[v];
    }
}
int findcen(int u,int p){
    for(int v:edge[u]){
        if(v==p || used[v]) continue;
        if(child[v]>sz/2) return findcen(v,u);
    }
    return u;
}

void decompose(int u){
    //cout << "decompose " << u << '\n';
    dfs_sz(u,-1);sz=child[u];
    if(sz<=B){
        cal(u,'#');
        return;
    }
    int x=findcen(u,-1);dfs_sz(x,-1);
    calB(x,'#');used[x]=true;
    for(int v:edge[x]){
        if(used[v]) continue;
        if(child[v]<=B) cal(v,C[x]);
        else calB(v,C[x]);
    }
    for(int v:edge[x]) if(!used[v]) decompose(v);
}

void solve(){
    cin >> n >> m;B=sqrt(n)+1;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;u--;v--;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    cin >> C >> S;
    for(int i=0;i<m;i++){
        S1.extend(S[i]-'a');
        P1[i]=S1.last;
    }
    S1.precalc();
    for(int i=m-1;i>=0;i--){
        S2.extend(S[i]-'a');
        P2[i]=S2.last;
    }
    S2.precalc();
    decompose(0);
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
