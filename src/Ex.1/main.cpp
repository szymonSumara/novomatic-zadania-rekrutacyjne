#include <array>
#include <iostream>
#include "../Collision/collision.h"



int main(){
    std::cout << "Ex.1\n";
    std::cout << "------------------------------------\n";

    triangle A;
    A.points[0] = {0,0};
    A.points[1] = {0,10};
    A.points[2] = {10,0};

    triangle B;
    B.points[0] = {-1,1};
    B.points[1] = {-2,2};
    B.points[2] = {-4,3};

    std::cout << isColliding(A, B);
    return 0;
}