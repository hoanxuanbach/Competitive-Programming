#include "tree.h"
#include "tree.cpp"
#include <cstdio>
#include <cassert>

#include <vector>

int main() {
	int N;
	assert(scanf("%d", &N) == 1);
	std::vector<int> F(N);
	F[0] = -1;
	for (int i = 1; i < N; ++i) {
		assert(scanf("%d", &F[i]) == 1);
	}
	std::vector<int> ans = compute(N, F);
	if (ans.size() != static_cast<size_t>(N - 1)) {
		printf("-1\n");
	}
	else {
		for (int i = 0; i < N - 1; ++i) {
			printf("%d", ans[i]);
			if (i < N - 2) {
				printf(" ");
			}
			else {
				printf("\n");
			}
		}
	}
	return 0;
}
