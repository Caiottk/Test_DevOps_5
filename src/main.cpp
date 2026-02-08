#include <iostream>
#include <vector>
#include <numeric>

int add(int a, int b) {
    return a + b;
}

int main() {
    std::cout << " Calculadora Iniciada " << std::endl;
    
    int a = 10;
    int b = 20;
    
    std::cout << "Calculando: " << a << " + " << b << " = " << add(a, b) << std::endl;
    
    return 0;
}
