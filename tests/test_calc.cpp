#include <iostream>
#include <cassert>

int add(int a, int b) {
    return a + b;
}

int main() {
    std::cout << "[TESTE] Iniciando Teste Unitário de Soma..." << std::endl;
    
    int result = add(2, 2);
    
    if (result == 4) {
        std::cout << "[PASSOU] 2 + 2 = 4" << std::endl;
        return 0; // Out 0 = Sucesso no Jenkins
    } else {
        std::cout << "[FALHOU] Esperado 4, recebeu " << result << std::endl;
        return 1; // Out 1 = Falha no Jenkins
    }
}
