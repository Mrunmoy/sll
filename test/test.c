#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include "sll.h"

int main() {
    int a[10] = {0};
     srand(time(0));
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        a[i] = rand() % 32;
        printf("%3d ", a[i]);
    }
    printf("\n");

    sll_t *list = sll_new();
    if (list) {
        for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
            sll_append(list, &a[i], sizeof(a[i]));
        }

        void **b = (void **)malloc(list->count * sizeof(void *));
        assert(b);
        size_t n = sll_traverse(list, b);

        for (int i = 0; i < n; i++) {
            int *obj  = b[i];
            printf("%3d ", *obj);
        }
        printf("\n");

        n = sll_reverse_traverse(list, b);
        for (int i = 0; i < n; i++) {
            int *obj  = b[i];
            printf("%3d ", *obj);
        }
        printf("\n");

        printf("list has loop: %s\n", sll_has_loop(list) ? "true" : "false");

        free(b);
        sll_free(list);


        list = sll_new();

        int val = 0;
        sll_append(list, &val, sizeof(val));
        val = 0;
        sll_append(list, &val, sizeof(val));
#if 0
        val = 3;
        sll_append(list, &val, sizeof(val));
        val = 4;
        sll_append(list, &val, sizeof(val));
        val = 3;
        sll_append(list, &val, sizeof(val));
        val = 2;
        sll_append(list, &val, sizeof(val));
        val = 1;
        sll_append(list, &val, sizeof(val));
#endif
        n = sll_traverse(list, b);
        for (int i = 0; i < n; i++) {
            int *obj  = b[i];
            printf("%3d ", *obj);
        }
        printf("\n");
        printf("is palindrome: %s\n", sll_is_palindrome(list) ? "true": "false");
#if 0
        val = 5;
        sll_append(list, &val, sizeof(val));
        n = sll_traverse(list, b);
        for (int i = 0; i < n; i++) {
            int *obj  = b[i];
            printf("%3d ", *obj);
        }
        printf("\n");
        printf("is palindrome: %s\n", sll_is_palindrome(list) ? "true": "false");
#endif
#if 0
        sll_remove_duplicates(list);
        n = sll_traverse(list, b);
        for (int i = 0; i < n; i++) {
            int *obj  = b[i];
            printf("%3d ", *obj);
        }
        printf("\n");

#endif


        sll_free(list);
    }
    return 0;
}