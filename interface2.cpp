#include <windows.h>
#include <stdio.h>

char logo[] =
        " /## /########                           /##                          \n"
        "|__/|__  ##__/                          | ##                          \n"
        " /##   | ##  /######  /######   /#######| ##   /##  /######   /###### \n"
        "| ##   | ## /##__  ##|____  ## /##_____/| ##  /##/ /##__  ## /##__  ##\n"
        "| ##   | ##| ##  \\__/ /#######| ##      | ######/ | ########| ##  \\__/ \n"
        "| ##   | ##| ##      /##__  ##| ##      | ##_  ## | ##_____/| ##      \n"
        "| ##   | ##| ##     |  #######|  #######| ## \\  ##|  #######| ##      \n"
        "|__/   |__/|__/      \\_______/ \\_______/|__/  \\__/ \\_______|__/      \n";

int choice;

void printMenu() {
    printf("[========================= Menu Inicial ==========================]\n\n");
    printf("<< [1]. Cadastrar >>\n");
    printf("<< [2]. Pesquisar >>\n");
    printf("<< [3]. Editar    >>\n");
    printf("<< [4]. Apagar    >>\n");
    printf("<< [5]. Sair      >>\n");
    printf("\n>>> Selecione uma opcao:");
}

void printCadastrar() {
	system("cls");
    printf("========= Modo Cadastrar =========\n");
    //TODO
    scanf("%d", &choice);
}

void printPesquisar() {
	system("cls");
    printf("========= Modo Pesquisar =========\n");
    //TODO
    scanf("%d", &choice);
}

void printEditar() {
	system("cls");
    printf("========= Modo Editar =========\n");
    //TODO
    scanf("%d", &choice);
}

void printApagar() {
	system("cls");
    printf("========= Modo Apagar =========\n");
    //TODO
    scanf("%d", &choice);
}

int main() {
	
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | 0);
	
    printf("%s\n", logo);

    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printCadastrar();
                break;
            case 2:
                printPesquisar();
                break;
            case 3:
                printEditar();
                break;
            case 4:
                printApagar();
                break;
            case 5:
            	system("cls");
                printf("Saindo do programa.\n");
                Sleep(500);
                system("cls");
                printf("Saindo do programa..\n");
                Sleep(500);
                system("cls");
                printf("Saindo do programa...\n");
                Sleep(500);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 5);

    return 0;
}
