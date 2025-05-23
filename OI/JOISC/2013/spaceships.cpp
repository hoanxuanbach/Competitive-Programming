#include<bits/stdc++.h>
using namespace std;

template<class node>
struct link_cut_tree{
	bool connected(int u, int v){
		return connected(&data[u], &data[v]);
	}
	bool connected(node *u, node *v){
		return lca(u, v) != NULL;
	}
	int depth(int u){
		return depth(&data[u]);
	}
	int depth(node *u){
		access(u);
		return size(u->ch[0]);
	}
	int root(int u){
		return root(&data[u]) - &data[0];
	}
	node *root(node *u){
		access(u);
		while(u->ch[0]) u = u->ch[0], u->push();
		return access(u), u;
	}
	// Returns the k-th parent on path to root
	int ancestor(int u, int k){
		return ancestor(&data[u], k) - &data[0];
	}
	node *ancestor(node *u, int k){
		k = depth(u) - k;
		assert(k >= 0);
		for(; ; u->push()){
			int _size = size(u->ch[0]);
			if(_size == k) return access(u), u;
			if(_size < k) k -= _size + 1, u = u->ch[1];
			else u = u->ch[0];
		}
		assert(0);
	}
	int lca(int u, int v){
	    if(!connected(u,v)) return -2;
		return lca(&data[u], &data[v]) - &data[0];
	}
	node *lca(node *u, node *v){
		if(u == v) return u;
		access(u), access(v);
		if(!u->p) return NULL;
		u->splay();
		return u->p ?: u;
	}
	// Make u the parent of v
	void link(int u, int v){
		link(&data[u], &data[v]);
	}
	void link(node *u, node *v){
		assert(!connected(u, v));
		make_root(v);
		access(u);
		set_link(v, u, 0);
		v->refresh();
	}
	// Cut u from its parent
	void cut(int u){
		cut(&data[u]);
	}
	void cut(node *u){
		access(u);
		u->ch[0]->p = NULL;
		u->ch[0] = NULL;
		u->refresh();
	}
	// Assumes u, v are adjacent in tree
	void cut(int u, int v){
		cut(&data[u], &data[v]);
	}
	void cut(node *u, node *v){
		cut(depth(u) > depth(v) ? u : v);
	}
	// Make u root of LCT component
	void make_root(int u){
		make_root(&data[u]);
	}
	void make_root(node *u){
		access(u);
		u->reverse();
		access(u);
		assert(!u->ch[0] && !u->ch[1]);
	}
	// Put u on the preferred path then splay it (right subtree is empty)
	void access(int u){
		access(&data[u]);
	}
	void access(node *u){
		for(node *v = u, *pre = NULL; v; v = v->p){
			v->splay(); // now refresh virtual children
			/*if(pre) v->template refresh_virtual<false>(pre);
			if(v->ch[1]) v->template refresh_virtual<true>(v->ch[1]);*/
			v->ch[1] = pre;
			v->refresh();
			pre = v;
		}
		u->splay();
		assert(!u->ch[1]);
	}
	node *operator[](int i){
		return &data[i];
	}
	int operator[](node *u){
		return u - &data[0];
	}
	vector<node> data;
	link_cut_tree(int n): data(n){ }
};
template<class ptr>
struct splay_tree{
	ptr ch[2] = {}, p = {};
	bool rev = false;
	int _size = 1;
	splay_tree(){ }
	friend int size(ptr u){
		return u ? u->_size : 0;
	}
	virtual void refresh(){
		_size = 1 + size(ch[0]) + size(ch[1]);
	}
	virtual void push(){
		if(rev){
			if(ch[0]) ch[0]->reverse();
			if(ch[1]) ch[1]->reverse();
			rev = false;
		}
	}
	virtual void reverse(){
		rev ^= true;
		swap(ch[0], ch[1]);
	}
	int dir(){
		if(!p) return -2; // root of LCT component
		if(p->ch[0] == this) return 0; // left child
		if(p->ch[1] == this) return 1; // right child
		return -1; // root of current splay tree
	}
	bool is_root(){
		return dir() < 0;
	}
	friend void set_link(ptr u, ptr v, int d){
		if(v) v->p = u;
		if(d >= 0) u->ch[d] = v;
	}
	// Assumes p and p->p propagated
	void rotate(){
		assert(!is_root());
		int x = dir(); ptr g = p;
		set_link(g->p, static_cast<ptr>(this), g->dir());
		set_link(g, ch[x ^ 1], x);
		set_link(static_cast<ptr>(this), g, x ^ 1);
		g->refresh();
	}
	// Bring the node to the top
	void splay(){
		while(!is_root() && !p->is_root()){
			p->p->push(), p->push(), push();
			dir() == p->dir() ? p->rotate() : rotate();
			rotate();
		}
		if(!is_root()) p->push(), push(), rotate();
		push();
		refresh();
	}
};
/*
struct node: splay_tree<node *>{
	using splay_tree::ch;
	int val = 0, id = -1;
	long long aux_sum = 0;
	array<int, 2> aux_max{0, -1};
	node(): splay_tree(){ }
	void refresh() override{
		splay_tree::refresh();
		aux_sum = val;
		aux_max = {val, id};
		if(ch[0]){
			aux_sum += ch[0]->aux_sum;
			ctmax(aux_max, ch[0]->aux_max);
		}
		if(ch[1]){
			aux_sum += ch[1]->aux_sum;
			ctmax(aux_max, ch[1]->aux_max);
		}
	}
	void apply(auto lazy){

	}
	template<bool add>
	void refresh_virtual(node* v){

	}
	void reverse() override{
		splay_tree::reverse();

	}
	// Make sure push fix the node (don't call splay_tree::refresh)
	void push() override{
		splay_tree::push();

	}
};
*/
struct node: splay_tree<node *>{
	int size = 1; // includes itself, auxiliary subtrees, and virtual subtrees
	int virtual_size = 0; // includes virtual subtrees
	long long val = 0;
	long long subtr_sum = 0; // includes itself, auxiliary subtrees, and virutal subtrees
	long long virtual_subtr_sum = 0; // includes virtual subtrees
	long long auxiliary_lazy = 0;
	long long virtual_lazy = 0;
	node(){ }
	// there must be no lazy propagation
	void refresh() override{
		splay_tree::refresh();
		assert(auxiliary_lazy == 0);
		subtr_sum = val + virtual_subtr_sum;
		size = 1 + virtual_size;
		for(auto u: ch) if(u){
			subtr_sum += u->subtr_sum;
			size += u->size;
		}
	}
	template<bool add>
	void refresh_virtual(node *u){
		if(!add) u->apply(virtual_lazy);
		virtual_subtr_sum += (add ? 1 : -1) * u->subtr_sum;
		virtual_size += (add ? 1 : -1) * u->size;
		if(add) u->apply(-virtual_lazy);
	}
	void push() override{
		splay_tree::push();
		if(auxiliary_lazy){
			for(auto u: ch) if(u) u->apply(auxiliary_lazy);
			auxiliary_lazy = 0;
		}
	}
	void reverse() override{
		splay_tree::reverse();

	}
	void apply(long long lazy){
		val += lazy;
		subtr_sum += lazy * size;
		virtual_subtr_sum += lazy * virtual_size;
		auxiliary_lazy += lazy;
		virtual_lazy += lazy;
	}
};

void solve(){
    int n,q;cin >> n >> q;
    link_cut_tree<node> LCT(n);
    vector<int> nxt(n);
    for(int i=0;i<q;i++){
        int id,u;cin >> id >> u;
        if(id==1){
            int v;cin >> v;
            u--;v--;nxt[u]=v;
            LCT.link(v,u);
        }
        else if(id==2){
            u--;
            LCT.cut(u);
        }
        else{
            int v;cin >> v;
            u--;v--;
            cout << LCT.lca(u,v)+1 << '\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
