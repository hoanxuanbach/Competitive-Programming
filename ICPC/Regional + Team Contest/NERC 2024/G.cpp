#include <iostream>
using namespace std;
struct CITY {
    long long int x, y, c, d, a, h;
} t[800005], hhh;
struct LAZY {
    long long int lazy, lazyx, lazyy;
} lazy[800005];
int a[200005], f[200005], g[200005];
CITY Merge(CITY aa, CITY bb) {
    CITY res;
    res.x = max(aa.x, bb.x);
    res.y = max(aa.y, bb.y);
    res.c = aa.c + bb.c;
    res.d = aa.d + bb.d;
    res.a = max(aa.a, bb.a);
    if (aa.a < bb.a) res.h = bb.h;
    else res.h = aa.h;
    return res;
}
void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v].x = t[v].c = f[tl];
        t[v].y = t[v].d = g[tl];
        t[v].a = a[tl];
        t[v].h = tl;
        lazy[v].lazy = lazy[v].lazyx = lazy[v].lazyy = 0;
        return;
    }
    int mid = (tl + tr) / 2;
    build(v * 2, tl, mid);
    build(v * 2 + 1, mid + 1, tr);
    t[v] = Merge(t[v * 2], t[v * 2 + 1]);
}
void push(int v, int tl, int tr) {
    int mid = (tl + tr) / 2;
    lazy[v * 2].lazyx += lazy[v].lazyx;
    lazy[v * 2].lazyy += lazy[v].lazyy;
    lazy[v * 2].lazy += lazy[v].lazy;
    t[v * 2].c += lazy[v].lazyx * (mid - tl + 1);
    t[v * 2].d += lazy[v].lazyy * (mid - tl + 1);
    t[v * 2].a += lazy[v].lazy;
    t[v * 2].x += lazy[v].lazyx;
    t[v * 2].y += lazy[v].lazyy;
    lazy[v * 2 + 1].lazyx += lazy[v].lazyx;
    lazy[v * 2 + 1].lazyy += lazy[v].lazyy;
    lazy[v * 2 + 1].lazy += lazy[v].lazy;
    t[v * 2 + 1].c += lazy[v].lazyx * (tr - mid);
    t[v * 2 + 1].d += lazy[v].lazyy * (tr - mid);
    t[v * 2 + 1].a += lazy[v].lazy;
    t[v * 2 + 1].x += lazy[v].lazyx;
    t[v * 2 + 1].y += lazy[v].lazyy;
    lazy[v].lazy = lazy[v].lazyx = lazy[v].lazyy = 0;
}
void update(int v, int tl, int tr, int l, int r, int flag) {
    if (l > r) return;
    if (tl == l && tr == r) {
        if (flag == 0) {
            lazy[v].lazyx++;
            t[v].c += r - l + 1;
            t[v].x++;
        }
        else if (flag == 1) {
            lazy[v].lazyy++;
            t[v].d += r - l + 1;
            t[v].y++;
        }
        else {
            lazy[v].lazy++;
            t[v].a++;
        }
        return;
    }
    push(v, tl, tr);
    int mid = (tl + tr) / 2;
    update(v * 2, tl, mid, l, min(r, mid), flag);
    update(v * 2 + 1, mid + 1, tr, max(l, mid + 1), r, flag);
    t[v] = Merge(t[v * 2], t[v * 2 + 1]);
}
CITY sum(int v, int tl, int tr, int l, int r) {
    if (l > r) return hhh;
    if (tl == l && tr == r) {
        return t[v];
    }
    push(v, tl, tr);
    int mid = (tl + tr) / 2;
    return Merge(sum(v * 2, tl, mid, l, min(r, mid)), sum(v * 2 + 1, mid + 1, tr, max(l, mid + 1), r));
}
int res, res2, fl = 0, fl2 = 0;
void why(int v, int tl, int tr, int l, int r, int x, int flag) {
    if (l > r) return;
    if (tl == l && tr == r) {
            //cout << tl << " " << tr << " " << t[v].a << endl;
        if (t[v].a <= x) return;
        if (flag == 0 && fl != 0) return;
        if (flag == 1 && fl2 != 0) return;
        if (tl == tr) {
            if (flag == 0) {
                fl = 1;
                res = tl;
            }
            else {
                fl2 = 1;
                res2 = tl;
            }
            return;
        }
        push(v, tl, tr);
        int mid = (tl + tr) / 2;
        why(v * 2, tl, mid, l, min(r, mid), x, flag);
        why(v * 2 + 1, mid + 1, tr, max(l, mid + 1), r, x, flag);
        return;
    }
    push(v, tl, tr);
    int mid = (tl + tr) / 2;
    why(v * 2, tl, mid, l, min(r, mid), x, flag);
    why(v * 2 + 1, mid + 1, tr, max(l, mid + 1), r, x, flag);
}
void why2(int v, int tl, int tr, int l, int r, int x, int flag) {
    if (l > r) return;
    if (tl == l && tr == r) {
        //cout << tl << " " << tr << " " << t[v].y << " " << x << " " << res2 << endl;
        if (t[v].a <= x) return;
        if (flag == 0 && fl != 0) return;
        if (flag == 1 && fl2 != 0) return;
        if (tl == tr) {
            if (flag == 0) {
                fl = 1;
                res = tl;
            }
            else {
                fl2 = 1;
                res2 = tl;
            }
            return;
        }
        push(v, tl, tr);
        int mid = (tl + tr) / 2;
        why2(v * 2 + 1, mid + 1, tr, max(l, mid + 1), r, x, flag);
        why2(v * 2, tl, mid, l, min(r, mid), x, flag);
        return;
    }
    push(v, tl, tr);
    int mid = (tl + tr) / 2;
    why2(v * 2 + 1, mid + 1, tr, max(l, mid + 1), r, x, flag);
    why2(v * 2, tl, mid, l, min(r, mid), x, flag);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    long long int n, q, c = 0;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        c += a[i];
        f[i] = max(f[i - 1], a[i]);
    }
    for (int i = n; i >= 1; i--) {
        g[i] = max(g[i + 1], a[i]);
    }
    for (int i = 1; i <= n * 4; i++) t[i] = hhh;
    build(1, 1, n);
    int hh = t[1].h;
    cout << sum(1, 1, n, 1, hh - 1).c + sum(1, 1, n, hh + 1, n).d - c + t[1].a << '\n';
    for (int jj = 0; jj < q; jj++) {
        int x, y;
        cin >> x >> y;
        update(1, 1, n, x, y, 2);
        CITY h = sum(1, 1, n, 1, x - 1), k = sum(1, 1, n, y + 1, n), g = sum(1, 1, n, x, y);
        res = y + 1, res2 = y;
        fl = fl2 = 0;
        why(1, 1, n, x, y, h.a, 0);
        why(1, 1, n, y + 1, n, g.a - 1, 1);
        if (fl2 == 0) res2 = n + 1;
        update(1, 1, n, res, y, 0);
        if (res != y + 1) update(1, 1, n, y + 1, res2 - 1, 0);
        res = x - 1, res2 = x;
        fl = fl2 = 0;
        why2(1, 1, n, x, y, k.a, 0);
        why2(1, 1, n, 1, x - 1, g.a - 1, 1);
        if (fl2 == 0) res2 = 0;
        update(1, 1, n, x, res, 1);
        if (res != x - 1) update(1, 1, n, res2 + 1, x - 1, 1);
        c += y - x + 1;
        int hh = t[1].h;
        cout << sum(1, 1, n, 1, hh - 1).c + sum(1, 1, n, hh + 1, n).d - c + t[1].a << '\n';
    }
}
