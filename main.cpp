#include "database.h"

using namespace std;

int main(){

    Database myDatabase("product_database.txt");

    Product cake("food", "123", "cake", "A slice of cake.", "$4.99");

    myDatabase.append(cake);
    
    
    return 0;

}
