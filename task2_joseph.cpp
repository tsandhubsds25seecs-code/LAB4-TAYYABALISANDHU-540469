// lab4Dsa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//joseph problem
#include <iostream>
using namespace std;

//circular lists

class Person {
public:
    int id;           // person's number (1, 2, 3, ...)
    Person* next;     // points to the next person

    // Constructor
    Person(int i) {
        id = i;
        next = NULL;
    }
};
class Josephus {
public:
    Person* head;     // first person in the circle

    // Constructor
    Josephus() {
        head = NULL;
    }

    // Destructor — free all remaining nodes
    ~Josephus() {
        if (head == NULL) return;

        Person* temp = head;
        // First, break the circle so the loop ends
        Person* last = head;
        while (last->next != head) {
            last = last->next;
        }
        last->next = NULL;   // now it's a normal list

        // Delete every node
        while (temp != NULL) {
            Person* nextPerson = temp->next;
            delete temp;
            temp = nextPerson;
        }
    }
    void createCircle(int N) {
        if (N <= 0) {
            cout << "Number of people must be greater than 0.\n";
            return;
        }

        head = new Person(1);
        Person* temp = head;

        for (int i = 2; i <= N; i++) {
            Person* newPerson = new Person(i);
            temp->next = newPerson;
            temp = newPerson;
        }

        // Last person points back to head → circular!
        temp->next = head;

        cout << "Circle created with " << N << " people.\n";
    }
    void displayCircle() {
        if (head == NULL) {
            cout << "Circle is empty.\n";
            return;
        }

        cout << "Circle: ";
        Person* temp = head;
        do {
            cout << temp->id;
            temp = temp->next;
            if (temp != head) cout << " -> ";
        } while (temp != head);
        cout << " -> (back to " << head->id << ")\n";
    }
    void eliminate(int k) {
        if (head == NULL) {
            cout << "Circle is empty. Create it first.\n";
            return;
        }
        if (k <= 0) {
            cout << "Step count k must be greater than 0.\n";
            return;
        }

        // Special case: only one person
        if (head->next == head) {
            cout << "Elimination order: (none)\n";
            cout << "Survivor: " << head->id << "\n";
            return;
        }

        // We need 'prev' to remove a node.
        // Start 'prev' at the last node (the one pointing to head).
        Person* prev = head;
        while (prev->next != head) {
            prev = prev->next;
        }
        Person* curr = head;    // start counting from person 1

        cout << "Elimination order: ";

        // Keep going until only one person remains
        while (curr->next != curr) {

            // Count k-1 steps (because curr itself is step 1)
            for (int count = 1; count < k; count++) {
                prev = curr;
                curr = curr->next;
            }

            // Eliminate 'curr'
            cout << curr->id << " ";

            // Remove curr from the circle
            prev->next = curr->next;
            Person* toDelete = curr;
            curr = curr->next;      // resume from the next person
            delete toDelete;
        }

        // Now only one node remains
        cout << "\nSurvivor: " << curr->id << "\n";
    }
};
int main() {
    Josephus j;
    int N, k;

    cout << "===== JOSEPHUS PROBLEM SIMULATION =====\n";

    cout << "Enter number of people (N): ";
    cin >> N;

    cout << "Enter step count (k): ";
    cin >> k;

    j.createCircle(N);
    j.displayCircle();
    j.eliminate(k);

    return 0;
}
