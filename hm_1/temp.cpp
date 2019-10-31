#include <iostream>

double f(double x1, double x2){
    return (x1 * x1 * x2 + x1 * x2 * x2 - 2 * x1 * x2);
}

int main(){
    std::cout << f(-0.1, 2.1) << "\n";
    std::cout << f(-0.1, 2.1) << "\n";
    std::cout << f(-0.1, 2.1) << "\n";
}