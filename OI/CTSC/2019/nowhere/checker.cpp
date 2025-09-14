#include "testlib.h"
#define iri inf.readInt
#define ori ouf.readInt
typedef long long ll;
const int N = 10000 + 1, INF = (1 << 30) - 1;
int type, n, W, H, w[N], h[N], l[N], r[N], b[N], t[N];
void check1() {
    for (int i = 1; i <= n; ++i) {
        int c = ori(1, 1);
        l[i] = ori(0, INF);
        b[i] = ori(0, INF);
        int dir = ori(0, 1);
        if (dir == 0) {
            r[i] = l[i] + w[i];
            t[i] = b[i] + h[i];
        } else {
            r[i] = l[i] + h[i];
            t[i] = b[i] + w[i];
        }
        for (int j = 1; j < i; ++j)
            quitif(l[i] < r[j] && l[j] < r[i] && b[i] < t[j] && b[j] < t[i],
             _wa, "Output is invalid. r_%d intersects with r_%d.", j, i);
        if (r[i] >= W)
            W = r[i];
        if (t[i] >= H)
            H = t[i];
    }
    ll val = 1LL * W * H;
    int score = 0;
    for (int i = 1; i <= 10; ++i) {
        ll a = ans.readLong();
        if (val <= a)
            score = i;
    }
    if (score == 0)
        quitf(_wa, "Wrong Answer. W = %d, H = %d, val = %lld", W, H, val);
    else if (score == 10)
        quitf(_ok, "Accepted. W = %d, H = %d, val = %lld", W, H, val);
    else
        quitp(score * 10, "Partially Correct. W = %d, H = %d, val = %lld", W, H, val);
}

void check2() {
    int val = 0;
    for (int i = 1; i <= n; ++i) {
        int c = ori(0, 1);
        if (c == 0)
            continue;
        ++val;
        l[i] = ori(0, INF);
        b[i] = ori(0, INF);
        int dir = ori(0, 1);
        if (dir == 0) {
            r[i] = l[i] + w[i];
            t[i] = b[i] + h[i];
        } else {
            r[i] = l[i] + h[i];
            t[i] = b[i] + w[i];
        }
        quitif(r[i] > W || t[i] > H, _wa, "Output is invalid. r_%d is out of R.", i);
        for (int j = 1; j < i; ++j)
            if(r[j])
                quitif(l[i] < r[j] && l[j] < r[i] && b[i] < t[j] && b[j] < t[i],
                 _wa, "Output is invalid. r_%d intersects with r_%d.", j, i);
    }
    int score = 0;
    for(int i = 1; i <= 10; ++i) {
        int a = ans.readInt();
        if (val >= a)
            score = i;
    }
    if (score == 0)
        quitf(_wa, "Wrong Answer. val = %d", val);
    else if (score == 10)
        quitf(_ok, "Accepted. val = %d", val);
    else
        quitp(score * 10, "Partially Correct. val = %d", val);
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    type = iri(), n = iri();
    if (type == 2)
        W = iri(), H = iri();
    for (int i = 1; i <= n; ++i)
        w[i] = iri(), h[i] = iri();
    if (type == 1)
        check1();
    else
        check2();
}