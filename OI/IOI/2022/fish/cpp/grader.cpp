#include "fish.h"
#include "fish.cpp"
#include <cassert>
#include <cstdio>

#include <vector>

int main() {
  int N, M;
  assert(2 == scanf("%d %d", &N, &M));

  std::vector<int> X(M), Y(M), W(M);
  for (int i = 0; i < M; ++i) {
    assert(3 == scanf("%d %d %d", &X[i], &Y[i], &W[i]));
  }

  long long result = max_weights(N, M, X, Y, W);
  printf("%lld\n", result);
  return 0;
}
/*
3 4
0 1 1
1 1 2
2 1 2
1 0 1
*/
/*
5 4
0 2 5
1 1 2
4 4 1
3 3 3
*/
