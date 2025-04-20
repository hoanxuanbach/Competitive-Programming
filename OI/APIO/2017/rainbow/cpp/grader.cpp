#include "rainbow.h"
#include "rainbow.cpp"
#include <stdio.h>

static int RR, CC, M, Q;
static int sr, sc;
static char S[100000 + 5];

int main() {
    scanf("%d %d %d %d", &RR, &CC, &M, &Q);
    scanf("%d %d", &sr, &sc);
    if (M > 0) {
        scanf(" %s ", S);
    }

    init(RR, CC, sr, sc, M, S);

    int query;
    for (query = 0; query < Q; query++) {
        int ar, ac, br, bc;
        scanf("%d %d %d %d", &ar, &ac, &br, &bc);
        printf("%d\n", colour(ar, ac, br, bc));
    }

    return 0;
}

