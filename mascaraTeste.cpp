#include <stdio.h>
#include <conio.h>

void applyCreditCardMask(char *input, char *maskedInput) {
    int i, j = 0;

    for (i = 0; input[i] != '\0'; ++i) {
        if (i > 0 && i % 4 == 0) {
            maskedInput[j++] = '-';
        }

        maskedInput[j++] = input[i];
    }

    maskedInput[j] = '\0';
}

int main() {
    char creditCardNumber[16]; // Tamanho do número do cartão sem a máscara
    char maskedInput[20];      // Tamanho da máscara "xxxx-xxxx-xxxx-xxxx"
    int i = 0;

    printf("Digite o número do cartao de credito (apenas digitos): \n");

    while (1) {
        char ch = getch();

        if (ch == '\r' || ch == '\n') {
            break; // Se Enter for pressionado, encerra o loop
        } else if (ch >= '0' && ch <= '9' && i < 16) {
            creditCardNumber[i++] = ch;
            applyCreditCardMask(creditCardNumber, maskedInput);
            printf("\rNumero do cartao com mascara: %s", maskedInput);
        }
    }

    printf("\n");
    printf("O cartao eh %s\n", maskedInput);
    return 0;
}
