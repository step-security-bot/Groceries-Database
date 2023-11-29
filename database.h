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

        //returns the price of a product as a float
        const float getPriceAsFloat(){
            
            //stof() converts a string to a float
            return stof(price);

        }

        const string getType(){

            return itemType;

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

        //initializez numOfProducts as the size of a string vector that contains all the lines of the file.
        numOfProducts = 0;
        vector<string> fileVector = turnFileIntoStringVector();

        for(string line : fileVector){

            if(line == "^"){

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

        numOfProducts = myProductVector.size();





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
    const void sortByPrice(){

        
        vector<Product> myProductVector = turnFileIntoProductVector();

        bool sorting = true;
        int numOfSwaps;
        Product placeholder;

        while(sorting){

                numOfSwaps = 0;
                

                for(int i = 0; i < myProductVector.size()-1; i++){

                    if (myProductVector[i].getPriceAsFloat() > myProductVector[i+1].getPriceAsFloat()){

                        placeholder = myProductVector[i];
                        myProductVector[i] = myProductVector[i+1];
                        myProductVector[i+1] = placeholder;

                        numOfSwaps++;

                    
                    }

                    
                            
                }


                if(numOfSwaps == 0){
                    
                    sorting = false;

                }



                
                
            }
                    

            
            turnProductVectorIntoFile(myProductVector);
            

           

        }



        //uses a bubble sorting algorythm to sort products by type in alphabetical order
        const void sortByType(){

        
        vector<Product> myProductVector = turnFileIntoProductVector();

        bool sorting = true;
        int numOfSwaps;
        Product placeholder;

        while(sorting){

                numOfSwaps = 0;
                

                for(int i = 0; i < myProductVector.size()-1; i++){

                    if (myProductVector[i].getType() > myProductVector[i+1].getType()){

                        placeholder = myProductVector[i];
                        myProductVector[i] = myProductVector[i+1];
                        myProductVector[i+1] = placeholder;

                        numOfSwaps++;

                    
                    }

                    
                            
                }


                if(numOfSwaps == 0){
                    
                    sorting = false;

                }



                
                
            }
                    

            
            turnProductVectorIntoFile(myProductVector);
            

           

        }



        const Database makeNewFileOfProductsWithTheSameType(string newfilename, string type){

            vector<Product> myProductVector = turnFileIntoProductVector();
            vector<Product> vectorOfSameTypes = {};
        
            for(Product myProduct : myProductVector){

                if(myProduct.getType() == type){

                    vectorOfSameTypes.push_back(myProduct);

                }
        

            }

            Database myNewDatabase(newfilename);
            myNewDatabase.turnProductVectorIntoFile(vectorOfSameTypes);

            return myNewDatabase;


        }
        


    



    private: 
        string fileName;
        int numOfProducts;







};
