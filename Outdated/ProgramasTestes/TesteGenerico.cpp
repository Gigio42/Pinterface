#include <stdio.h>

// Exemplo fictício da função color
void setColor(int color) {
    // Função color específica do compilador
    // A implementação exata pode variar
    // Este é apenas um exemplo fictício
    printf("\033[%dm", color);
}

int main() {
    // Exemplo de uso da função color
    setColor(35); // Define a cor para roxo
    printf("Hello, World!\n");

    setColor(0); // Reseta para a cor padrão
    printf("Hello, World!\n");

    return 0;
}
