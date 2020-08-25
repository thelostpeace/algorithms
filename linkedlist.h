#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
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
