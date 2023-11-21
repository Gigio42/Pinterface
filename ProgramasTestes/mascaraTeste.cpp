#include <stdio.h>
#include <windows.h>

void aplicarMascara(char *input, char *maskedInput) {
    int j = 0;

    for (int i = 0; input[i] != '\0'; ++i) {
        if (i == 3 || i == 6) {
            maskedInput[j++] = '.';
        } else if (i == 9) {
            maskedInput[j++] = '-';
        }
        maskedInput[j++] = input[i];
    }
    maskedInput[j] = '\0';
}

void apagarVisualmente(int n) {
    for (int i = 0; i < n; ++i) {
        printf("\b \b"); // Apaga visualmente um caractere
    }
}

int main() {
    char cpf[12];
    char maskedInput[15];
    int i = 0;

    HANDLE hStdin;
    DWORD mode;

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT) & (~ENABLE_LINE_INPUT));

    printf("Digite o CPF (apenas digitos): \n");

    while (1) {
        char ch;
        DWORD read;

        ReadConsole(hStdin, &ch, 1, &read, NULL);

        if (ch == '\b') { // Backspace
            if (i > 0) {
                --i;
                cpf[i] = '\0'; // Apaga o último caractere
                aplicarMascara(cpf, maskedInput);
                apagarVisualmente(strlen(maskedInput) + 1);
            }
        } else if (ch >= '0' && ch <= '9' && i < 11) {
            cpf[i++] = ch;
        }

        aplicarMascara(cpf, maskedInput);
        printf("\rCPF com mascara: %s", maskedInput);

        if (i > 10) {
            break; // Se Enter for pressionado, encerra o loop
        }
    }

    SetConsoleMode(hStdin, mode); // Restaurar o modo original do console

    printf("\n");
    printf("O CPF eh %s\n", maskedInput);

    return 0;
}
