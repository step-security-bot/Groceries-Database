#include "database.h"

using namespace std;

int main(){

    Product cake("123", "cake", "A slice of cake.", "$4.99");
    Database::appendProductToFile(cake);
    


    return 0;

}
