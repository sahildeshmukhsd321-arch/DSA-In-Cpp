
#include <iostream>
#include <string>
using namespace std;

struct Contact {
    string name;
    string phone;
    string address;
    Contact* next;
};

Contact* head = NULL;

// Add a new contact
void addContact() {
    Contact* newContact = new Contact;

    cout << "Enter Name: ";
    getline(cin >> ws, newContact->name);

    cout << "Enter Phone Number: ";
    getline(cin, newContact->phone);

    cout << "Enter Address: ";
    getline(cin, newContact->address);

    newContact->next = NULL;

    if (head == NULL) {
        head = newContact;
    } else {
        Contact* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newContact;
    }

    cout << "Contact added successfully!\n";
}

// Display all contacts
void displayContacts() {
    if (head == NULL) {
        cout << "No contacts available.\n";
        return;
    }

    Contact* temp = head;

    while (temp != NULL) {
        cout << "\nName: " << temp->name;
        cout << "\nPhone: " << temp->phone;
        cout << "\nAddress: " << temp->address;
        cout << "\n----------------------\n";

        temp = temp->next;
    }
}

// Search a contact by name
void searchContact() {
    string name;
    cout << "Enter name to search: ";
    getline(cin >> ws, name);

    Contact* temp = head;

    while (temp != NULL) {
        if (temp->name == name) {
            cout << "Contact Found!\n";
            cout << "Name: " << temp->name << "\n";
            cout << "Phone: " << temp->phone << "\n";
            cout << "Address: " << temp->address << "\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Contact not found.\n";
}

// Delete a contact by name
void deleteContact() {
    string name;
    cout << "Enter name to delete: ";
    getline(cin >> ws, name);

    Contact* temp = head;
    Contact* prev = NULL;

    while (temp != NULL && temp->name != name) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Contact not found.\n";
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
    cout << "Contact deleted successfully!\n";
}

int main() {
    int choice;

    do {
        cout << "\n--- Contact Management System ---\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            break;
        }

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    // Free remaining memory
    while (head != NULL) {
        Contact* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
