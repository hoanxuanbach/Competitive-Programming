#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second

using namespace std;
const int N = (int)5e5 + 228;

struct SegmentTree {
	vector<int> tree;
	vector<int> lazy;
	int n;

	SegmentTree(int _n = 0) {
		n = _n;
		tree.assign(n * 4 + 7, 0);
		lazy.assign(n * 4 + 7, 0);
	}

	void down(int id) {
		for (int i = id * 2; i <= id * 2 + 1; ++i) {
			lazy[i] += lazy[id];
			tree[i] += lazy[id];
		}
		lazy[id] = 0;
	}

	void update(int id, int l, int r, int u, int v, int val) {
		if (l > v || r < u) return;
		if (u <= l && r <= v) {
			tree[id] += val;
			lazy[id] += val;
			return;
		}
		down(id);
		int mid = (l + r) / 2;
		update(id * 2, l, mid, u, v, val);
		update(id * 2 + 1, mid + 1, r, u, v, val);
		tree[id] = tree[id * 2] + tree[id * 2 + 1];
	}
	void update(int l, int r, int val) {
		update(1, 1, n, l, r, val);
	}

	int get(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return 0;
		if (u <= l && r <= v) return tree[id];
		down(id);
		int mid = (l + r) / 2;
		return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
	}
	int get(int l, int r) {
		return get(1, 1, n, l, r);
	}
};

struct Event {
	int l, r;
	int ul, ur;
	int tl, tr;
	Event() {
		l = r = 0;
		ul = ur = 0;
		tl = tr = -1;
	}
};

int n, a[N], h[N];
vector<int> vt1[N];
vector<int> vt2[N];
Event events[N];
SegmentTree it1;
SegmentTree it2;

void update(int l, int r, int i) {
	if (l > r) return;
	int cnt = it1.get(l, r);
	events[l].l = l, events[l].r = r;
	events[l].ul = r - cnt + 1;
	events[l].ur = r;
	events[l].tl = i;
	events[l].tr = -1;		
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	for (int i = 1; i < n; ++i) {
		cin >> h[i];
	}
	h[n] = n;

	for (int i = 1; i <= n; ++i) {
		vt1[h[i]].push_back(i);
		vt2[a[i]].push_back(i);
	}

	it1 = SegmentTree(n);
	it2 = SegmentTree(n);
	set<int> s;
	vector<Event> cans;

	events[1].l = 1, events[1].r = n, events[1].ul = n+1, events[1].ur = n + 1, events[1].tl = 0, events[1].tr = -1;
	s.insert(1);

	for (int i = n; i >= 1; --i) {
		for (int x : vt2[i]) {
			it1.update(x, x, 1);
			auto it = s.upper_bound(x);
			--it;
			int l = *it;
			Event event = events[l];
			event.tr = i + 1;
			cans.push_back(event);
			int r = event.r;

			update(l, r, i);
		}


		for (int x : vt1[i]) {
			auto it = s.upper_bound(x);
			--it;
			int l = *it;
			int r = events[l].r;
			Event event = events[l];
			event.tr = i + 1;
			cans.push_back(event);

			update(l, x, i);
			update(x + 1, r, i);
			s.insert(x + 1);
		}
	}

	for (int i = 1; i <= n; ++i) {
		if (events[i].tr == -1) {
			events[i].tr = 1;
			cans.push_back(events[i]);
		}
	}

	for (Event event: cans) {
		if (event.tl < event.tr) {
			continue;
		}
		if (event.ul > event.ur) {
			continue;
		}
		it2.update(event.ul, event.ur, event.tl - event.tr + 1);
	}

	for (int i = 1; i <= n; ++i) {
		cout << it2.get(i, i) << ' ';
	}
	cout << '\n';
}

int main() {
#ifdef LOCAL
	freopen("main.inp", "r", stdin);
	freopen("main.out", "w", stdout);
#endif
	ios::sync_with_stdio(0);
	cin.tie(0);
	int test = 1;
	// cin >> test;
	while (test--)
		solve();
	return 0;
}