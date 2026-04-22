#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class MenuItem {
    string name;
    double price;
public:
    MenuItem(string n, double p) : name(n), price(p) {}
    string getName() { return name; }
    double getPrice() { return price; }
    void setPrice(double p) { price = p; }
};

class Order {
    string itemName;
    int quantity;
    double totalPrice;
public:
    Order(string item, int qty, double total) : itemName(item), quantity(qty), totalPrice(total) {}
    string getItemName() { return itemName; }
    int getQuantity() { return quantity; }
    double getTotalPrice() { return totalPrice; }
};

class FoodSystem {
    vector<MenuItem> menu;
    vector<Order> history;

public:
    FoodSystem() {
        menu.push_back(MenuItem("Biryani", 150));
        menu.push_back(MenuItem("FriedRice", 120));
        menu.push_back(MenuItem("Omlet", 30));
        menu.push_back(MenuItem("Samosa", 20));
        menu.push_back(MenuItem("ChickenPuff", 35));
        menu.push_back(MenuItem("EggPuff", 25));
        menu.push_back(MenuItem("CurryPuff", 30));
    }

    void showMenu() {
        cout << fixed << setprecision(2);
        cout << "\n--- MENU ---\n";
        for (int i = 0; i < menu.size(); i++) {
            cout << i + 1 << ". " << menu[i].getName()
                 << " - Rs " << menu[i].getPrice() << "\n";
        }
    }

    void showHistory() {
        if (history.empty()) {
            cout << "No order history.\n";
            return;
        }
        cout << "\n--- ORDER HISTORY ---\n";
        for (auto &o : history) {
            cout << o.getItemName() << " x" << o.getQuantity()
                 << " = Rs " << o.getTotalPrice() << "\n";
        }
    }

    double placeOrder() {
        showMenu();
        int choice, qty;

        cout << "Enter item number: ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > menu.size()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice.\n";
            return 0.0;
        }

        cout << "Enter quantity: ";
        cin >> qty;
        if (cin.fail() || qty <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid quantity.\n";
            return 0.0;
        }

        MenuItem item = menu[choice - 1];
        double total = item.getPrice() * qty;

        cout << fixed << setprecision(2);
        cout << "\nOrder Placed: " << item.getName()
             << " x" << qty << " = Rs " << total << "\n";

        history.push_back(Order(item.getName(), qty, total));
        return total;
    }

    void adminLogin() {
        string password;
        cout << "Enter admin password: ";
        cin >> password;

        if (password == "admin123") {
            adminPanel();
        } else {
            cout << "Access denied.\n";
        }
    }

    void adminPanel() {
        int ch;
        do {
            cout << "\n--- ADMIN PANEL ---\n";
            cout << "1. Add Menu Item\n";
            cout << "2. Update Item Price\n";
            cout << "3. Delete Menu Item\n";
            cout << "4. View Menu\n";
            cout << "5. Clear Order History\n";
            cout << "6. Exit Admin\n";
            cout << "Enter choice: ";
            cin >> ch;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input.\n";
                continue;
            }

            if (ch == 1) {
                string name;
                double price;

                cout << "Enter item name: ";
                cin >> name;

                cout << "Enter price: ";
                cin >> price;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid price.\n";
                    continue;
                }

                menu.push_back(MenuItem(name, price));
                cout << "Item added!\n";
            }
            else if (ch == 2) {
                showMenu();
                int id;
                double newPrice;

                cout << "Enter item number to update: ";
                cin >> id;

                if (cin.fail() || id < 1 || id > menu.size()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid item number.\n";
                    continue;
                }

                cout << "Enter new price: ";
                cin >> newPrice;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid price.\n";
                    continue;
                }

                menu[id - 1].setPrice(newPrice);
                cout << "Price updated!\n";
            }
            else if (ch == 3) {
                showMenu();
                int id;

                cout << "Enter item number to delete: ";
                cin >> id;

                if (cin.fail() || id < 1 || id > menu.size()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid item number.\n";
                    continue;
                }

                menu.erase(menu.begin() + id - 1);
                cout << "Item deleted!\n";
            }
            else if (ch == 4) {
                showMenu();
            }
            else if (ch == 5) {
                history.clear();
                cout << "Order history cleared!\n";
            }

        } while (ch != 6);
    }
};

int main() {
    FoodSystem system;
    int choice;
    double sessionTotal = 0.0;

    do {
        cout << "\n====== ONLINE FOOD ORDERING SYSTEM ======\n";
        cout << "1. View Menu\n";
        cout << "2. Place Order\n";
        cout << "3. View Order History\n";
        cout << "4. Admin Login\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: system.showMenu(); break;
            case 2: sessionTotal += system.placeOrder(); break;
            case 3: system.showHistory(); break;
            case 4: system.adminLogin(); break;
            case 5:
                cout << fixed << setprecision(2);
                cout << "Total bill for this session: Rs " << sessionTotal << "\n";
                cout << "Thank you!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}