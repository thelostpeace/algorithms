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

/***
 * time complexity O(N), space complexity O(1)
 */
void morris_in_order_traversal(treenode_t *root) {
    treenode_t *cur = root;
    treenode_t *par = NULL, *subroot;
    while (cur != NULL) {
        subroot = cur;
        if (cur->left) {
            cur = cur->left;
            par = cur;
            while (par->right) {
                par = par->right;
            }
            par->right = subroot; 
            subroot->left = NULL;
            //print_binary_tree(cur);
        } else {
            cout << cur->val << " ";
            cur = cur->right;
        }
    }
    cout << endl;
}

void inorder_with_stack(treenode_t *root) {
    stack<treenode_t *> s;
    s.push(root);
    treenode_t *left = NULL;
    while (!s.empty()) {
        treenode_t *top = s.top();
        if (top->left && left != top->left) {
            s.push(top->left);
            left = top->left;
            continue;
        } 
        cout << top->val << " ";
        s.pop();
        if (top->right) {
            s.push(top->right);
            left = top;
        } 
    }
    cout << endl;
}

/**
 * replace each node with sum of it's inorder predecessor and successor
 */
void inorder_sum(treenode_t *root) {
    stack<treenode_t *> s;
    s.push(root);
    // store left child, so it is not visited again
    treenode_t *left = NULL;
    // store the left value of add
    int pre = 0;
    // this is the node we need to calculate value
    treenode_t *calc = NULL;
    while (!s.empty()) {
        treenode_t *top = s.top();
        // go left until there is no left child
        if (top->left) {
            if (left != top->left) {
                s.push(top->left);
                left = top->left;
                continue;
            } else {
                left = top;
            }
        } 
        // pop left or root
        s.pop();
        // push right child if it has one
        if (top->right) {
            s.push(top->right);
        }
        // init calc with the first inorder node
        if (calc == NULL) {
            calc = top;
            continue;
        }
        // calculate calc node value
        int temp = calc->val;
        calc->val = pre + top->val;
        pre = temp;
        calc = top;
    }
    // calcualte the last node
    calc->val = pre;
}

#define IS_VISITED(x, table) (x == NULL || table[0] == x || table[1] == x)

stack<treenode_t *> find_path(treenode_t *root, int target) {
    stack<treenode_t *> s;
    if (root == NULL)
        return s;
    s.push(root);
    vector<treenode_t *> visited = {NULL, NULL};
    while (!s.empty()) {
        treenode_t *top = s.top();
        if (top->val == target) {
            return s;
        }
        if (!IS_VISITED(top->left, visited)) 
            s.push(top->left);
        else if (!IS_VISITED(top->right, visited))
            s.push(top->right);
        else {
            s.pop();
            visited[0] = visited[1];
            visited[1] = top;
        }
    }

    return s;
}

treenode_t *lowest_common_ancestor(treenode_t *root, int a, int b) {
    stack<treenode_t *> patha = find_path(root, a);
    stack<treenode_t *> pathb = find_path(root, b);

    stack<treenode_t *> patha_;
    while (!patha.empty()) {
        patha_.push(patha.top());
        patha.pop();
    }
    stack<treenode_t *> pathb_;
    while (!pathb.empty()) {
        pathb_.push(pathb.top());
        pathb.pop();
    }

    treenode_t *common = NULL;
    while (!patha_.empty() && !pathb_.empty()) {
        if (patha_.top() != pathb_.top()) {
            break;
        } else {
            common = patha_.top();
            patha_.pop();
            pathb_.pop();
        }
    }
    return common;
}

int main(int argc, char **argv) {
    //vector<int> data = {79, 81, 77, 86, 42, 62, 36, 26, 97, 19};
    //gen_vector(data, 0, 100, 10);
    //print_vector(data);
    //node_t *head;
    //create_linkedlist(&head, data);
    //print_linkedlist(head);

    //reverse_linkedlist(&head);
    //move_last_to_first(&head);
    //quicksort_linkedlist(&head);
    //print_linkedlist(head);
    
    vector<int> data = {1, 2, 3, 4, 5, 6, 7};
    //gen_vector(data, 0, 100, 10);
    print_vector(data);
    treenode_t *root;
    create_binary_tree(&root, data);
    print_binary_tree(root);
    morris_in_order_traversal(root);
    //inorder_with_stack(root);
    //inorder_sum(root);
    //print_binary_tree(root);
    //treenode_t *common = lowest_common_ancestor(root, 4, 6);
    //cout << (common == NULL ? -1 : common->val) << endl;

    return 0;
}
