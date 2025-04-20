#include "beechtree.h"
#include "beechtree.cpp"
#include <cassert>
#include <cstdio>

int main()
{
    int N, M;
    assert(2 == scanf("%d %d", &N, &M));
    std::vector<int> P(N);
    for (int i = 0; i < N; ++i)
        assert(1 == scanf("%d", &P[i]));
    std::vector<int> C(N);
    for (int i = 0; i < N; ++i)
        assert(1 == scanf("%d", &C[i]));

    fclose(stdin);

    std::vector<int> res = beechtree(N, M, P, C);

    int n = res.size();
    for (int i = 0; i < n; ++i)
    {
        if (i > 0)
            printf(" ");
        printf("%d", res[i]);
    }
    printf("\n");
    fclose(stdout);

    return 0;
}
