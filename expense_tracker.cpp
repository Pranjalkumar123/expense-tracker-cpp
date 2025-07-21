
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Expense {
    string date;
    string category;
    float amount;
    string note;
};

void addExpense() {
    Expense e;
    cout << "Enter date (DD-MM-YYYY): ";
    cin >> ws; getline(cin, e.date);
    cout << "Enter category (Food, Travel, etc.): ";
    getline(cin, e.category);
    cout << "Enter amount: ";
    cin >> e.amount;
    cout << "Enter note (optional): ";
    cin >> ws; getline(cin, e.note);

    ofstream file("expenses.txt", ios::app);
    file << e.date << "|" << e.category << "|" << e.amount << "|" << e.note << "\n";
    file.close();

    cout << "✅ Expense added successfully.\n";
}

void viewExpenses() {
    ifstream file("expenses.txt");
    string line;
    cout << "\n=== All Expenses ===\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void viewTotal() {
    ifstream file("expenses.txt");
    string line;
    float total = 0.0;
    while (getline(file, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        size_t pos3 = line.find("|", pos2 + 1);
        string amtStr = line.substr(pos2 + 1, pos3 - pos2 - 1);
        total += stof(amtStr);
    }
    file.close();
    cout << "💰 Total Expense: ₹" << total << "\n";
}

void filterByCategory() {
    string category;
    cout << "Enter category to filter: ";
    cin >> ws; getline(cin, category);
    ifstream file("expenses.txt");
    string line;
    cout << "\n=== Filtered by Category: " << category << " ===\n";
    while (getline(file, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        string cat = line.substr(pos1 + 1, pos2 - pos1 - 1);
        if (cat == category) {
            cout << line << endl;
        }
    }
    file.close();
}

void clearAllExpenses() {
    ofstream file("expenses.txt", ios::trunc);
    file.close();
    cout << "🧹 All expenses cleared!\n";
}

int main() {
    int choice;
    do {
        cout << "\n===== Expense Tracker =====\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. Filter by Category\n";
        cout << "4. View Total Expense\n";
        cout << "5. Clear All\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addExpense(); break;
            case 2: viewExpenses(); break;
            case 3: filterByCategory(); break;
            case 4: viewTotal(); break;
            case 5: clearAllExpenses(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "❌ Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
