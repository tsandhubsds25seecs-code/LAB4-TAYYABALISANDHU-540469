// lab4Dsa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
using namespace std;

// ============================================================
//  Song class — one node of the doubly linked list
// ============================================================
class Song {
public:
    int id;
    string name;
    int minutes;
    int seconds;
    Song* prev;    // points to the previous song
    Song* next;    // points to the next song

    // Constructor
    Song(int i, string n, int m, int s) {
        id = i;
        name = n;
        minutes = m;
        seconds = s;
        prev = NULL;
        next = NULL;
    }

    // Print duration in mm:ss format
    void showDuration() {
        cout << minutes << ":";
        if (seconds < 10) cout << "0";   // pad with leading zero
        cout << seconds;
    }
};

// ============================================================
//  Playlist class — manages the list of songs
// ============================================================
class Playlist {
public:
    Song* head;
    Song* tail;
    Song* current;   // song currently playing

    // Constructor — empty playlist
    Playlist() {
        head = NULL;
        tail = NULL;
        current = NULL;
    }

    // Destructor — free all memory when program ends
    ~Playlist() {
        Song* temp = head;
        while (temp != NULL) {
            Song* nextSong = temp->next;
            delete temp;
            temp = nextSong;
        }
    }

    // ---------------------------------------------------------
    // 1. Add Song at the end
    // ---------------------------------------------------------
    void addSong(int id, string name, int minutes, int seconds) {
        // Check duration is valid
        if (minutes < 0 || seconds < 0 || seconds > 59) {
            cout << "Invalid duration! Seconds must be 0-59.\n";
            return;
        }

        Song* newSong = new Song(id, name, minutes, seconds);

        if (head == NULL) {
            // First song in the playlist
            head = newSong;
            tail = newSong;
            current = newSong;
        }
        else {
            // Attach at the end
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }

        cout << "Song add: " << name << "(";
        newSong->showDuration();
        cout << ")\n";
    }
    // delete song by id
    void deleteSong(int id){
        Song* temp = head;
        //finding the song
        while (temp != NULL && temp->id != id) {
            temp = temp->next;
        }
        if (temp == NULL) {
            cout << "Song with id " << id << " not found " << endl;
            return;
        }
        if (temp == head) {
            head = temp->next;
        }
        if (temp == tail) {
            tail = temp -> prev;
        }
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
        if (current == temp) {
            if (temp->next != NULL)
                current = temp->next;
            else
                current = head;

        }
        if (head != NULL) head->prev = NULL;
        if (tail != NULL) tail->next = NULL;

        cout << "Song [" << id << "] " << temp->name << " deleted.\n";
        delete temp;
    }
    void displayForward() {
        if (head == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        cout << "\nPlaylist (Forward):\n";
        Song* temp = head;
        while (temp != NULL) {
            cout << "  ID: " << temp->id
                << " | Name: " << temp->name
                << " | Duration: ";
            temp->showDuration();
            cout << "\n";
            temp = temp->next;
        }
        cout << "\n";
    }
    void displayBackward() {
        if (tail == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        cout << "\nPlaylist (Backward):\n";
        Song* temp = tail;
        while (temp != NULL) {
            cout << "  ID: " << temp->id
                << " | Name: " << temp->name
                << " | Duration: ";
            temp->showDuration();
            cout << "\n";
            temp = temp->prev;
        }
        cout << "\n";
    }
    // 5. Search Song by ID

    void searchSong(int id) {
        Song* temp = head;

        while (temp != NULL) {
            if (temp->id == id) {
                cout << "Found: ID=" << temp->id
                    << ", Name=" << temp->name
                    << ", Duration=";
                temp->showDuration();
                cout << "\n";
                return;
            }
            temp = temp->next;
        }

        cout << "Song with ID " << id << " not found.\n";
    }
    void playNext() {
        if (current == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        if (current->next != NULL)
            current = current->next;
        else
            current = head;   // go back to first song

        cout << "Now playing: " << current->name << " (";
        current->showDuration();
        cout << ")\n";
    }
    void playPrevious() {
        if (current == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        if (current->prev != NULL)
            current = current->prev;
        else
            current = tail;   // go to last song

        cout << "Now playing: " << current->name << " (";
        current->showDuration();
        cout << ")\n";
    }
    void reversePlaylist() {
        if (head == NULL || head->next == NULL) {
            cout << "Nothing to reverse.\n";
            return;
        }

        Song* temp = NULL;
        Song* curr = head;

        // Swap prev and next of every node
        while (curr != NULL) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;   // move using old next
        }

        // Swap head and tail
        temp = head;
        head = tail;
        tail = temp;

        cout << "Playlist reversed.\n";
    }
};
int main() {
    Playlist pl;
    int choice, id, min, sec;
    string name;

    do {
        cout << "\n===== PLAYLIST MENU =====\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Forward\n";
        cout << "4. Display Backward\n";
        cout << "5. Search Song\n";
        cout << "6. Play Next\n";
        cout << "7. Play Previous\n";
        cout << "8. Reverse Playlist\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Song ID: ";
            cin >> id;
            cin.ignore();  // clear the newline
            cout << "Enter Song Name: ";
            getline(cin, name);
            cout << "Enter Minutes: ";
            cin >> min;
            cout << "Enter Seconds: ";
            cin >> sec;
            pl.addSong(id, name, min, sec);
        }
        else if (choice == 2) {
            cout << "Enter Song ID to delete: ";
            cin >> id;
            pl.deleteSong(id);
        }
        else if (choice == 3) {
            pl.displayForward();
        }
        else if (choice == 4) {
            pl.displayBackward();
        }
        else if (choice == 5) {
            cout << "Enter Song ID to search: ";
            cin >> id;
            pl.searchSong(id);
        }
        else if (choice == 6) {
            pl.playNext();
        }
        else if (choice == 7) {
            pl.playPrevious();
        }
        else if (choice == 8) {
            pl.reversePlaylist();
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
