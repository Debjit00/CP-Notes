// 1. Create a linked list data. add three nodes. create respective links. display all the data from all three nodes from the first node. using c++
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

// Linked list data: 10 20 30


// 2. Implement a singly linked list using menu driven approach to performs the following
#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
};

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// Function to insert a node at the beginning
void insertAtBeginning(Node*& head, int data) {
    Node* newNode = createNode(data);
    newNode->next = head;
    head = newNode;
    cout << "Node inserted at the beginning.\n";
}

// Function to insert a node at the end
void insertAtEnd(Node*& head, int data) {
    Node* newNode = createNode(data);
    if (head == nullptr) {
        head = newNode;  // If list is empty, new node becomes the head
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;  // Traverse to the end of the list
        }
        current->next = newNode;  // Insert the node at the end
    }
    cout << "Node inserted at the end.\n";
}

// Function to delete a node with a specific value
void deleteNode(Node*& head, int data) {
    if (head == nullptr) {
        cout << "List is empty. Cannot delete.\n";
        return;
    }

    if (head->data == data) {
        Node* temp = head;
        head = head->next;  // Update the head
        delete temp;  // Free memory
        cout << "Node deleted.\n";
        return;
    }

    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr && current->data != data) {
        prev = current;
        current = current->next;  // Traverse the list
    }

    if (current == nullptr) {
        cout << "Node not found.\n";
        return;
    }

    prev->next = current->next;
    delete current;  // Free memory
    cout << "Node deleted.\n";
}

// Function to display the list
void displayList(Node* head) {
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL\n";
}

// Main function with a menu-driven approach
int main() {
    Node* head = nullptr;  // Initialize the head of the list to null
    int choice, data;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert at beginning\n";
        cout << "2. Insert at end\n";
        cout << "3. Delete node\n";
        cout << "4. Display list\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter data to insert: ";
                cin >> data;
                insertAtBeginning(head, data);
                break;

            case 2:
                cout << "Enter data to insert: ";
                cin >> data;
                insertAtEnd(head, data);
                break;

            case 3:
                cout << "Enter data to delete: ";
                cin >> data;
                deleteNode(head, data);
                break;

            case 4:
                cout << "Linked List: ";
                displayList(head);
                break;

            case 5:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
/*
Output:
Menu:
1. Insert at beginning
2. Insert at end
3. Delete node
4. Display list
5. Exit
Enter your choice: 1
Enter data to insert: 10
Node inserted at the beginning.

Menu:
1. Insert at beginning
2. Insert at end
3. Delete node
4. Display list
5. Exit
Enter your choice: 2
Enter data to insert: 20
Node inserted at the end.

Menu:
1. Insert at beginning
2. Insert at end
3. Delete node
4. Display list
5. Exit
Enter your choice: 4
Linked List: 10 -> 20 -> NULL

Menu:
1. Insert at beginning
2. Insert at end
3. Delete node
4. Display list
5. Exit
Enter your choice: 5
Exiting...
*/
