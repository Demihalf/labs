#include <iostream>
using namespace std;

typedef int ListType;

struct Node {
    ListType value;
    Node* next;
};

// Inserts the value right after n.
// Returns node, if it's not null, creates node otherwise.
Node * list_insert(Node * node, ListType v) {
    Node * n = new Node;
    n->value = v;
    if (node) { 
        n->next = node->next; 
        node->next = n;
        
        return node;
    } else {
        n->next = NULL;
        return n;
    }
}

void list_delete(Node * head) {
    if (!head) return;
    list_delete(head->next);
    delete head;
}

bool list_has_value(Node * head, ListType val) {
    if (!head) return false;
    return (head->value == val) || list_has_value(head->next, val);
}

int main() {
    Node * head = NULL;

    cout << "Enter values: ";
    ListType v;
    while (cin >> v) {
        head = list_insert(head, v);
    }

    cin.clear();

    cout << "Enter search query: ";
    ListType e;
    cin >> e;

    cout << (list_has_value(head, e) ? "Value found" : "Value not found") << endl;

    list_delete(head);
    head = NULL;

    return 0;
}
