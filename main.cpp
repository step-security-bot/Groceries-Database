#include "database.h"

using namespace std;

int main(){

    Database myDatabase("product_database.txt");

    Product cake("food", "001", "cake", "a slice of cake", "$4.99");
    Product cereal("food", "002", "cereal", "a box of cereal", "$4.00");
    Product tv("technology", "003", "tv", "a television", "$500.00");

    vector<Product> myProductVector = {cake, cereal, tv};

    myDatabase.turnProductVectorIntoFile(myProductVector);

    
    
    return 0;

}
