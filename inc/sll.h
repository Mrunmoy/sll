#ifndef SLL_H
#define SLL_H

/**
 *  @file sll.h
 *  @author championsurfer3044
 *  @date 17 Jun 2019 
 *  @brief 
 *
 *  LICENSE:-
 *  The MIT License (MIT)
 *  Copyright (c) 2019 Mrunmoy Samal
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom
 *  the Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall
 *  be included in all copies or substantial portions of the
 *  Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 *  OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
*----------------------------------------------------------------------
*   Include Files
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Public Data Types
*----------------------------------------------------------------------
*/

// SLL node definition
typedef struct sll_node_t {
    void *value;
    size_t size;
    struct sll_node_t *next;
}sll_node_t;

// SLL List definition
typedef struct sll_t {
    sll_node_t *head;
    sll_node_t *tail;
    size_t count;
} sll_t;

/*
*----------------------------------------------------------------------
*   Public Constants (const)
*----------------------------------------------------------------------
*/


/*
*----------------------------------------------------------------------
*   Public Function Prototypes
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Externs
*----------------------------------------------------------------------
*/
extern sll_node_t  *sll_node_new(void *val, size_t size);
extern void         sll_node_free(sll_node_t *item);
extern sll_t       *sll_new(void);
extern void         sll_free(sll_t *item);
extern bool         sll_append(struct sll_t *list, void *value, size_t size);
extern bool         sll_contains(struct sll_t *list, void *value, size_t size);
extern bool         sll_has_loop(struct sll_t *list);
extern void         sll_remove(struct sll_t *list, void *value, size_t size);
extern size_t       sll_traverse(struct sll_t *list, void *a[]);
extern size_t       sll_reverse_traverse(struct sll_t *list, void *a[]);
extern sll_node_t * sll_find_loop_start(struct sll_t *list);
extern sll_node_t * sll_find_intersection(struct sll_t *list1, struct sll_t *list2);
extern sll_node_t * sll_get_kth_node(struct sll_t *list,  int k);
extern bool         sll_is_palindrome(sll_t *list);
extern void         sll_remove_duplicates(sll_t *list);
#ifdef __cplusplus
}
#endif

#endif //SLL_H
