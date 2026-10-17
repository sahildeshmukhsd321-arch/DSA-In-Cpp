
#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Contact {
    string name, phone, email, address;
    bool emergency;
    Contact* next;
};

Contact* head = NULL;

void addContact() {
    Contact* node = new Contact;

    cout << "Enter name: ";
    getline(cin >> ws, node->name);

    cout << "Enter phone: ";
    getline(cin, node->phone);

    Contact* temp = head;
    while (temp != NULL) {
        if (temp->phone == node->phone) {
            cout << "Duplicate phone number!\n";
            delete node;
            return;
        }
        temp = temp->next;
    }

    cout << "Enter email: ";
    getline(cin, node->email);

    cout << "Enter address: ";
    getline(cin, node->address);

    node->emergency = false;
    node->next = NULL;

    if (head == NULL) {
        head = node;
    } else {
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = node;
    }

    cout << "Contact added successfully!\n";
}

void displayContacts() {
    Contact* temp = head;

    if (temp == NULL) {
        cout << "No contacts available.\n";
        return;
    }

    while (temp != NULL) {
        cout << "\nName: " << temp->name
             << "\nPhone: " << temp->phone
             << "\nEmail: " << temp->email
             << "\nAddress: " << temp->address
             << "\nEmergency: "
             << (temp->emergency ? "Yes" : "No")
             << "\n---------------------\n";

        temp = temp->next;
    }
}

Contact* findContact(string key) {
    Contact* temp = head;

    while (temp != NULL) {
        if (temp->name == key || temp->phone == key)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void searchContact() {
    string key;
    cout << "Enter name or phone: ";
    getline(cin >> ws, key);

    Contact* temp = findContact(key);

    if (temp != NULL) {
        cout << "Contact Found!\n";
        cout << "Name: " << temp->name
             << "\nPhone: " << temp->phone
             << "\nEmail: " << temp->email
             << "\nAddress: " << temp->address << "\n";
    } else {
        cout << "Contact not found.\n";
    }
}

void updateContact() {
    string key;
    cout << "Enter name or phone to update: ";
    getline(cin >> ws, key);

    Contact* temp = findContact(key);

    if (temp == NULL) {
        cout << "Contact not found.\n";
        return;
    }

    string newPhone;
    cout << "Enter new name: ";
    getline(cin, temp->name);

    cout << "Enter new phone: ";
    getline(cin, newPhone);

    Contact* check = head;
    while (check != NULL) {
        if (check != temp && check->phone == newPhone) {
            cout << "Phone number already exists.\n";
            return;
        }
        check = check->next;
    }
    temp->phone = newPhone;

    cout << "Enter new email: ";
    getline(cin, temp->email);

    cout << "Enter new address: ";
    getline(cin, temp->address);

    cout << "Contact updated successfully!\n";
}

void deleteContact() {
    string key;
    cout << "Enter name or phone to delete: ";
    getline(cin >> ws, key);

    Contact* temp = head;
    Contact* prev = NULL;

    while (temp != NULL &&
           temp->name != key && temp->phone != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Contact not found.\n";
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    delete temp;
    cout << "Contact deleted successfully!\n";
}

void sortContacts() {
    if (head == NULL) {
        cout << "No contacts to sort.\n";
        return;
    }

    for (Contact* i = head; i->next != NULL; i = i->next) {
        for (Contact* j = i->next; j != NULL; j = j->next) {
            if (i->name > j->name) {
                swap(i->name, j->name);
                swap(i->phone, j->phone);
                swap(i->email, j->email);
                swap(i->address, j->address);
                swap(i->emergency, j->emergency);
            }
        }
    }

    cout << "Contacts sorted alphabetically.\n";
}

void markEmergency() {
    string key;
    cout << "Enter name or phone: ";
    getline(cin >> ws, key);

    Contact* temp = findContact(key);

    if (temp == NULL) {
        cout << "Contact not found.\n";
        return;
    }

    temp->emergency = !temp->emergency;
    cout << "Emergency status: "
         << (temp->emergency ? "Yes" : "No") << "\n";
}

void countContacts() {
    int count = 0;
    Contact* temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    cout << "Total contacts: " << count << "\n";
}

int main() {
    int choice;

    do {
        cout << "\n--- SMART CONTACT MANAGEMENT ---\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Update Contact\n";
        cout << "5. Delete Contact\n";
        cout << "6. Sort Contacts\n";
        cout << "7. Mark Emergency Contact\n";
        cout << "8. Count Contacts\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            break;
        }

        switch (choice) {
            case 1: addContact(); break;
            case 2: displayContacts(); break;
            case 3: searchContact(); break;
            case 4: updateContact(); break;
            case 5: deleteContact(); break;
            case 6: sortContacts(); break;
            case 7: markEmergency(); break;
            case 8: countContacts(); break;
            case 9: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 9);

    while (head != NULL) {
        Contact* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
