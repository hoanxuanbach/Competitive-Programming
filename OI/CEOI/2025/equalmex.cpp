#include<bits/stdc++.h>
using namespace std;

std::vector<int> solve(int n, std::vector<int>& v, int q, std::vector<std::pair<int,int>> &qq)
{
	int A=0;
	for(int i=0;i<n;i++) A=max(A,v[i]),v[i]--;	
	//for(int i=0;i<q;i++) for(int j=qq[i].first;j<=qq[i].second;j++) cout << v[j] << ' ';
	vector<int> res(q);
	auto cal = [&](vector<int> &L,vector<int> &R){

		vector<int> tree(4*(A+1),n);
		function<void(int,int,int,int,int)> update = [&](int l,int r,int id,int x,int val){
			if(l==r){
				tree[id]=val;
				return;
			}
			int mid=(l+r)>>1;
			if(x<=mid) update(l,mid,id<<1,x,val);
			else update(mid+1,r,id<<1|1,x,val);
			tree[id]=max(tree[id<<1],tree[id<<1|1]);
		};
		function<int(int,int,int,int)> get = [&](int l,int r,int id,int x){
			if(l==r) return tree[id];
			int mid=(l+r)>>1;
			if(x<=mid) return get(l,mid,id<<1,x);
			else return max(tree[id<<1],get(mid+1,r,id<<1|1,x));
		};

		vector<int> last(A+1,n);
		for(int i=n-1;i>=0;i--){
			R[i]=last[v[i]]-1;last[v[i]]=i;
			update(0,A,1,v[i],i);
			L[i]=get(0,A,1,v[i]);
		}
	};
	vector<int> lx(n),rx(n),ly(n),ry(n);
	cal(lx,rx);
	reverse(v.begin(),v.end());
	cal(ly,ry);
	reverse(v.begin(),v.end());
	reverse(ly.begin(),ly.end());
	reverse(ry.begin(),ry.end());
	for(int i=0;i<n;i++) swap(ly[i],ry[i]),ly[i]=n-1-ly[i],ry[i]=n-1-ry[i];

	for(int i=0;i<n;i++){
		if(lx[i]>rx[i]) lx[i]=n,rx[i]=0;
		if(ly[i]>ry[i]) ly[i]=n,ry[i]=0; 
	}

	int k=0;
	vector<int> tree(4*n,0);
	function<void(int,int,int,int)> fix = [&](int l,int r,int id,int x){
		if(l==r){
			tree[id]^=1;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) fix(l,mid,id<<1,x);
		else fix(mid+1,r,id<<1|1,x);
		tree[id]=tree[id<<1]|tree[id<<1|1];
	};
	int pos=0;
	function<void(int,int,int,int,int)> get = [&](int l,int r,int id,int tl,int tr){
		if(tr<l || r<tl || !tree[id]) return;
		if(l==r){
			qq.push_back({pos,l});k++;
			//cout << pos << ' ' << l << '\n';
			return;
		}
		int mid=(l+r)>>1;
		get(l,mid,id<<1,tl,tr);get(mid+1,r,id<<1|1,tl,tr);
	};
	vector<vector<int>> add(n);
	for(int i=0;i<n;i++){
		if(ly[i]<=ry[i]){
			add[ry[i]].push_back(i);
			if(ly[i]) add[ly[i]-1].push_back(i);
		}
	}
	for(int i=n-1;i>=0;i--){
		pos=i;
		for(int id:add[i]) fix(0,n-1,1,id);
		if(lx[i]<=rx[i]) get(0,n-1,1,lx[i],rx[i]);
	}
	
	vector<vector<int>> f(n);
	vector<int> mex(q+k);

	tree.assign(4*(A+1),n);
	function<void(int,int,int,int,int)> update = [&](int l,int r,int id,int x,int val){
		if(l==r){
			tree[id]=val;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) update(l,mid,id<<1,x,val);
		else update(mid+1,r,id<<1|1,x,val);
		tree[id]=max(tree[id<<1],tree[id<<1|1]);
	};
	function<int(int,int,int,int)> query = [&](int l,int r,int id,int x){
		if(l==r) return l;
		int mid=(l+r)>>1;
		if(tree[id<<1]>x) return query(l,mid,id<<1,x);
		else return query(mid+1,r,id<<1|1,x);
	};
	for(int i=0;i<q+k;i++){
		//cerr << i << ' ' << qq[i].first << ' ' << qq[i].second << endl;
		assert(qq[i].first>=0 && qq[i].first<n);
		f[qq[i].first].push_back(i);
	}
	
	for(int i=n-1;i>=0;i--){
		update(0,A,1,v[i],i);
		for(int id:f[i]) mex[id]=query(0,A,1,qq[id].second);
	}

	vector<vector<int>> g(A+1);
	for(int i=0;i<q+k;i++){
		//cout << "range " << qq[i].first << ' ' << qq[i].second << ' ' << mex[i] << '\n';
		if(mex[i]) g[mex[i]].push_back(i);
		else if(i<q) res[i]=qq[i].second-qq[i].first+1;
	}
	assert(k<=2*n);
	
	for(int t=1;t<=A;t++){
		//cout << "mex " << t << endl;
		vector<int> com;
		reverse(g[t].begin(),g[t].end());
		for(int id:g[t]){
			com.push_back(qq[id].first);
			com.push_back(qq[id].second+1);
		}
		sort(com.begin(),com.end());
		com.erase(unique(com.begin(),com.end()),com.end());
		int sz=(int)com.size();
		vector<vector<int>> ff(sz);
		
		for(int id:g[t]){
			qq[id].first=lower_bound(com.begin(),com.end(),qq[id].first)-com.begin();
			qq[id].second=lower_bound(com.begin(),com.end(),qq[id].second+1)-com.begin()-1;
			if(qq[id].first<=qq[id].second) ff[qq[id].second].push_back(id);
		}
		int tt=sz;
		vector<int> par(sz),cnt(sz);
		iota(par.begin(),par.end(),0);
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
		for(int i=0;i<sz;i++) pq.push({i-1,i});
		for(int i=0;i<sz;i++){
			//cout << "mex " << t << ' ' << i << endl;
			for(int id:ff[i]){
				auto [l,r]=qq[id];
				//cout << l << ' ' << r << ' ' << id << endl;
				
				if(id>=q){
					int x=tt;tt++;
					cnt.push_back(1);
					par.push_back(x);
					while(!pq.empty() && pq.top().first<l){
						int y=pq.top().second;pq.pop();
						par[y]=x;
					}
					pq.push({r,x});
				}
				else{
					function<pair<int,int>(int)> findpar = [&](int u){
						if(u!=par[u]){
							pair<int,int> x=findpar(par[u]);
							cnt[u]+=x.second;par[u]=x.first;
							return pair<int,int>{x.first,cnt[u]};
						}
						return pair<int,int>{u,0};
					};
					pair<int,int> val=findpar(l);
					res[id]=cnt[val.first]+val.second;
				}
				
			}
		}
	}
	return res;
}
