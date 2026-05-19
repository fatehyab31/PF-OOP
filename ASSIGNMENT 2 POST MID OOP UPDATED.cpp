#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ===================== BASE CLASS =====================
class LibraryResource {
protected:
    int resourceID;
    string title;
    string author;
    bool isAvailable;

public:
    // Constructor
    LibraryResource(int id, string t, string a, bool avail = true) {
        resourceID = id;
        title = t;
        author = a;
        isAvailable = avail;
    }

    // Getters
    int getResourceID() { return resourceID; }
    string getTitle() { return title; }
    string getAuthor() { return author; }
    bool getIsAvailable() { return isAvailable; }

    // Setters (this pointer used here to distinguish parameter from member variable)
    void setTitle(string title) {
        this->title = title; // 'this->title' is the member, 'title' is the parameter
    }

    void setAuthor(string author) {
        this->author = author; // same reason as above
    }

    void setIsAvailable(bool isAvailable) {
        this->isAvailable = isAvailable;
    }

    // Display details (hidden by derived classes)
    void displayDetails() {
        cout << "ID: " << resourceID
            << " | Title: " << title
            << " | Author: " << author
            << " | Available: " << (isAvailable ? "Yes" : "No") << endl;
    }

    // Base late fee (hidden by derived classes - function hiding, NOT overriding)
    double calculateLateFee(int daysLate) {
        return daysLate * 1; // default fee
    }

    // Returns current object for method chaining (this pointer used here)
    LibraryResource& setDetails(string t, string a) {
        this->title = t;   // using this pointer explicitly
        this->author = a;
        return *this;      // returning current object using this pointer
    }
};


// ===================== DERIVED CLASS: Book =====================
class Book : public LibraryResource {
    string ISBN;
    int pageCount;

public:
    Book(int id, string t, string a, string isbn, int pages)
        : LibraryResource(id, t, a) {
        ISBN = isbn;
        pageCount = pages;
    }

    // Function hiding: hides base class calculateLateFee()
    double calculateLateFee(int daysLate) {
        return daysLate * 5; // Rs. 5 per day
    }

