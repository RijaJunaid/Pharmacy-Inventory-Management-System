#include <iostream>
#include <string>
#include <vector>
#include<conio.h>
#include<fstream>
#include<sstream>
using namespace std;

// Item class to represent a medication in the inventory
class Item {
private:
    string itemName;
    int Quantity;
    double Price;
    string expirydate;
    string type_of_item;

public:
    Item( string name, int quantity, double price, string exp,string typeitem) {
        this->itemName = name;
        this->Quantity = quantity;
        this->Price = price;
        this->expirydate = exp;
        this->type_of_item = typeitem;
    }
    string getitemName() {
        return itemName;
    }
    string gettypeofitem() {
        return type_of_item;
    }
    int getQuantity() {
        return Quantity;
    }
    double getPrice() {
        return Price;
    }
    string getexpirydate() {
        return expirydate;
    }
    void setQuantity(int quantity) {
        this->Quantity = quantity;
    }
    void settexpirydate() {
        this->expirydate = expirydate;
    }
};

// PharmacyInventory class to manage the inventory of the pharmacy
class PharmacyInventory {
private:
    vector<Item>items;
public:
    void addItem( string name,  string type, int quantity, string expiryDate, double price) {
       items.push_back(Item(name, quantity,price, expiryDate,type));
    }
   // Item(string name, int quantity, double price, string exp, string typeitem)
    void removeItem(string name) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i].getitemName() == name) {
                items.erase(items.begin() + i);
                break;
            }
        }
    }
    void displayInventory() {
        cout << "Pharmacy Inventory:" << endl;
        for (int i = 0; i < items.size(); i++) {
            cout << "Item " << i + 1 << ":" << endl;
            cout << "Name: " << items[i].getitemName() << endl;
            cout << "Quantity: " << items[i].getQuantity() << endl;
            cout << "Price: $" << items[i].getPrice() << endl;
        }
    }
    void sellItem(string name, int quantity) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i].getitemName() == name) {
                int newQuantity = items[i].getQuantity() - quantity;
                if (newQuantity < 0) {
                    cout << "Insufficient quantity!" << endl;
                    return;
                }
                items[i].setQuantity(newQuantity);

                if (newQuantity < 15) {
                    callVendor(name, newQuantity);
                }

                cout << "Sold " << quantity << " " << name << "(s)." << endl;
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void callVendor(string name, int quantity) {
        cout << "Calling vendor for item " << name << ". Current quantity: " << quantity << endl;
        // Add code to call the vendor here
    }




    void saveInventoryToCSV( string inputfile) {
        ofstream file(inputfile);
        if (!file.is_open()) {
            cout << "Failed to open the CSV file for writing." << endl;
            return;
        }

        for ( auto& item : items) {
            file << item.getitemName() << "," << item.getQuantity() << "," << item.getPrice() << endl;
        }

        file.close();
        cout << "Inventory saved to " << inputfile << " successfully." << endl;
    }

    void loadInventoryFromCSV(string inputfile) {
        ifstream file(inputfile);
        if (!file.is_open()) {
            cout << "Failed to open the CSV file for reading." << endl;
            return;
        }

        items.clear();
        

        string line;
        getline(file, line); // Read and discard the header line

        while (getline(file, line)) {
            stringstream ss(line);
            string customerName;
            string customerID;
            string customerPhone;
            string customerAddress;
            string itemName;
            string type;
            int quantity;
            string expiryDate;
            double price;
            getline(ss, customerName, ',');
            getline(ss, customerID, ',');
            getline(ss, customerPhone, ',');
            getline(ss, customerAddress, ',');
            getline(ss, itemName, ',');
            getline(ss, type, ',');
            ss >> quantity;
            ss.ignore();
            getline(ss, expiryDate, ',');
            ss >> price;

            // Add the item to the inventory
            items.push_back(Item(itemName, quantity, price, expiryDate ,type ));
        }

        file.close();
        cout << "Inventory loaded from " << inputfile << " successfully." << endl;
    }
   
};

// Main function to test the PharmacyInventory class
int main() {
    PharmacyInventory inventory;
    int choice;

    string username = "admin";
    string password = "password";
    string inputUsername;
    string inputPassword;

    cout << "Enter your Username: ";
    cin >> inputUsername;

    cout << "Enter your Password: ";
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!inputPassword.empty()) {
                cout << "\b \b";
                //inputPassword.pop_back();
            }
        }
        else {
            cout << '*';
            inputPassword += ch;
        }
    }

    cout << endl;

    if (inputUsername == username && inputPassword == password) {
        cout << "-------Login successful! Welcome, " << username << "-------" << endl;


        inventory.loadInventoryFromCSV("pharmacydata.csv");
        do {
            cout << "------Pharmacy Inventory Management System------" << endl;
            cout << "1. Add Item" << endl;
            cout << "2. Remove Item" << endl;
            cout << "3. Display Inventory" << endl;
            cout << "4. Sell Item" << endl;
            cout << "5. Quit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
            case 1: {
                string name;
                string type; // Added type variable
                int quantity;
                string expiryDate; // Added expiryDate variable
                double price;
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter item type: ";
                cin >> type;
                cout << "Enter item quantity: ";
                cin >> quantity;
                cout << "Enter item expiry date: ";
                cin >> expiryDate;
                cout << "Enter item price: ";
                cin >> price;
                inventory.addItem(name, type, quantity, expiryDate, price);// Pass the additional arguments
                break;
            }
            case 2: {
                string name;
                cout << "Enter item name: ";
                cin >> name;
                inventory.removeItem(name);
                break;
            }
            case 3: {
                inventory.displayInventory();
                break;
            }
            case 4: {
                string name;
                int quantity;
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter item quantity: ";
                cin >> quantity;
                inventory.sellItem(name, quantity);
                break;
            }
            case 5: {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice!" << endl;
            }
            }
        } while (choice != 5);
           
        
    }

   else {
        cout << "Invalid Username or Password. Login Failed." << endl;
    

    }

    return 0;
}