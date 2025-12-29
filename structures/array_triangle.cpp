#include "array_triangle.h"

// Быстрая сортировка для блоков
void quickSort(Block* arr, int left, int right) {
    if (left >= right) return;
    
    int i = left, j = right;
    Block pivot = arr[(left + right) / 2];
    
    while (i <= j) {
        while (arr[i].width < pivot.width || 
               (arr[i].width == pivot.width && arr[i].height < pivot.height)) i++;
        while (arr[j].width > pivot.width || 
               (arr[j].width == pivot.width && arr[j].height > pivot.height)) j--;
        
        if (i <= j) {
            Block temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    
    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}

long long maxPyramidHeight(Array<Block>& blocks) {
    int n = blocks.size();


    quickSort(&blocks[0], 0, n - 1);

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