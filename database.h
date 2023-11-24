#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Product{

    public:

        Product(string myNum = "Null", string myName = "Null", string myDescription = "Null", string myPrice = "Null"){

            itemNum = myNum;
            itemName = myName;
            itemDescription = myDescription;
            price = myPrice;

        }

        const vector<string> makeDataVector(){

            vector<string> myVector = {itemNum, itemName, itemDescription, price};
            return myVector;

        }

    private:

        string itemNum;
        string itemName;
        string itemDescription;
        string price;





};




class Database {

    public:
    
    static const void appendProductToFile(Product myProduct){
        vector<string> productDataVector = myProduct.makeDataVector();
        ofstream file("product_database.txt", ios::app);

        file << "^\n";
        for (string dataMember : productDataVector){

            file << dataMember << "\n";

        }
        file << "&\n";
        file.close();


    }

    static const void clearDatabase(){

        ofstream file("product_database.txt");

        file << "";

        file.close();

    }



    private: 
        int numOfItems;






};