    void displayDetails() {
        cout << "[Book] ID: " << resourceID
            << " | Title: " << title
            << " | Author: " << author
            << " | ISBN: " << ISBN
            << " | Pages: " << pageCount
            << " | Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};


// ===================== DERIVED CLASS: Magazine =====================
class Magazine : public LibraryResource {
    int issueNumber;

public:
    Magazine(int id, string t, string a, int issue)
        : LibraryResource(id, t, a) {
        issueNumber = issue;
    }

    // Function hiding: hides base class calculateLateFee()
    double calculateLateFee(int daysLate) {
        return daysLate * 3; // Rs. 3 per day
    }

    void displayDetails() {
        cout << "[Magazine] ID: " << resourceID
            << " | Title: " << title
            << " | Author: " << author
            << " | Issue No: " << issueNumber
            << " | Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};


// ===================== DERIVED CLASS: DVD =====================
class DVD : public LibraryResource {
    int duration; // in minutes

public:
    DVD(int id, string t, string a, int dur)
        : LibraryResource(id, t, a) {
        duration = dur;
    }

    // Function hiding: hides base class calculateLateFee()
    double calculateLateFee(int daysLate) {
        return daysLate * 10; // Rs. 10 per day
    }

    void displayDetails() {
        cout << "[DVD] ID: " << resourceID
            << " | Title: " << title
            << " | Author: " << author
            << " | Duration: " << duration << " mins"
            << " | Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};


// ===================== LIBRARY MEMBER CLASS =====================
class LibraryMember {
    int memberID;
    string name;
    vector<LibraryResource> borrowedItems; // composition: stores by value (not pointer)

public:
    LibraryMember(int id, string n) {
        memberID = id;
        name = n;
    }

    int getMemberID() { return memberID; }
    string getName() { return name; }

    // Borrow a resource (availability already checked and set in Library::borrowResource)
    void borrowResource(LibraryResource res) {
        borrowedItems.push_back(res);
        cout << "'" << res.getTitle() << "' borrowed successfully by " << name << ".\n";
    }

    // Return a resource by ID
    void returnResource(int resourceID) {
        for (int i = 0; i < borrowedItems.size(); i++) {
            if (borrowedItems[i].getResourceID() == resourceID) {
                borrowedItems[i].setIsAvailable(true);
                cout << "'" << borrowedItems[i].getTitle() << "' returned successfully.\n";
                borrowedItems.erase(borrowedItems.begin() + i);
                return;
            }
        }
        cout << "Error: Resource ID " << resourceID << " not found in borrowed list.\n";
    }

    // Display all borrowed items
    void displayBorrowedItems() {
        if (borrowedItems.empty()) {
            cout << name << " has no borrowed items.\n";
            return;
        }
        cout << "Borrowed items of " << name << ":\n";
        for (int i = 0; i < borrowedItems.size(); i++) {
            borrowedItems[i].displayDetails();
        }
    }

    // Calculate total late fee
    double calculateTotalLateFee(int daysLate) {
        double total = 0;
        for (int i = 0; i < borrowedItems.size(); i++) {
            total += borrowedItems[i].calculateLateFee(daysLate);
        }
        return total;
    }

    // Friend function declaration
    friend void adminView(vector<LibraryResource>& resources, vector<LibraryMember>& members);
};


// ===================== LIBRARY CLASS =====================
class Library {
    vector<LibraryResource> resources;
    vector<LibraryMember> members;

public:
    // Friend function declaration
    friend void adminView(vector<LibraryResource>& resources, vector<LibraryMember>& members);

    void addResource(LibraryResource res) {
        resources.push_back(res);
        cout << "Resource '" << res.getTitle() << "' added to library.\n";
    }

    void registerMember(LibraryMember mem) {
        members.push_back(mem);
        cout << "Member '" << mem.getName() << "' registered.\n";
    }

    // Find resource index by ID
    int findResourceIndex(int id) {
        for (int i = 0; i < resources.size(); i++) {
            if (resources[i].getResourceID() == id) return i;
        }
        return -1;
    }

    // Find member index by ID
    int findMemberIndex(int id) {
        for (int i = 0; i < members.size(); i++) {
            if (members[i].getMemberID() == id) return i;
        }
        return -1;
    }

    void borrowResource(int memberID, int resourceID) {
        int mi = findMemberIndex(memberID);
        int ri = findResourceIndex(resourceID);

        if (mi == -1) { cout << "Error: Member not found.\n"; return; }
        if (ri == -1) { cout << "Error: Resource not found.\n"; return; }
        if (!resources[ri].getIsAvailable()) { cout << "Error: Resource already borrowed.\n"; return; }

        resources[ri].setIsAvailable(false);
        members[mi].borrowResource(resources[ri]);
    }

    void returnResource(int memberID, int resourceID) {
        int mi = findMemberIndex(memberID);
        int ri = findResourceIndex(resourceID);

        if (mi == -1) { cout << "Error: Member not found.\n"; return; }
        if (ri == -1) { cout << "Error: Resource not found.\n"; return; }

        members[mi].returnResource(resourceID);
        resources[ri].setIsAvailable(true);
    }

    void displayAllResources() {
        if (resources.empty()) { cout << "No resources in library.\n"; return; }
        cout << "\n--- All Library Resources ---\n";
        for (int i = 0; i < resources.size(); i++) {
            resources[i].displayDetails();
        }
    }

    void displayMemberItems(int memberID) {
        int mi = findMemberIndex(memberID);
        if (mi == -1) { cout << "Error: Member not found.\n"; return; }
        members[mi].displayBorrowedItems();
    }

    void calculateLateFee(int memberID, int daysLate) {
        int mi = findMemberIndex(memberID);
        if (mi == -1) { cout << "Error: Member not found.\n"; return; }
        double fee = members[mi].calculateTotalLateFee(daysLate);
        cout << "Total late fee for " << members[mi].getName() << ": Rs. " << fee << endl;
    }

    void callAdminView() {
        adminView(resources, members);
    }
};


// ===================== FRIEND FUNCTION =====================
// This function can access private members of both Library and LibraryMember
void adminView(vector<LibraryResource>& resources, vector<LibraryMember>& members) {
    cout << "\n====== ADMIN VIEW ======\n";

    cout << "\n-- All Resources --\n";
    if (resources.empty()) {
        cout << "No resources found.\n";
    }
    else {
        for (int i = 0; i < resources.size(); i++) {
            resources[i].displayDetails();
        }
    }

    cout << "\n-- All Members --\n";
    if (members.empty()) {
        cout << "No members found.\n";
    }
    else {
        for (int i = 0; i < members.size(); i++) {
            cout << "Member ID: " << members[i].memberID  // accessing private member directly
                << " | Name: " << members[i].name << endl;
            members[i].displayBorrowedItems();
        }
    }

    cout << "========================\n";
}


// ===================== MAIN MENU =====================
int main() {
    Library lib;
    int choice;

    cout << "Welcome to Library Management System\n";

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Add a new Resource\n";
        cout << "2. Register a new Member\n";
        cout << "3. Borrow a Resource\n";
        cout << "4. Return a Resource\n";
        cout << "5. Display all Resources\n";
        cout << "6. Display Member's Borrowed Items\n";
        cout << "7. Calculate Late Fee\n";
        cout << "8. Admin View\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int type, id, pages, issue, dur;
            string title, author, isbn;
            cout << "1. Book  2. Magazine  3. DVD\nType: ";
            cin >> type;
            cout << "Enter ID: "; cin >> id;
            cout << "Enter Title: "; cin >> title;
            cout << "Enter Author: "; cin >> author;

            if (type == 1) {
                cout << "Enter ISBN: "; cin >> isbn;
                cout << "Enter Page Count: "; cin >> pages;
                lib.addResource(Book(id, title, author, isbn, pages));
            }
            else if (type == 2) {
                cout << "Enter Issue Number: "; cin >> issue;
                lib.addResource(Magazine(id, title, author, issue));
            }
            else if (type == 3) {
                cout << "Enter Duration (minutes): "; cin >> dur;
                lib.addResource(DVD(id, title, author, dur));
            }
            else {
                cout << "Invalid type.\n";
            }

        }
        else if (choice == 2) {
            int id;
            string name;
            cout << "Enter Member ID: "; cin >> id;
            cout << "Enter Name: "; cin >> name;
            lib.registerMember(LibraryMember(id, name));

        }
        else if (choice == 3) {
            int mid, rid;
            cout << "Enter Member ID: "; cin >> mid;
            cout << "Enter Resource ID: "; cin >> rid;
            lib.borrowResource(mid, rid);

        }
        else if (choice == 4) {
            int mid, rid;
            cout << "Enter Member ID: "; cin >> mid;
            cout << "Enter Resource ID: "; cin >> rid;
            lib.returnResource(mid, rid);

        }
        else if (choice == 5) {
            lib.displayAllResources();

        }
        else if (choice == 6) {
            int mid;
            cout << "Enter Member ID: "; cin >> mid;
            lib.displayMemberItems(mid);

        }
        else if (choice == 7) {
            int mid, days;
            cout << "Enter Member ID: "; cin >> mid;
            cout << "Enter Days Late: "; cin >> days;
            lib.calculateLateFee(mid, days);

        }
        else if (choice == 8) {
            lib.callAdminView();

        }
        else if (choice == 9) {
            cout << "Goodbye!\n";

        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 9);

    return 0;
}