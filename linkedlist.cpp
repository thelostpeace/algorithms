#include "linkedlist.h"
#include <climits>

/**
 * reverse a linked list
 */
void reverse_linkedlist(node_t **head) {
    node_t *new_head = NULL;
    node_t *cur = *head;
    while (cur != NULL) {
        node_t *p = cur->next;
        cur->next = new_head;
        new_head = cur;
        cur = p;
    }

    *head = new_head;
}

/**
 * move last node to head
 */
void move_last_to_first(node_t **head) {
    node_t *cur = *head;
    node_t *last = cur->next;
    node_t *new_last = cur;
    while (last != NULL) {
        new_last = cur;
        cur = cur->next;
        last = last->next;
    }
    new_last->next = NULL;
    cur->next = cur == *head ? NULL : *head;
    *head = cur;
}

void linkedlist_swap(node_t *prev_a, node_t *a, node_t *prev_b, node_t *b) {
    if (a == b)
        return;
    if (b == NULL) {
        if (prev_a) 
            prev_a->next = a->next;
            prev_b->next = a;
            a->next = NULL;
    } else {
        if (prev_a)
            prev_a->next = b;
        node_t *temp = b->next;
        if (prev_b != a) {
            b->next = a->next;
            a->next = temp;
            prev_b->next = a;
        } else {
            a->next = temp;
            b->next = a;
        }
    }
}

void quicksort_partition(node_t *begin, node_t *end, node_t *prev_begin) {
    if (begin == end) {
        return;
    }
    node_t *pivot = begin;
    node_t *last_small = pivot;
    node_t *prev_last_small = NULL;
    node_t *first_big = last_small->next;
    while (first_big != end) {
        if (first_big->val < pivot->val) {
            last_small = last_small->next;
            first_big = first_big->next;
            if (prev_last_small == NULL) {
                prev_last_small = pivot;
            } else {
                prev_last_small = prev_last_small->next;
            }
        } else {
            break;
        }
    }
    node_t *cur = first_big != end ? first_big->next : end;
    node_t *prev_cur = first_big;
    while (cur != end) {
        if (cur->val < pivot->val) {
            linkedlist_swap(last_small, first_big, prev_cur, cur);
            node_t *temp = cur->next;
            prev_last_small = last_small;
            last_small = cur;
            cur = first_big->next;
            prev_cur = first_big;
            first_big = temp;
        } else {
            cur = cur->next;
            prev_cur = prev_cur->next;
        }
    }
    linkedlist_swap(prev_begin, pivot, prev_last_small, last_small);
    quicksort_partition(last_small, pivot, prev_begin);
    quicksort_partition(pivot->next, end, pivot);
}

void quicksort_linkedlist(node_t **head) {
    node_t *cur = *head;
    node_t *last = *head;
    int min_ = INT_MAX;
    while (last != NULL) {
        if (last->val < min_) {
            cur = last;
            min_ = cur->val;
        }
        last = last->next;
    }
    quicksort_partition(*head, last, NULL);
    *head = cur;
}


int main(int argc, char **argv) {
    vector<int> data = {79, 81, 77, 86, 42, 62, 36, 26, 97, 19};
    gen_vector(data, 0, 100, 10);
    print_vector(data);
    node_t *head;
    create_linkedlist(&head, data);
    print_linkedlist(head);

    //reverse_linkedlist(&head);
    //move_last_to_first(&head);
    quicksort_linkedlist(&head);
    print_linkedlist(head);

    return 0;
}
