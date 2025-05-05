#include <stdio.h>
#include <stdlib.h>

void merge(int* nums1, int m, int* nums2, int n) {
    int p1 = m - 1;
    int p2 = n - 1;
    int p = m + n - 1;

    while (p1 >= 0 && p2 >= 0) {
        if (nums1[p1] < nums2[p2]) {
            nums1[p--] = nums2[p2--];
        } else {
            nums1[p--] = nums1[p1--];
        }
    }

    while (p2 >= 0) {
        nums1[p--] = nums2[p2--];
    }
}

int main() {
    int m, n;
    scanf("%d", &m);
    int* nums1 = (int*)malloc((m + 20) * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &nums1[i]);
    }

    scanf("%d", &n);
    int* nums2 = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums2[i]);
    }

    merge(nums1, m, nums2, n);

    for (int i = 0; i < m + n; i++) {
        printf("%d\n", nums1[i]);
    }
    printf("\n");

    free(nums1);
    free(nums2);

    return 0;
}