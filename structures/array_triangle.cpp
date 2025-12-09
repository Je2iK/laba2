#include "array_triangle.h"

long long maxPyramidHeight(Array<Block>& blocks) {
    int n = blocks.size();

    sort(&blocks[0], &blocks[0] + n, [](const Block& a, const Block& b) {
        if (a.width == b.width)
            return a.height < b.height;
        return a.width < b.width;
    });

    Array<long long> dp(n);
    for (int i = 0; i < n; ++i)
        dp.push_back(blocks[i].height);

    long long maxHeight = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (blocks[j].width < blocks[i].width) {
                dp[i] = max(dp[i], dp[j] + blocks[i].height);
            }
        }
        maxHeight = max(maxHeight, dp[i]);
    }

    return maxHeight;
}