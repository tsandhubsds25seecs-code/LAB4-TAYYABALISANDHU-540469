// lab4Dsa.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
using namespace std;

class BitNode {
public:
    int bit;
    BitNode* prev;
    BitNode* next;

    BitNode(int b) {
        bit = b;
        prev = NULL;
        next = NULL;
    }
};

class BinaryDLL {
public:
    BitNode* head;
    BitNode* tail;

    BinaryDLL() {
        head = NULL;
        tail = NULL;
    }

    ~BinaryDLL() {
        BitNode* temp = head;
        while (temp != NULL) {
            BitNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }

    void addBitAtEnd(int b) {
        BitNode* newNode = new BitNode(b);
        if (head == NULL) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void addBitAtFront(int b) {
        BitNode* newNode = new BitNode(b);
        if (head == NULL) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void storeBinary(string bits) {
        BitNode* temp = head;
        while (temp != NULL) {
            BitNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = tail = NULL;

        for (int i = 0; i < bits.length(); i++) {
            if (bits[i] == '0' || bits[i] == '1') {
                addBitAtEnd(bits[i] - '0');
            }
        }
    }

    void display() {
        if (head == NULL) {
            cout << "0";
            return;
        }

        int count = 0;
        BitNode* temp = head;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }

        int pad = (8 - (count % 8)) % 8;
        for (int i = 0; i < pad; i++) {
            cout << "0";
            if ((i + 1) % 8 == 0) cout << " ";
        }

        temp = head;
        int printed = pad;
        while (temp != NULL) {
            cout << temp->bit;
            printed++;
            if (printed % 8 == 0 && temp->next != NULL)
                cout << " ";
            temp = temp->next;
        }
    }

    void onesComplement() {
        BitNode* temp = head;
        while (temp != NULL) {
            temp->bit = 1 - temp->bit;
            temp = temp->next;
        }
    }

    void twosComplement() {
        onesComplement();

        BitNode* temp = tail;
        int carry = 1;

        while (temp != NULL && carry == 1) {
            int sum = temp->bit + carry;
            temp->bit = sum % 2;
            carry = sum / 2;
            temp = temp->prev;
        }

        if (carry == 1) {
            addBitAtFront(1);
        }
    }

    int toDecimal() {
        int value = 0;
        BitNode* temp = head;
        while (temp != NULL) {
            value = value * 2 + temp->bit;
            temp = temp->next;
        }
        return value;
    }

    static BinaryDLL add(BinaryDLL& a, BinaryDLL& b) {
        BinaryDLL result;
        BitNode* pa = a.tail;
        BitNode* pb = b.tail;
        int carry = 0;

        while (pa != NULL || pb != NULL || carry == 1) {
            int sum = carry;

            if (pa != NULL) {
                sum += pa->bit;
                pa = pa->prev;
            }
            if (pb != NULL) {
                sum += pb->bit;
                pb = pb->prev;
            }

            result.addBitAtFront(sum % 2);
            carry = sum / 2;
        }

        return result;
    }

    static BinaryDLL multiply(BinaryDLL& a, BinaryDLL& b) {
        BinaryDLL result;

        BinaryDLL shiftA;
        BitNode* temp = a.head;
        while (temp != NULL) {
            shiftA.addBitAtEnd(temp->bit);
            temp = temp->next;
        }

        BitNode* pb = b.tail;
        while (pb != NULL) {
            if (pb->bit == 1) {
                BinaryDLL sum = add(result, shiftA);
                result = sum;
            }
            shiftA.addBitAtEnd(0);
            pb = pb->prev;
        }

        return result;
    }
};

int main() {
    BinaryDLL num1, num2;
    string bits;
    int choice;

    do {
        cout << "\n===== BINARY ARITHMETIC MENU =====\n";
        cout << "1. Store Binary Number 1\n";
        cout << "2. Store Binary Number 2\n";
        cout << "3. Display Both Numbers\n";
        cout << "4. 1's Complement of Number 1\n";
        cout << "5. 2's Complement of Number 1\n";
        cout << "6. Add Number 1 + Number 2\n";
        cout << "7. Multiply Number 1 * Number 2\n";
        cout << "8. Convert Number 1 to Decimal\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter binary number: ";
            cin >> bits;
            num1.storeBinary(bits);
            cout << "Number 1 stored: ";
            num1.display();
            cout << "\n";
        }
        else if (choice == 2) {
            cout << "Enter binary number: ";
            cin >> bits;
            num2.storeBinary(bits);
            cout << "Number 2 stored: ";
            num2.display();
            cout << "\n";
        }
        else if (choice == 3) {
            cout << "Number 1: ";
            num1.display();
            cout << "\nNumber 2: ";
            num2.display();
            cout << "\n";
        }
        else if (choice == 4) {
            num1.onesComplement();
            cout << "1's Complement: ";
            num1.display();
            cout << "\n";
        }
        else if (choice == 5) {
            num1.twosComplement();
            cout << "2's Complement: ";
            num1.display();
            cout << "\n";
        }
        else if (choice == 6) {
            BinaryDLL sum = BinaryDLL::add(num1, num2);
            cout << "Sum: ";
            sum.display();
            cout << "  (Decimal: " << sum.toDecimal() << ")\n";
        }
        else if (choice == 7) {
            BinaryDLL product = BinaryDLL::multiply(num1, num2);
            cout << "Product: ";
            product.display();
            cout << "  (Decimal: " << product.toDecimal() << ")\n";
        }
        else if (choice == 8) {
            cout << "Decimal: " << num1.toDecimal() << "\n";
        }
        else if (choice == 0) {
            cout << "Exiting...\n";
        }
        else {
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}