#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

class Product{

    public:

        //constructor
        Product(string myType = "Null", string myNum = "Null", string myName = "Null", string myDescription = "Null", string myPrice = "Null"){

            itemType = myType;
            itemNum = myNum;
            itemName = myName;
            itemDescription = myDescription;
            price = myPrice;

        }

        //this function returns a string vector containing the values of the data members of the product object, in the order they appear in the constructor
         vector<string> makeDataVector() const {

            vector<string> myVector = {itemType, itemNum, itemName, itemDescription, price};
            return myVector;

        }

        //prints out the data members of the product, for debugging purposes
         void print() const{

            vector<string> myStringVector = makeDataVector();

            for(string myString : myStringVector){

                cout << myString << endl;

            }

        }

        const string getItemNum() const {
            return itemNum;
        }

        //returns the price of a product as a float
        const float getPriceAsFloat() {

            //stof() converts a string to a float
            return stof(price);

        }

        const string getType() {

            return itemType;

        }

        void setPrice(const string& newPrice) 
        {
            price = newPrice;
        }

    private:

        //these are the data members of the product class
        string itemType;
        string itemNum;
        string itemName;
        string itemDescription;
        string price;
};

class Database {

    public:

    //constructor, takes in the name of the database text file
    Database(string myFileName){

        fileName = myFileName;

        //initializez numOfLines as the size of a string vector that contains all the lines of the file.
        numOfProducts = 0;
        vector<string> fileVector = turnFileIntoStringVector();

        for (string line : fileVector) {

            if (line == "^") {

                numOfProducts++;

            }
        }
    }

    //takes a file and turn the data in it into a vector of products
    const vector<Product> turnFileIntoProductVector(){

        vector<string> linesVector = turnFileIntoStringVector();
        vector<Product> productVector = {};


        int i = 0;
        for(string line : linesVector){

            if(line == "^"){

                Product myProduct(linesVector[i + 1], linesVector[i + 2], linesVector[i+3], linesVector[i+4], linesVector[i+5]);
                productVector.push_back(myProduct);


            }

            i++;

        }

        return productVector;

    }

    //takes in a product vector and replaces whatever was in the file with the data from the product vector
    const void turnProductVectorIntoFile(vector<Product> myProductVector){

        clearDatabase();

        for(Product myProduct : myProductVector){

            append(myProduct);

        }
    }

    //returns a string vector that contains all the lines of the file
    const vector<string> turnFileIntoStringVector(){

        ifstream file(fileName);
        string line;
        vector<string> linesVector = {};

        while(getline(file, line)){

            linesVector.push_back(line);

        }
        
        file.close();

        return linesVector;

    
    }
    
    //appends a product object to the end of the file, a '^' marks the start of an object and a '&' marks the end
    const void append(Product myProduct){


        vector<string> productDataVector = myProduct.makeDataVector();
        ofstream file(fileName, ios::app);

        file << "^\n";
        for (string dataMember : productDataVector){

            file << dataMember << "\n";

        }
        file << "&\n";
        file.close();

        numOfProducts++;


    }

    //removes the last product object from the database file by finding the second to last & and rewriting the file to omit everything after it
    const void removeLast(){

        vector<string> linesVector = turnFileIntoStringVector();

        int ampersandDecrementor = numOfProducts;
        int lineIncrementor = 0;
        vector<string> newLinesVector = {};



        if (numOfProducts > 1){

            while (ampersandDecrementor > 1){

                if( linesVector[lineIncrementor] == "&"){

                    ampersandDecrementor--;

                }

                newLinesVector.push_back(linesVector[lineIncrementor]);
                lineIncrementor++;

                


            } 

            ofstream file(fileName);

            for(string line : newLinesVector){

                file << line;
                file << "\n";

            }

            file.close();
            numOfProducts--;

        }else{

            clearDatabase();
            

        }


    }

    //clears the file
    const void clearDatabase(){

        ofstream file(fileName);

        file << "";

        file.close();

        numOfProducts = 0;

    }

    //uses a bubble sorting algorythm to sort products by price from low to high
    const void sortByPrice() {


        vector<Product> myProductVector = turnFileIntoProductVector();

        bool sorting = true;
        int numOfSwaps;
        Product placeholder;

        while (sorting) {

            numOfSwaps = 0;


            for (int i = 0; i < myProductVector.size() - 1; i++) {

                if (myProductVector[i].getPriceAsFloat() < myProductVector[i + 1].getPriceAsFloat()) {

                    placeholder = myProductVector[i];
                    myProductVector[i] = myProductVector[i + 1];
                    myProductVector[i + 1] = placeholder;

                    numOfSwaps++;


                }



            }


            if (numOfSwaps == 0) {

                sorting = false;

            }





        }



        turnProductVectorIntoFile(myProductVector);
        printAllProducts();



    }

    //uses a bubble sorting algorythm to sort products by type in alphabetical order
    const void sortByType() {


        vector<Product> myProductVector = turnFileIntoProductVector();

        bool sorting = true;
        int numOfSwaps;
        Product placeholder;

        while (sorting) {

            numOfSwaps = 0;


            for (int i = 0; i < myProductVector.size() - 1; i++) {

                if (myProductVector[i].getType() > myProductVector[i + 1].getType()) {

                    placeholder = myProductVector[i];
                    myProductVector[i] = myProductVector[i + 1];
                    myProductVector[i + 1] = placeholder;

                    numOfSwaps++;


                }



            }


            if (numOfSwaps == 0) {

                sorting = false;

            }





        }



        turnProductVectorIntoFile(myProductVector);
        printAllProducts();




    }

