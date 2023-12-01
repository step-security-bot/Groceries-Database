#include "database.h"
//#include <Windows.h>
using namespace std;

int main()
{

    bool temp = true;
    int opt =1;
    Product toFind;


    cout << "Welcome Loading Database..." << endl << endl;
    Database myDatabase("product_database.txt");

    
   
    do {
        cout << "What would you like to do? " << endl;
        cout << "(1) Add new product" << endl;
        cout << "(2) Print Database " << endl;
        cout << "(3) Item Number Look up " << endl;
        cout << "(4) Edit product price" << endl;
        cout << "(5) Sort by Price " << endl;
        cout << "(6) Sort by type " << endl;
        cout << "(7) Print out seperate file for given type " << endl;
        cout << "(8) Delete product " << endl;
        cout << "(9) Close " << endl;

        cout << "\n\nEnter your option: ";
        cin >> opt;
        cout << endl << endl;

        switch (opt) {
        case 1: // Add new product
            
            do
            {
                myDatabase.addNewProduct();
                cout << "Enter 0 to stop, 1 to keep going: ";
                cin >> temp;
            } while (temp == true);
            break;
        case 2:
            // Print Database
            myDatabase.printAllProducts();
            break;
        case 3:
            // searches for specifc item by unique number
            cout << endl;
            toFind = myDatabase.userSearchByItemNum();
            toFind.print();
            cout << endl; 
            break;
        case 4:
            // Edit product price
            myDatabase.printAllProducts();
            myDatabase.editProductPrice();
            break;
        case 5:
            // Sort by Price
            myDatabase.sortByPrice();
            break;
        case 6:
            // Sort by type
            myDatabase.sortByType();
            break;
        case 7:
            // groups all of same type toghter saves into file
            myDatabase.filepertype();

            break;
        case 8:
            // Delete product
            //system("cls");
            myDatabase.printAllProducts();
            myDatabase.removeProduct();
            break;
        case 9:
            // Close
            cout << "Closing the program." << endl;
            break;
        case 32:
            // Clears database (option hidden)
            cout << "deleting database..." << endl;
            myDatabase.clearDatabase();
            break;
        default:
            cout << "Invalid choice. Please select a number from 1 to 9." << endl;
        }
        //system("pause");
        //system("cls");
    } while (opt != 9);

    return 0;
}
