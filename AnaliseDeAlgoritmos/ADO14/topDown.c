#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int memo[MAX];

int lis_helper(int arr[], int n, int *max_ref) {
    if (memo[n] != -1) {
        return memo[n];
    }

    int res, max_ending_here = 1; 

    for (int i = 0; i < n; i++) {
        res = lis_helper(arr, i, max_ref);
        if (arr[i] < arr[n] && res + 1 > max_ending_here) {
            max_ending_here = res + 1;
        }
    }

    if (*max_ref < max_ending_here) {
        *max_ref = max_ending_here;
    }

    return memo[n] = max_ending_here;
}

int lis_top_down(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        memo[i] = -1;
    }

    int max = 1;
    lis_helper(arr, n - 1, &max);
    return max;
}

int main() {
    int arr[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("LIS comprimento (Top-Down): %d\n", lis_top_down(arr, n));
    return 0;
}
