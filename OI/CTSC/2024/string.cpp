#include<bits/stdc++.h>
using namespace std; 
//#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 2e6+5;

struct suffix_automaton{
	// Begin States
	vector<int> max_len{0}; // Length of the longest string in the class
	vector<int> link{-1};
	vector<int> first_pos{-1}; // Index (of the last character) of the first occurence of the strings in the class
	vector<int> is_clone{false};
	int next[maxn][26];
	suffix_automaton(){}
	suffix_automaton(const string &s){ extend(s); }
	// End States
	int new_state(int l, int sl, int fp, bool c, int adj[]){
		max_len.push_back(l);
		link.push_back(sl);
		first_pos.push_back(fp);
		is_clone.push_back(c);
		int x=(int)max_len.size()-1;
        for(int i=0;i<26;i++) next[x][i]=adj[i];
		return x;
	}
	int last=0,empty[26];
	void extend(int c){
		int cur = new_state(max_len[last] + 1, -1, max_len[last], false,empty), p = last;
		while(~p && !next[p][c]) next[p][c] = cur, p = link[p];
		if(!~p) link[cur] = 0;
		else{
			int q = next[p][c];
			if(max_len[p] + 1 == max_len[q]) link[cur] = q;
			else{
				int clone = new_state(max_len[p] + 1, link[q], first_pos[q], true, next[q]);
				while(~p && next[p][c] == q) next[p][c] = clone, p = link[p];
				link[q] = link[cur] = clone;
			}
		}
		last = cur;
		count.clear();
		inv_link.clear();
	}
	void extend(char c){
		extend((int)(c - 'a'));
	}
	void extend(const vector<int> &s){
		for(auto c: s) extend(c);
	}
	void extend(const string &s){
		for(auto c: s) extend(c);
	}
	int next_state(int u, int c){
		assert(0 <= u && u < 26);
		while(u && !next[u][c]) u = link[u];
		if(next[u][c]) u = next[u][c];
		return u;
	}
	int next_state(int u, char c){
		return next_state(u, tolower(c) - 'a');
	}
	pair<int, int> next_state(int u, int len, int c){
		assert(0 <= u && u < 26);
		while(u && !next[u][c]) u = link[u], len = max_len[u];
		if(next[u][c]) u = next[u][c], ++len;
		return {u, len};
	}
	pair<int, int> next_state(int u, int len, char c){
		return next_state(u, len, tolower(c) - 'a');
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
	void precalc_count(){
		int sz = (int)size();
		count.assign(sz, 0), inv_link.assign(sz, {});
		for(auto u = 1; u < sz; ++ u) inv_link[link[u]].push_back(u);
		auto dfs = [&](auto self, int u)->void{
			count[u] = !is_clone[u];
			for(auto v: inv_link[u]){
				self(self, v);
				count[u] += count[v];
			}
		};
		dfs(dfs, 0);
	}
	vector<int> find_all_occurrences(int u){
		assert(!count.empty() && u < size());
		vector<int> res;
		auto dfs = [&](auto self, int u)->void{
			if(!is_clone[u]) res.push_back(first_pos[u]);
			for(auto v: inv_link[u]) self(self, v);
		};
		dfs(dfs, u);
		return res;
	}
}sam;

const int LG = 21;
int nxt[maxn][LG];

void solve(){   
    string S;cin >> S;
    int n=(int)S.length();
    reverse(S.begin(),S.end());
    
    S="#"+S;
    vector<int> f(n+1);
    for(int i=1;i<=n;i++){
        sam.extend(S[i]);
        f[i]=sam.last;
    }

    int m=(int)sam.max_len.size(),T=0;
    vector<int> L(m+1),R(m+1);
    vector<vector<int>> g(m);
    for(int i=1;i<m;i++){
        g[sam.link[i]].push_back(i);
        nxt[i][0]=sam.link[i];
    }
    for(int j=1;j<LG;j++) for(int i=0;i<m;i++) nxt[i][j]=nxt[nxt[i][j-1]][j-1];
    function<void(int)> dfs = [&](int u){
        L[u]=++T;
        for(int v:g[u]) dfs(v);
        R[u]=T;
    };
    dfs(0);

    vector<int> bit(m+1);
    auto update = [&](int x,int val){
        for(int i=x;i<=m;i+=(i&(-i))) bit[i]+=val;
    };
    auto query = [&](int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    };

    auto cal = [&](int x,int y){
        int u=f[y],d=y-x+1;
        for(int i=LG-1;i>=0;i--){
            int v=nxt[u][i];
            if(sam.max_len[v]>=d) u=v;
        }
        int val = query(R[u])-query(L[u]-1);
        //cout << x << ' ' << y << ' ' << val << '\n';
        return val;
    };

    vector<int> v;
    v.push_back(0);
    vector<int> dp(n+1);
    for(int i=1;i<=n;i++){
        update(L[f[i]],1);
        while(!v.empty()){
            dp[i]=max(dp[i],cal(v.back()+1,i)-dp[v.back()]);
            if(dp[v.back()]<dp[i]) break;
            else v.pop_back();
        }
        v.push_back(i);
    }
    cout << dp[n] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}