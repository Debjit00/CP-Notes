#include <iostream>
using namespace std;

// Define a Node structure
struct Node {
    int data;      // Data part
    Node* next;    // Pointer to the next node
};

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = new Node(); // Allocate memory for a new node
    newNode->data = data;       // Assign data to the node
    newNode->next = nullptr;    // Initialize the next pointer to null
    return newNode;
}

// Function to display the data in the linked list
void displayList(Node* head) {
    Node* current = head;  // Start from the head node
    while (current != nullptr) {  // Traverse until the end of the list
        cout << current->data << " "; // Print the data
        current = current->next; // Move to the next node
    }
    cout << endl;
}

int main() {
    // Creating three nodes
    Node* first = createNode(10);  // First node with data 10
    Node* second = createNode(20); // Second node with data 20
    Node* third = createNode(30);  // Third node with data 30

    // Linking nodes
    first->next = second; // Link first node to second node
    second->next = third; // Link second node to third node

    // Display all nodes starting from the first
    cout << "Linked list data: ";
    displayList(first);

    return 0;
}
