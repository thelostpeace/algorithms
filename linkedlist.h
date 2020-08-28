#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

typedef struct node_t {
    int val;
    node_t *next;
} node_t;

void create_linkedlist(node_t **head, vector<int> &data) {
    node_t *cur = NULL;
    *head = NULL;
    for (int i = data.size() - 1; i >=0; --i) {
        *head = new node_t;
        (*head)->val = data[i];
        (*head)->next = cur;
        cur = *head;
    }
}

void print_linkedlist(node_t *head) {
    while (head != NULL) {
        cout << head->val << " => ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

void gen_vector(vector<int> &data, int low=0, int high=100, int size=10) {
    data.clear();
    int count = 0;
    srand(time(NULL));
    while (count < size) {
        int val = rand() % (high - low) + low;
        data.push_back(val);
        ++count;
    }
}

void print_vector(vector<int> &data) {
    cout << "[ ";
    for (int i = 0; i < data.size(); ++i) {
        cout << data[i] << " ";
    }
    cout << "]" << endl;
}

typedef struct treenode_t {
    int val;
    treenode_t *left;
    treenode_t *right;
    treenode_t() {
        left = NULL;
        right = NULL;
    }
} treenode_t;

void create_binary_tree(treenode_t **root, vector<int> &data) {
    if (data.empty()) {
        *root = NULL;
    } else {
        *root = new treenode_t;
        (*root)->val = data[0];
    }
    queue<treenode_t *> q;
    q.push(*root);
    for (int i = 1; i < data.size(); ++i) {
        treenode_t *node = new treenode_t;
        node->val = data[i];
        treenode_t *front = q.front();
        if (front->left == NULL) {
            front->left = node;
        } else if (front->right == NULL) {
            front->right = node;
            q.pop();
        }
        q.push(node);
    }
}

void print_binary_tree(treenode_t *root) {
    if (root == NULL) {
        cout << "#" << endl;
        return;
    } 
    queue<treenode_t *> q;
    q.push(root);
    q.push(NULL);
    while (!q.empty()) {
        treenode_t *front = q.front();
        if (front == NULL) {
            q.pop();
            if (q.front()) {
                cout << "# ";
                q.push(NULL);
            }
            continue;
        } 
        if (front->left) {
            q.push(front->left);
        } 
        if (front->right) {
            q.push(front->right);
        }
        cout << front->val << " ";
        q.pop();
    }
    cout << endl;
}

typedef struct rbtreenode_t {
    enum {
        red,
        black
    } c;
    int val;
    rbtreenode_t *left;
    rbtreenode_t *right;
    rbtreenode_t *parent;
    rbtreenode_t() {
        c = red;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
} rbtreenode_t;

void left_rotate(rbtreenode_t **root, rbtreenode_t **x) {
    rbtreenode_t *parent = (*x)->parent;
    rbtreenode_t *right = (*x)->right;
    if (right == NULL) {
        return;
    }
    (*x)->parent = right;
    right->parent = parent;
    (*x)->right = right->left;
    right->left = (*x);
    if (parent) {
        parent->right = right;
    }
    if ((*x)->right) {
        (*x)->right->parent = *x;
    }
    if (right->parent == NULL) {
        *root = right;
    }
}

void right_rotate(rbtreenode_t **root, rbtreenode_t **y) {
    rbtreenode_t *parent = (*y)->parent;
    rbtreenode_t *left = (*y)->left;
    if (left == NULL) {
        return;
    }
    left->parent = parent;
    (*y)->parent = left;
    left->right = *y;
    (*y)->left = left->right;
    if (parent) {
        parent->left = left;
    }
    if ((*y)->left) {
        (*y)->left->parent = *y;
    }
    if (left->parent == NULL) {
        *root = left;
    }
}

rbtreenode_t *bst_insert(rbtreenode_t **root, int val) {
    rbtreenode_t *x = new rbtreenode_t;
    x->val = val;
    rbtreenode_t *cur = *root;
    rbtreenode_t *stop = NULL;
    while (cur) {
        stop = cur;
        if (cur->val > val) {
            cur = cur->left;
        } else if (cur->val < val) {
            cur = cur->right;
        }
    }
    if (stop == NULL) {
        *root = x;
    } else if (stop->val < val) {
        stop->right = x;
        x->parent = stop;
    } else {
        stop->left = x;
        x->parent = stop;
    }

    return x;
}

void rbtree_insert(rbtreenode_t **root, int val) {
    rbtreenode_t *x = bst_insert(root, val);
    // parent is red
    while (x != *root && x->parent->c == rbtreenode_t::red) {
        rbtreenode_t *grand_parent = x->parent ? x->parent->parent : NULL;
        rbtreenode_t *uncle = NULL;
        if (grand_parent) {
            uncle = x->parent == grand_parent->left ? grand_parent->right : grand_parent->left;
            // parent is red and uncle is red
            if (uncle && uncle->c == rbtreenode_t::red) {
                x->parent->c = rbtreenode_t::black;
                uncle->c = rbtreenode_t::black;
                grand_parent->c = rbtreenode_t::red;
                x = grand_parent;
            } else { // parent is red and uncle is black
                // 1. x is left left of grandparent
                if (grand_parent->left && x == grand_parent->left->left) {
                    right_rotate(root, &grand_parent);
                    grand_parent->c = rbtreenode_t::red;
                    grand_parent->parent->c = rbtreenode_t::black;
                } else if (grand_parent->left && x == grand_parent->left->right) {
                    left_rotate(root, &(x->parent));
                    right_rotate(root, &grand_parent);
                    grand_parent->c = rbtreenode_t::red;
                    grand_parent->parent->c = rbtreenode_t::black;
                } else if (grand_parent->right && x == grand_parent->right->right) {
                    left_rotate(root, &grand_parent);
                    grand_parent->c = rbtreenode_t::red;
                    grand_parent->parent->c = rbtreenode_t::black;
                } else if (grand_parent->right && x == grand_parent->right->left) {
                    right_rotate(root, &(x->parent));
                    left_rotate(root, &grand_parent);
                    grand_parent->c = rbtreenode_t::red;
                    grand_parent->parent->c = rbtreenode_t::black;
                }
                break;
            }
        }
    }
    if (x->parent == NULL) {
        x->c = rbtreenode_t::black;
    }
}

tbtreenode_t *bst_find(rbtreenode_t *root, int val) {
    while (root) {
        if (root->val == val) {
            break;
        } else if(root->val < val) {
            root = root->right;
        } else {
            root = root->left;
        }
    }

    return root;
}

#define IS_LEFT_CHILD(x) (x->parent && x == x->parent->left)
void bst_delete(rbtreenode_t **root, int val) {
    rbtreenode_t *x = bst_find(*root, val);
    if (x->left == NULL && x->right == NULL) {
        if (x == *root) {
            *root = NULL;
        } else {
            x->parent->left = NULL;
            x->parent->right = NULL;
        }
    } else if (x->left && x->right == NULL) {
        rbtreenode_t *parent = x->parent;
        x->left->parent = parent;
        if (parent) {
            if (IS_LEFT_CHILD(x)) {
                x->parent->left = x->left;
            } else {
                x->parent->right = x->left;
            }
        } else {
            *root = x->left;
        }
    } else if (x->right && x->left == NULL) {
        rbtreenode_t *parent = x->parent;
        x->right->parent = parent;
        if (parent) {
            if (IS_LEFT_CHILD(x)) {
                x->parent->left = x->right;
            } else {
                x->parent->right = x->right;
            }
        } else {
            *root = x->right;
        }
    } else {
        rbtreenode_t *parent = x->parent;
        rbtreenode_t *newparent = x->right;
        while (newparent->left) {
            newparent = newparent->left;
        }
        if (newparent->right) {
            newparent->right->parent = newparent->parent;
        }
        newparent->left = x->left;
        newparent->parent->left = newparent->right;
        newparent->parent = parent;
        newparent->right = newparent == x->right ? newparent->right : x->right;
        if (newparent->parent == NULL) {
            *root = newparent;
        }
    }
    delete x;
    x->parent = NULL;
    x->left = NULL;
    x->right = NULL;
}

void rbtree_delete(rbtreenode_t **root, int val) {
    // too complicate 
    // if some mother fucker ask you to implement rbtree insertion or deletion
    // on paper, better just leave. It is not hard if steps given. but coding on 
    // paper is still time costing. left rotation & right rotation & standard binary
    // search tree deletion and insertion and deletion, all time costing.
    
    // rbtree insertion and deletion need at most 2 rotations. avl tree is also a good
    // one, slower on insertion and deletion than rbtree but faster on searching.
}

/***
 * Advantages of B+ trees:
 *
 * https://stackoverflow.com/questions/870218/what-are-the-differences-between-b-trees-and-b-trees
 * Because B+ trees don't have data associated with interior nodes, more keys can fit on a page of memory. Therefore, it will require fewer cache misses in order to access data that is on a leaf node.
 * The leaf nodes of B+ trees are linked, so doing a full scan of all objects in a tree requires just one linear pass through all the leaf nodes. A B tree, on the other hand, would require a traversal of every level in the tree. This full-tree traversal will likely involve more cache misses than the linear traversal of B+ leaves.
 * Advantage of B trees:
 *
 * Because B trees contain data with each key, frequently accessed nodes can lie closer to the root, and therefore can be accessed more quickly.'
 */

void print_rbtree(rbtreenode_t *root) {
    if (root == NULL) {
        cout << "#" << endl;
        return;
    } 
    queue<rbtreenode_t *> q;
    q.push(root);
    q.push(NULL);
    while (!q.empty()) {
        rbtreenode_t *front = q.front();
        if (front == NULL) {
            q.pop();
            if (q.front()) {
                cout << "# ";
                q.push(NULL);
            }
            continue;
        } 
        if (front->left) {
            q.push(front->left);
        } 
        if (front->right) {
            q.push(front->right);
        }
        cout << front->val << "|" << (front->c == rbtreenode_t::red ? "red" : "black") << " ";
        q.pop();
    }
    cout << endl;
}
