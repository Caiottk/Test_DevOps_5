#include <iostream>
#include <vector>
#include <numeric>

#ifndef APP_VERSION
#define APP_VERSION "UNKNOWN"
#endif

int add(int a, int b) {
    return a + b;
}

int main(int argc, char* argv[]) {

    if (argc > 1 && std::string(argv[1]) == "--version") {
        std::cout << "Calculator App Version: " << APP_VERSION << std::endl;
        return 0;
    }

    std::cout << " Calculadora Iniciada " << std::endl;
    
    int a = 10;
    int b = 20;
    
    std::cout << "Calculando: " << a << " + " << b << " = " << add(a, b) << std::endl;
    
    return 0;
}
