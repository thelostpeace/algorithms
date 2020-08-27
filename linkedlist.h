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
