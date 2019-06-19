/**
 *  @file sll.c
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


/*
*----------------------------------------------------------------------
*   Include Files
*----------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include "../inc/sll.h"

/*
*----------------------------------------------------------------------
*   Private Defines
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Macros
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Data Types
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Public Variables
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Variables ()
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Public Constants (const)
*----------------------------------------------------------------------
*/


/*
*----------------------------------------------------------------------
*   Private Constants ()
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Function Prototypes ()
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Externs
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Functions Definitions
*----------------------------------------------------------------------
*/


/*
*----------------------------------------------------------------------
*   Exported Functions Definitions
*----------------------------------------------------------------------
*/
sll_node_t *sll_node_new(void *val, size_t size) {
    sll_node_t * item = malloc(sizeof(sll_node_t));
    if (item) {
        item->value = malloc(size);
        item->size = size;
        memcpy(item->value, val, size);
        item->next = NULL;
    }
    return item;
}

void sll_node_free (sll_node_t *item) {
    if (!item) return;
    if (item->value) free(item->value);
    free(item);
}


bool sll_append(sll_t *list, void *value, size_t size) {
    if (NULL == list || NULL == value) return false;

    sll_node_t *item = sll_node_new(value, size);
    if (NULL == list->head) {
        list->head = item;
        list->tail = item;
    }
    else {
        list->tail->next = item;
        list->tail = item;
    }
    list->count++;
    return true;
}

bool sll_contains(sll_t *list, void *value, size_t size) {
    if (NULL == list || NULL == value || 0 == list->count) return false;
    sll_node_t *runner = list->head;
    while(runner) {
        if (memcmp(runner->value, value, size) == 0) return true;
        runner = runner->next;
    }
    return false;
}

void sll_remove(sll_t *list, void *value, size_t size) {
    if (NULL == list || 0 == list->count) return;

    if (list->count == 1) {
        if (memcmp(list->head->value, value, size) == 0) {
            sll_node_free(list->head);
            list->head = NULL;
            list->tail = NULL;
            list->count = 0;
        }
        return;
    }

    sll_node_t *runner = list->head;
    while (runner->next && memcmp(runner->value, value, size) != 0) {
        runner = runner->next;
    }

    if (NULL != runner->next) {
        if (list->tail == runner->next) {
            sll_node_free(list->tail);
            list->tail = runner;
            list->tail->next = NULL;
        }
        else {
            sll_node_t *temp = runner->next;
            runner->next = runner->next->next;
            sll_node_free(temp);
        }
        list->count--;
    }
}

size_t sll_traverse(sll_t *list, void *a[]) {
    if (NULL == list || list->count == 0) return 0;
    sll_node_t *runner = list->head;
    size_t index = 0;
    while(runner) {
        a[index++] = runner->value;
        runner= runner->next;
    }
    return index;
}

size_t sll_reverse_traverse(sll_t *list, void *a[]) {
    if (NULL == list || list->count == 0) return 0;
    sll_node_t *runner = list->tail;
    size_t index = 0;
    while(runner != list->head) {
        sll_node_t *prev = list->head;
        while (prev->next != runner) prev = prev->next;
        a[index++] = runner->value;
        runner = prev;
    }
    a[index++] = runner->value; // head
    return index;
}

sll_node_t *sll_find_loop_start(sll_t *list) {
    if (NULL == list) return NULL;

    sll_node_t *fast = list->head;
    sll_node_t *slow = list->head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }

    if (fast == NULL || fast->next == NULL) return NULL;

    slow = list->head;
    while(slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return fast;
}

bool sll_has_loop(sll_t *list) {
    return (NULL != sll_find_loop_start(list));
}

sll_node_t * sll_get_kth_node(struct sll_t *list,  int k) {
    if (NULL == list) return NULL;

    sll_node_t *runner = list->head;
    while (k > 0 && runner != NULL) {
        runner = runner->next;
        k--;
    }
    return runner;
}

sll_node_t * sll_find_intersection(struct sll_t *list1, struct sll_t *list2) {
    if (NULL == list1 || NULL == list2 || list1->tail != list2->tail) return NULL;

    sll_node_t *shorter;
    sll_node_t *longer;

    // since both lists have same tail pointer, there must be a node
    // which lies exactly k nodes from  the start of longer list
    if (list1->count < list2->count) {
        shorter = list1->head;
        longer = sll_get_kth_node(list2, list2->count - list1->count);

    }
    else {
        shorter = list2->head;
        longer = sll_get_kth_node(list1, list1->count - list2->count);
    }

    while(shorter != longer) {
        shorter = shorter->next;
        longer = longer->next;
    }

    return longer;
}


static bool is_palindrome_helper(sll_node_t *head, sll_node_t **next, int length) {
    if ( NULL == head  || length <= 0) {
        *next = head;
        return true;
    }
    else if (length == 1) {
        *next = head->next;
        return true;
    }

    bool result = is_palindrome_helper(head->next, next, length - 2);
    if (!result || !*next) return result;

    result = false;
    if (head->size == (*next)->size && memcmp(head->value, (*next)->value, head->size) == 0) {
        *next = (*next)->next;
        result = true;
    }
    return result;
}

bool sll_is_palindrome(sll_t *list) {
    if (NULL == list) return false;
    sll_node_t *next = NULL;
    return is_palindrome_helper(list->head, &next, list->count);
}

sll_t *sll_create_copy(sll_t *list) {
    if (NULL == list) return false;

    sll_t *result = sll_new();
    result->count = list->count;
    sll_node_t *runner = list->head;
    while (runner) sll_append(result, runner->value, runner->size);

    return result;
}

void sll_remove_duplicates(sll_t *list) {
    if (NULL == list || 0 == list->count) return;
    sll_node_t *current = list->head;
    while(current) {
        sll_node_t *runner = current;
        while(runner->next != NULL) {
            if (runner->next->size == current->size &&
                 memcmp(runner->next->value, current->value, current->size) == 0)
            {
                sll_node_t *temp = runner->next;
                runner->next = runner->next->next;
                sll_node_free(temp);
                list->count--;
            }
            else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

sll_t *sll_new(void) {
    sll_t * item = malloc(sizeof(sll_t));
    if (item) {
        item->head  = NULL;
        item->tail  = NULL;
        item->count = 0;
    }
    return item;
}

void sll_free(sll_t *item) {
    if (NULL == item || NULL == item->head) return;
    sll_node_t *runner = item->head;
    while(runner) {
        sll_node_t *temp = runner;
        runner = runner->next;
        sll_node_free(temp);
    }
    free(item);
}


