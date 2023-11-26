#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
        const vector<string> makeDataVector(){

            vector<string> myVector = {itemType, itemNum, itemName, itemDescription, price};
            return myVector;

        }

        //prints out the data members of the product, for debugging purposes
        const void print(){

            vector<string> myStringVector = makeDataVector();

            for(string myString : myStringVector){

                cout << myString << endl;

            }

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
        numOfLines = 0;
        vector<string> fileVector = turnFileIntoStringVector();

        for(string line : fileVector){

            if(line == "^"){

                numOfLines++;

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

        numOfLines++;


    }




    //removes the last product object from the database file by finding the second to last & and rewriting the file to omit everything after it
    const void removeLast(){

        vector<string> linesVector = turnFileIntoStringVector();

        int ampersandDecrementor = numOfLines;
        int lineIncrementor = 0;
        vector<string> newLinesVector = {};



        if (numOfLines > 1){

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
            numOfLines--;

        }else{

            clearDatabase();
            

        }


    }

    //clears the file
    const void clearDatabase(){

        ofstream file(fileName);

        file << "";

        file.close();

        numOfLines = 0;

    }



    private: 
        string fileName;
        int numOfLines;







};
