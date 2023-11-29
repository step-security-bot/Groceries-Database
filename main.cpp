#include "database.h"

using namespace std;

int main(){

    Database myDatabase("product_database.txt");

    Product appleSlices("food", "006", "apple slices", "sliced apples", "2.00");
    Product cake("food", "001", "cake", "a slice of cake", "4.99");
    Product cereal("food", "002", "cereal", "a box of cereal", "4.00");
    Product tv("technology", "003", "tv", "a television", "500.00");
    Product dogFood("pet supplies", "004", "dog food", "food for dogs", "20.00");
    Product catFood("pet supplies", "005", "cat food", "food for cats", "25.00");
    

   vector<Product> myProductVector = {tv, cake, cereal, dogFood, appleSlices, catFood};

    myDatabase.turnProductVectorIntoFile(myProductVector);

    Database myNewDatabase = myDatabase.makeNewFileOfProductsWithTheSameType("product_database.txt", "food");

    return 0;

}