    // Search function to find a product by its item number - no data verification
    Product searchByItemNum(const string& searchItemNum)
    {
        vector<Product> productVector = turnFileIntoProductVector();

        for (const Product& product : productVector)
        {
            if (product.getItemNum() == searchItemNum)
            {
                return product;
            }
        }

        // if no product is found return an empty Product or handle as needed
        return Product();
    }

    // allows for the user to enter a product number  - has data verification
    Product userSearchByItemNum()
    {
        int x = 0;

        do {
            cout << "Enter the item number: ";
            cin >> x;

            // Check if the input is not an integer or if it's less than or equal to 0
            if (cin.fail() || x <= 0) {
                cout << "Invalid data entered, try again.\n";
                cin.clear(); // Clear error flags
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore wrong input
            }

        } while (x <= 0);
        return searchByItemNum(std::to_string(x));
    }

    // Removes a product with the specified item number
    const void removeProduct()
    {
        vector<Product> productVector = turnFileIntoProductVector();
        string itemNum = intInput();
        auto it = std::find_if(productVector.begin(), productVector.end(), [&itemNum](const Product& product)
        {
            return product.getItemNum() == itemNum;
        });

        if (it != productVector.end()) 
        {
            productVector.erase(it);
            turnProductVectorIntoFile(productVector);
        }
        else 
        {
            cout << "Product not found." << endl;
        }
    }

    void printAllProducts() 
    {
        vector<Product> productVector = turnFileIntoProductVector();

        if (productVector.empty()) 
        {
            cout << "The database is empty." << endl;
            return;
        }

        for (const Product& product : productVector) 
        {
            product.print();
            cout << "----------------------" << endl; // Separator between products
        }
    }

    void addNewProduct()
    {
        string type, itemNum, name, description, price;

        while (true) {
            // Ignore any leftover characters in the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter item type (food, tech, nonfood, other): ";
            getline(cin, type);

            // Check if the input is one of the allowed types
            if (type == "food" || type == "tech" || type == "nonfood" || type == "other") {
                break; // Valid input, break out of the loop
            }
            else {
                cout << "Invalid type entered. Please choose from food, tech, nonfood, or other." << endl;
            }
        }

        itemNum = itemNumCreator();
        // Ignore any leftover characters in the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        cout << "Enter item name: ";
        getline(cin, name);

        cout << "Enter item description: ";
        getline(cin, description);

        cout << "Enter price: ";
        getline(cin, price);

        Product newProduct(type, itemNum, name, description, price);
        append(newProduct);

        cout << "Product added successfully." << endl;
    }

    void editProductPrice() 
    {
        string itemNum, newPrice;
        cout << "Enter the item number of the product to edit: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, itemNum);

        // Find the product
        vector<Product> products = turnFileIntoProductVector();
        auto it = find_if(products.begin(), products.end(), [&itemNum](const Product& product) 
            {
              return product.getItemNum() == itemNum;
            });

       if (it != products.end()) 
       {
           it->print();
           cout << endl;
           
           // Product found, prompt for new price and update
            cout << "Enter new price: ";
            getline(cin, newPrice);

            it->setPrice(newPrice); // Update the price

            // Save the updated product list
            turnProductVectorIntoFile(products);
            cout << "Price updated successfully." << endl;
       }
       else 
       {
           cout << "Product not found." << endl;
       }
    }
    
    void filepertype() {
        string type, name;
        while (true) { // only allows given types
            cout << "Enter item type (food, tech, nonfood, other): ";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore wrong input
            getline(cin, type);

            if (type == "food" || type == "tech" || type == "nonfood" || type == "other") {
                cout << "Enter the file name: ";
                getline(cin, name); // Read the file name
                makeNewFileOfProductsWithTheSameType(name, type);
                break; // Exit the loop after the file is created
            }
            else {
                cout << "Invalid type entered. Please choose from food, tech, nonfood, or other." << endl;
            }
        }
    }

    private: 
        string fileName;
        int numOfProducts;

        const Database makeNewFileOfProductsWithTheSameType(string newfilename, string type) {

            vector<Product> myProductVector = turnFileIntoProductVector();
            vector<Product> vectorOfSameTypes = {};

            for (Product myProduct : myProductVector) {

                if (myProduct.getType() == type) {

                    vectorOfSameTypes.push_back(myProduct);

                }


            }

            Database myNewDatabase(newfilename);
            myNewDatabase.turnProductVectorIntoFile(vectorOfSameTypes);

            return myNewDatabase;


        }

        // takes in a number makes sure its a number returns it as a string
        string intInput()
        { 
            int x;
            do 
            {
                cout << "Enter the number: ";
                cin >> x;

                // Check if the input is not an integer or if it's less than or equal to 0
                if (cin.fail() || x <= 0) 
                {
                    cout << "Invalid data entered, try again.\n";
                    cin.clear(); // Clear error flags
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore wrong input
                }

            } while (x <= 0);
            return to_string(x);
        }

        // checks if a item with the same number exist in the data base
        bool existingItemNum(const string& searchItemNum)
        {
            vector<Product> productVector = turnFileIntoProductVector();

            for (const Product& product : productVector)
            {
                if (product.getItemNum() == searchItemNum)
                {
                    return true;  // Item number exists
                }
            }

            return false;  // Item number does not exist
        }

        // returns item number as a string makes sure it dosent exist
        string itemNumCreator()
        {
            string itemNumber;

            while (true)
            {
                itemNumber = intInput();

                if (!existingItemNum(itemNumber)) 
                {
                    break;  // Exit loop if item number is unique
                }

                cout << "Item number already exists, please enter a different number." << endl;
            }
            return itemNumber;
        }
};
