#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define MAX_LENGTH 1024

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void editar();

char logo[] =
        "                                                                       \n"
        "  /## /########                           /##                          \n"
        " |__/|__  ##__/                          | ##                          \n"
        "  /##   | ##  /######  /######   /#######| ##   /##  /######   /###### \n"
        " | ##   | ## /##__  ##|____  ## /##_____/| ##  /##/ /##__  ## /##__  ##\n"
        " | ##   | ##| ##  \\__/ /#######| ##      | ######/ | ########| ##  \\__/ \n"
        " | ##   | ##| ##      /##__  ##| ##      | ##_  ## | ##_____/| ##      \n"
        " | ##   | ##| ##     |  #######|  #######| ## \\  ##|  #######| ##      \n"
        " |__/   |__/|__/      \\_______/ \\_______/|__/  \\__/ \\_______ |__/      \n";

int choice = 1;
int maxChoice = 5;
bool escape = false;

int codCliente = 1;

struct Cliente {
    char nome[20];
    char cpf[15];
    char telefone[15];
    char endereco[30];
    char cep[10];
    char cidade[20];
    char estado[3];
};

typedef struct {
    int codCliente;
    char nome[MAX_LENGTH];
    char cpf[MAX_LENGTH];
    char telefone[MAX_LENGTH];
    char endereco[MAX_LENGTH];
    char cep[MAX_LENGTH];
    char cidade[MAX_LENGTH];
    char estado[MAX_LENGTH];
} ClienteTemp;

//Personalização e customização
//cores & screenlock
void corLogo(){
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
}
void corMenu(){
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void corSelecionado(){
     SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void corOpcao(){
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | 0);
}
void corSucesso(){
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
}
void corErro(){
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}

void pausarNotif(){
    corOpcao();
    printf("\n >>> Pressione qualquer tecla para sair.");
    _getch();
}

//Mascaras
void apagarChar(int n) {
    for (int i = 0; i < n; ++i) {
        printf("\b \b"); // 1 \b para mover o cursor para trás, o segundo para apagar
    }
}

void aplicarMascaraCPF(char *input, char *maskedInput) {
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

void mascaraCPF(Cliente *clientes){
    char cpf[12];
    char mascara[15];      
    int i = 0;

    HANDLE hStdin;
    DWORD mode; //guarda o modo que está

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &mode); // 
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT) & (~ENABLE_LINE_INPUT)); //termina a execução sem precisar apertar enter e desabilita entrada padrão de caracteres

    printf(" >>>Digite o CPF: \n");

    while (1) {
        char ch;
        DWORD read; //guarda o total de variaveis

        ReadConsole(hStdin, &ch, 1, &read, NULL); //guarda um char em ch, 1 por vez, no read

        if (ch == '\b') { //Quando apertar back
            if (i > 0) {
                --i;
                cpf[i] = '\0'; // define o caracter atual como fim da string '\0' para poder apagar
                aplicarMascaraCPF(cpf, mascara);
                apagarChar(strlen(mascara) + 1); //de onde está, 1 pra frente
            }
        } else if (ch >= '0' && ch <= '9' && i < 11) {
            cpf[i++] = ch;
        }

        aplicarMascaraCPF(cpf, mascara);
        printf("\r >>>CPF: %s", mascara);

        if (i > 10) {
            break;
        }
    }
    SetConsoleMode(hStdin, mode); //volta o input ao padrão

    strcpy(clientes[codCliente].cpf, mascara);
}

void aplicarMascaraTelefone(char *input, char *maskedInput) {
    int j = 0;

    for (int i = 0; input[i] != '\0'; ++i) {
        if (i == 0) {
            maskedInput[j++] = '(';
            maskedInput[j++] = input[i];
        } else if (i == 2) {
            maskedInput[j++] = ')';
            maskedInput[j++] = input[i];
        } else if (i == 7) {
            maskedInput[j++] = '-';
            maskedInput[j++] = input[i];
        } else {
            maskedInput[j++] = input[i];
        }
    }
    maskedInput[j] = '\0';
}

void mascaraTelefone(Cliente *clientes) {
    char telefone[12];
    char mascara[15];
    int i = 0;

    HANDLE hStdin;
    DWORD mode;

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT) & (~ENABLE_LINE_INPUT));

    printf(" >>>Digite o telefone: \n");

    while (1) {
        char ch;
        DWORD read;

        ReadConsole(hStdin, &ch, 1, &read, NULL);

        if (ch == '\b') {
            if (i > 0) {
                --i;
                telefone[i] = '\0';
                aplicarMascaraTelefone(telefone, mascara);
                apagarChar(strlen(mascara) + 1);
            }
        } else if (ch >= '0' && ch <= '9' && i < 11) {
            telefone[i++] = ch;
        }

        aplicarMascaraTelefone(telefone, mascara);
        printf("\r >>>Telefone: %s", mascara);

        if (i > 10) {
            break;
        }
    }
    SetConsoleMode(hStdin, mode);

    strcpy(clientes[codCliente].telefone, mascara);
}

void aplicarMascaraCEP(char *input, char *maskedInput) {
    int j = 0;

    for (int i = 0; input[i] != '\0'; ++i) {
        if (i == 5) {
            maskedInput[j++] = '-';
            maskedInput[j++] = input[i];
        } else {
            maskedInput[j++] = input[i];
        }
    }
    maskedInput[j] = '\0';
}

void mascaraCEP(Cliente *clientes) {
    char cep[9]; 
    char mascara[12];
    int i = 0;

    HANDLE hStdin;
    DWORD mode;

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT) & (~ENABLE_LINE_INPUT));

    printf(" >>>Digite o CEP: \n");

    while (1) {
        char ch;
        DWORD read;

        ReadConsole(hStdin, &ch, 1, &read, NULL);

        if (ch == '\b') {
            if (i > 0) {
                --i;
                cep[i] = '\0';
                aplicarMascaraCEP(cep, mascara);
                apagarChar(strlen(mascara) + 1);
            }
        } else if (ch >= '0' && ch <= '9' && i < 8) {
            cep[i++] = ch;
        }

        aplicarMascaraCEP(cep, mascara);
        printf("\r >>>CEP: %s", mascara);

        if (i > 7) {
            break;
        }
    }
    SetConsoleMode(hStdin, mode);

    strcpy(clientes[codCliente].cep, mascara);
}

//Projeto em si
//Base
void handleSelection(int key) {
    switch (key) {
        case 'w':
        case 'W':
        case 72:
            choice = (choice - 1 > 0) ? choice - 1 : maxChoice;
            break;
        case 's':
        case 'S':
        case 80:
            choice = (choice + 1 <= maxChoice) ? choice + 1 : 1;
            break;
    }
}

void printMenu(int currentChoice) {
    system("cls");
    corLogo();
    printf("%s\n", logo);
    corMenu();
    printf(" [=========================== Menu Inicial ============================]\n\n");
    
    maxChoice = 5;

    for (int i = 1; i <= maxChoice; i++) {
        if (i == currentChoice) {
             corSelecionado();
             printf(" %c",16);
        } else {
            corOpcao();
        }
        switch (i) {
            case 1:
                printf(" << [Cadastrar]          >>\n");
                break;
            case 2:
                printf(" << [Pesquisar]          >>\n");
                break;
            case 3:
                printf(" << [Editar]             >>\n");
                break;
            case 4:
                printf(" << [Apagar/Recuperar]   >>\n");
                break;
            case 5:
                printf(" << [Sair]               >>\n");
                break;
        }
    }

    corMenu();
    printf("\n [=====================================================================]\n");
    corOpcao();
    printf("\n [w/s|%c%c]:Mover [Esc]:Sair\n [Enter]:Selecionar\n", 24, 25);
}

//Cadastro
void printCadastrar(int currentChoice, Cliente *clientes) { 
    system("cls");
    corLogo();
    printf("%s\n", logo);
    corMenu();
    printf(" [========================== Modo Cadastrar ===========================]\n\n");
    
    maxChoice = 10;

    for (int i = 1; i <= maxChoice; i++) {
        if (i == currentChoice) {
            corSelecionado();
            if(i > 8) {printf(" %c",16);}
        } else {
            corOpcao();
        }

        switch (i) {
            case 1:
            	printf(" [Codigo do cliente].: %i\n", codCliente);
                break;
            case 2:
                printf(" [Nome]..............: %s\n", clientes[codCliente].nome);
                break;
            case 3:
                printf(" [CPF]...............: %s\n", clientes[codCliente].cpf);
                break;
            case 4:
                printf(" [Telefone]..........: %s\n", clientes[codCliente].telefone);
                break;
            case 5:
                printf(" [Endereco]..........: %s\n", clientes[codCliente].endereco);
                break;
            case 6:
                printf(" [CEP]...............: %s\n", clientes[codCliente].cep);
                break;
            case 7:
                printf(" [Cidade]............: %s\n", clientes[codCliente].cidade);
                break;
            case 8:
                printf(" [Estado]............: %s\n\n", clientes[codCliente].estado);
                break;
            case 9:
                printf(" [Registrar]\n");
                break;
            case 10:
                printf(" [Voltar]\n");
                break;
        }
    }
    corOpcao();
    printf("\n >>> Use as setas ou 'W'/'S' para selecionar uma opcao e pressione 'Enter' para confirmar.\n");
}    

void sendToTxtFile(Cliente *clientes) {
    FILE *arquivoOriginal = fopen("Clientes.txt", "r");
    FILE *arquivoNovo = fopen("temporario.txt", "w");

    int numeroLinha = codCliente;

    char buffer[1024];
    int linhaAtual = 0;

    while (fgets(buffer, sizeof(buffer), arquivoOriginal) != NULL) {
        if (linhaAtual == numeroLinha) {
            fprintf(arquivoNovo, "%i,%s,%s,%s,%s,%s,%s,%s\n", codCliente, clientes[codCliente].nome, clientes[codCliente].cpf, clientes[codCliente].telefone,
            clientes[codCliente].endereco, clientes[codCliente].cep, clientes[codCliente].cidade, clientes[codCliente].estado);
        } else {
            fprintf(arquivoNovo, "%s", buffer);
        }
        linhaAtual++;
        
    }

    fclose(arquivoOriginal);
    fclose(arquivoNovo);

    remove("Clientes.txt");
    rename("temporario.txt", "Clientes.txt");
}

void setCodCliente(){
    FILE *arquivo = fopen("Clientes.txt", "r");

    char buffer[1024];
    int numeroLinha = 0;

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        numeroLinha++;

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        if (strlen(buffer) == 0) {
            codCliente = numeroLinha - 1;
            break;
        }
    }

    fclose(arquivo);
}

//Pesquisa
void printPesquisar(int currentChoice) {
	system("cls");
    corLogo();
    printf("%s\n", logo);
    corMenu();
    printf(" [========================== Modo Pesquisa ===========================]\n\n");
    
    maxChoice = 2;

    for (int i = 1; i <= maxChoice; i++) {
        if (i == currentChoice) {
            corSelecionado();
            printf(" %c",16);
        } else {
            corOpcao();
        }

        switch (i) {
            case 1:
            	printf("  [Pesquisar por CPF]\n");
                break;
            case 2:
                printf("  [Voltar]\n");
                break;
        }
    }
    corOpcao();
    printf("\n >>> Use as setas ou 'W'/'S' para selecionar uma opcao e pressione 'Enter' para confirmar.\n");
}

void imprimirCliente(ClienteTemp cliente) {
    corSelecionado();
    printf(" Codigo do cliente: %d\n", cliente.codCliente);
    printf(" Nome: %s\n", cliente.nome);
    printf(" CPF: %s\n", cliente.cpf);
    printf(" Telefone: %s\n", cliente.telefone);
    printf(" Endereco: %s\n", cliente.endereco);
    printf(" CEP: %s\n", cliente.cep);
    printf(" Cidade: %s\n", cliente.cidade);
    printf(" Estado: %s\n", cliente.estado);

    pausarNotif();
}

void limparCPF(char *cpf) {
    int i, j = 0;
    char cpfNumerico[MAX_LENGTH];

    for (i = 0; cpf[i] != '\0'; i++) {
        if (isdigit(cpf[i])) {
            cpfNumerico[j++] = cpf[i];
        }
    }

    cpfNumerico[j] = '\0';
    strcpy(cpf, cpfNumerico);
}

void formatarCPF(char *cpf) {
    char cpfFormatado[15];
    snprintf(cpfFormatado, sizeof(cpfFormatado), "%c%c%c.%c%c%c.%c%c%c-%c%c", cpf[0], cpf[1], cpf[2], cpf[3], cpf[4],
             cpf[5], cpf[6], cpf[7], cpf[8], cpf[9], cpf[10], cpf[11]);
    strcpy(cpf, cpfFormatado);
}

ClienteTemp pesquisarClientePorCPF(char *cpf, FILE *arquivo) {
    ClienteTemp clienteEncontrado;
    FILE *arq = arquivo;

    limparCPF(cpf);
    ClienteTemp clienteTemp;

    // Reiniciamos o ponteiro do arquivo para o início
    fseek(arq, 0, SEEK_SET);

    // linha de identificação
    char buffer[MAX_LENGTH];
    fgets(buffer, sizeof(buffer), arq);

    clienteEncontrado.codCliente = -1;

    // Loop para achar
    while (fscanf(arq, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^\n]", &clienteTemp.codCliente, clienteTemp.nome, clienteTemp.cpf,
    clienteTemp.telefone, clienteTemp.endereco, clienteTemp.cep, clienteTemp.cidade, clienteTemp.estado) == 8) {

        limparCPF(clienteTemp.cpf);

        if (strcmp(clienteTemp.cpf, cpf) == 0) {
            clienteEncontrado = clienteTemp;
            break;
        }
    }

    fclose(arq);

    return clienteEncontrado;
}

void procurarCPF() {
    FILE *arquivo = fopen("Clientes.txt", "r");

    char cpfPesquisado[MAX_LENGTH];
    printf(" >>> Digite o CPF do cliente que deseja pesquisar: ");
    scanf("%s", cpfPesquisado);

    ClienteTemp clienteEncontrado = pesquisarClientePorCPF(cpfPesquisado, arquivo);

    if (clienteEncontrado.codCliente == -1) {
        corErro();
        printf(" Cliente com CPF %s nao encontrado.\n", cpfPesquisado);
        pausarNotif();
    } else {
        formatarCPF(clienteEncontrado.cpf);
        corSucesso();
        printf("\n Cliente encontrado:\n\n");
        imprimirCliente(clienteEncontrado);
    }

    fclose(arquivo);
}

//Edição
void printEditar(int currentChoice) {
	system("cls");
    corLogo();
    printf("%s\n", logo);
    corMenu();
    printf(" [========================== Modo Editar ===========================]\n\n");
        
    maxChoice = 2;

    for (int i = 1; i <= maxChoice; i++) {
        if (i == currentChoice) {
            corSelecionado();
            printf(" %c",16);
        } else {
            corOpcao();
        }

        switch (i) {
            case 1:
            	printf(" [Editar por CPF]\n");
                break;
            case 2:
                printf(" [Voltar]\n");
                break;
        }
    }
    corOpcao();
    printf("\n >>> Use as setas ou 'W'/'S' para selecionar uma opcao e pressione 'Enter' para confirmar.\n");
}

void sendToTmpFile(ClienteTemp clientes, char mode) {
    FILE *arquivoOriginal = fopen("Clientes.txt", "r");
    FILE *arquivoNovo = fopen("temporario.txt", "w");

    int numeroLinha = clientes.codCliente;

    char buffer[1024];
    int linhaAtual = 0;

    while (fgets(buffer, sizeof(buffer), arquivoOriginal) != NULL) {
        if (linhaAtual == numeroLinha) {
            if(mode == '+'){
                fprintf(arquivoNovo, "%i,%s,%s,%s,%s,%s,%s,%s\n", clientes.codCliente, clientes.nome, clientes.cpf, clientes.telefone,
                clientes.endereco, clientes.cep, clientes.cidade, clientes.estado);
            } else if(mode == '-') {
                fprintf(arquivoNovo, "%i,usuarioDeletado,000.000.000-0%i,(00)00000-0000,EnderecoDeletado,00000-000,CidadeDeletada,AA\n", clientes.codCliente, clientes.codCliente);
            }
        } else {
            fprintf(arquivoNovo, "%s", buffer);
        }
        linhaAtual++;
        
    }

    fclose(arquivoOriginal);
    fclose(arquivoNovo);

    remove("Clientes.txt");
    rename("temporario.txt", "Clientes.txt");
}

void editar() {
    FILE *arquivoOriginal = fopen("Clientes.txt", "r");
    FILE *arquivoTemporario = fopen("temporario.txt", "w");

    char cpfPesquisado[15];
    printf(" >>> Digite o CPF do cliente que deseja editar: ");
    scanf("%s", cpfPesquisado);

    ClienteTemp clienteEncontrado = pesquisarClientePorCPF(cpfPesquisado, arquivoOriginal);

    if (clienteEncontrado.codCliente == -1) {
        corErro();
        printf("Cliente nao encontrado.\n");
        pausarNotif();
        fclose(arquivoOriginal);
        fclose(arquivoTemporario);
        return;
    }

    formatarCPF(clienteEncontrado.cpf);

    char campoAtualizar[10];
    printf(" >>> Digite o nome do campo que deseja atualizar: ");
    scanf("%s", campoAtualizar);

    char novoValor[30];
    printf(" >>> Digite o novo valor: ");
    getchar();
    fgets(novoValor, sizeof(novoValor), stdin);
    novoValor[strcspn(novoValor, "\n")] = '\0';

    bool estouroBuffer = false;

    if (strcmp(campoAtualizar, "nome") == 0) {
        if(strlen(novoValor) <= 20){
            strcpy(clienteEncontrado.nome, novoValor);
        } else{
            corErro();
            printf(" >>> O nome deve ate 20 digitos!");
            estouroBuffer = true;
            pausarNotif();
        }
    } else if (strcmp(campoAtualizar, "cpf") == 0) {
        if(strlen(novoValor) == 14){
            strcpy(clienteEncontrado.cpf, novoValor);
        } else{
            corErro();
            printf(" >>> O cpf deve conter 14 digitos!");
            estouroBuffer = true;
            pausarNotif();
        }
    } else if (strcmp(campoAtualizar, "telefone") == 0) {
        if(strlen(novoValor) == 14){
            strcpy(clienteEncontrado.telefone, novoValor);
        } else{
            corErro();
            printf(" >>> O telefone deve conter 14 digitos!");
            estouroBuffer = true;
            pausarNotif();
        }
    } else if (strcmp(campoAtualizar, "endereco") == 0) {
        if(strlen(novoValor) <= 30){
            strcpy(clienteEncontrado.endereco, novoValor);
        } else{
            corErro();
            printf(" >>> O endereco deve conter ate 30 digitos!");
            estouroBuffer = true;
            pausarNotif();
        }
    } else if (strcmp(campoAtualizar, "cep") == 0) {
        if(strlen(novoValor) == 9){
            strcpy(clienteEncontrado.cep, novoValor);
        } else{
            corErro();
            printf(" >>> O cep deve conter 9 digitos!");
            estouroBuffer = true;
            pausarNotif();
        }
    } else if (strcmp(campoAtualizar, "cidade") == 0) {
        if(strlen(novoValor) <= 20){
            strcpy(clienteEncontrado.cidade, novoValor);
        } else{
            corErro();
            printf(" >>> A cidade deve conter ate 20 digitos!");
            estouroBuffer = true;
            pausarNotif();
        }
    } else if (strcmp(campoAtualizar, "estado") == 0) {
        if(strlen(novoValor) == 2){
            strcpy(clienteEncontrado.estado, novoValor);
        } else{
            corErro();
            printf(" >>> O estado deve conter 2 digitos!");
            estouroBuffer = true;
            pausarNotif();
        }
    } else {
        corErro();
        printf(" >>>Campo nao encontrado");
        pausarNotif();
        sendToTmpFile(clienteEncontrado, '+');
        fclose(arquivoOriginal);
        fclose(arquivoTemporario);
        remove("Clientes.txt");
        rename("temporario.txt", "Clientes.txt");
        return;
    }

    if(estouroBuffer){
        estouroBuffer = false;
        sendToTmpFile(clienteEncontrado, '+');
        fclose(arquivoOriginal);
        fclose(arquivoTemporario);
        remove("Clientes.txt");
        rename("temporario.txt", "Clientes.txt");
        return;
    }

    sendToTmpFile(clienteEncontrado, '+');
    fclose(arquivoOriginal);
    fclose(arquivoTemporario);
    remove("Clientes.txt");
    rename("temporario.txt", "Clientes.txt");

    corSucesso();
    printf("\n >>>Dado alterado com sucesso!\n");
    pausarNotif();
}

//Apagar
void printApagar(int currentChoice) {
	system("cls");
    corLogo();
    printf("%s\n", logo);
    corMenu();
    printf(" [========================== Modo Apagar ===========================]\n\n");
    maxChoice = 3;

    for (int i = 1; i <= maxChoice; i++) {
        if (i == currentChoice) {
            corSelecionado();
            printf(" %c",16);
        } else {
            corOpcao();
        }

        switch (i) {
            case 1:
            	printf("  [Apagar por CPF]\n");
                break;
            case 2:
            	printf("  [Recuperar por CPF]\n");
                break;
            case 3:
                printf("  [Voltar]\n");
                break;
        }
    }
    corOpcao();
    printf("\n >>> Use as setas ou 'W'/'S' para selecionar uma opcao e pressione 'Enter' para confirmar.\n");
}

void sendToExcl() {
    FILE *arquivoOriginal = fopen("Clientes.txt", "r");
    FILE *arquivoTemporario = fopen("temporario.txt", "w");
    FILE *arquivoExcluidos = fopen("excluidos.txt", "a");

    char cpfPesquisado[15];
    printf(" >>> Digite o CPF do cliente a ser removido: ");
    scanf("%s", cpfPesquisado);

    ClienteTemp clienteEncontrado = pesquisarClientePorCPF(cpfPesquisado, arquivoOriginal);

    if (clienteEncontrado.codCliente == -1) {
        corErro();
        printf(" >>>Cliente nao encontrado.\n");
        pausarNotif();
        fclose(arquivoOriginal);
        fclose(arquivoTemporario);
        fclose(arquivoExcluidos);
        remove("temporario.txt");
        return;
    }

    formatarCPF(clienteEncontrado.cpf);

    sendToTmpFile(clienteEncontrado, '-');

    fprintf(arquivoExcluidos, "%d,%s,%s,%s,%s,%s,%s,%s\n",clienteEncontrado.codCliente, clienteEncontrado.nome, clienteEncontrado.cpf,
    clienteEncontrado.telefone, clienteEncontrado.endereco, clienteEncontrado.cep,clienteEncontrado.cidade, clienteEncontrado.estado);

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);
    fclose(arquivoExcluidos);

    remove("Clientes.txt");
    rename("temporario.txt", "Clientes.txt");

    corSucesso();
    printf("\n >>>Cliente removido.\n");
    pausarNotif();
}

void eraseExcl(ClienteTemp clientes) {
    FILE *arquivoOriginal = fopen("excluidos.txt", "r");
    FILE *arquivoNovo = fopen("tempExcluidos.txt", "w");

    int numeroLinha = clientes.codCliente;

    char buffer[1024];
    int linhaAtual = 0;

    while (fgets(buffer, sizeof(buffer), arquivoOriginal) != NULL) {

        int codigoClienteLinha;
        sscanf(buffer, "%d,", &codigoClienteLinha);

        if (codigoClienteLinha  == clientes.codCliente) {
            fprintf(arquivoNovo, "\n");
        } else {
            fprintf(arquivoNovo, "%s", buffer);
        }
        linhaAtual++;
    }

    fclose(arquivoOriginal);
    fclose(arquivoNovo);

    remove("excluidos.txt");
    rename("tempExcluidos.txt", "excluidos.txt");
}

void takeFromExcl() {
    FILE *arquivoOriginal = fopen("Clientes.txt", "r");
    FILE *arquivoTemporario = fopen("temporario.txt", "w");
    FILE *arquivoExcluidos = fopen("excluidos.txt", "r");

    char cpfPesquisado[15];
    printf(" >>> Digite o CPF do cliente a ser recuperado: ");
    scanf("%s", cpfPesquisado);

    ClienteTemp clienteRecuperado = pesquisarClientePorCPF(cpfPesquisado, arquivoExcluidos);

    if (clienteRecuperado.codCliente == -1) {
        corErro();
        printf(" >>>Cliente nao encontrado nos registros excluidos.\n");
        pausarNotif();
        fclose(arquivoOriginal);
        fclose(arquivoTemporario);
        fclose(arquivoExcluidos);
        return;
    }

    formatarCPF(clienteRecuperado.cpf);

    sendToTmpFile(clienteRecuperado, '+');

    eraseExcl(clienteRecuperado);

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);
    fclose(arquivoExcluidos);

    remove("Clientes.txt");
    rename("temporario.txt", "Clientes.txt");

    corSucesso();
    printf("\n >>>Cliente recuperado.\n");
    pausarNotif();
}

int main() {

    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    int numClientes = 50;
    struct Cliente *clientes = NULL;
    free(clientes);
    clientes = (struct Cliente *)malloc(numClientes * sizeof(struct Cliente));
    setCodCliente();

    char key;
    do {
        printMenu(choice);
        key = _getch();
        escape = false;

        if (key == 13) { //codigo ascii para enter
            switch (choice) {
                case 1:
                	do{
                    	printCadastrar(choice, clientes);
                    	key = _getch();
                    	
                    	if (key == 13){
                    		corSelecionado();
                    		switch (choice) { 
                    			case 1: 
                    				printf(" >>> Digite o codigo do cliente: ");
                    				scanf("%i", &codCliente);
                    				break;
                    			case 2:
                    				printf(" >>> Digite seu nome: ");
                    				fflush(stdin);
                                    fgets(clientes[codCliente].nome, sizeof(clientes[codCliente].nome), stdin);
                                    clientes[codCliente].nome[strcspn(clientes[codCliente].nome, "\n")] = '\0';
                    				break;
                    			case 3:
                                    mascaraCPF(clientes);
                    				break;
                                case 4:
                                    mascaraTelefone(clientes);
                    				break;
                                case 5:
                    				printf(" >>> Digite seu endereco:" );
                    				fflush(stdin);
                                    fgets(clientes[codCliente].endereco, sizeof(clientes[codCliente].endereco), stdin);
                                    clientes[codCliente].endereco[strcspn(clientes[codCliente].endereco, "\n")] = '\0';
                    				break;
                                case 6:
                                    mascaraCEP(clientes);
                    				break;
                                case 7:
                    				printf(" >>> Digite sua cidade:" );
                    				fflush(stdin);
                                    fgets(clientes[codCliente].cidade, sizeof(clientes[codCliente].cidade), stdin);
                                    clientes[codCliente].cidade[strcspn(clientes[codCliente].cidade, "\n")] = '\0';
                    				break;
                                case 8:
                    				printf(" >>> Digite seu Estado:" );
                    				fflush(stdin);
                                    do {
                                        fgets(clientes[codCliente].estado, sizeof(clientes[codCliente].estado), stdin);
                                        clientes[codCliente].estado[strcspn(clientes[codCliente].estado, "\n")] = '\0';
                                        
                                            if (strlen(clientes[codCliente].estado) < 2) {
                                                corErro();
                                                printf(" >>> O Estado deve ter exatamente 2 caracteres!.\n");
                                                corSelecionado();
                                                printf(" >>> Digite seu Estado: ");
                                            }
                                        } while (strlen(clientes[codCliente].estado) < 2);
                    				break;
                                case 9:
                                    sendToTxtFile(clientes);
                                    setCodCliente();
                                    break;
                    			case 10:
                                    choice = 1;
                    				escape = true;
							}
						}
						else if(key == 27){
							escape = true;
						}
						else{
							handleSelection(key);
						}
					}while(!escape);
                    break;
                case 2:
                    do{  
                    	printPesquisar(choice);
                    	key = _getch();
                    	
                    	if (key == 13){
                    		corSelecionado();
                    		switch (choice) { 
                    			case 1: 
                                    procurarCPF();
                    				break;
                                case 2:
                                    printf(" >>> Saindo...");
                                    choice = 1;
                                    escape = true;
                                    break;
							}
						}
						else if(key == 27){
							escape = true;
						}
						else{
							handleSelection(key);
						}
					}while(!escape);
                    break;
                case 3:
                    do{
                    	printEditar(choice);
                    	key = _getch();
                    	
                    	if (key == 13){
                    		corSelecionado();
                    		switch (choice) { 
                    			case 1: 
                                    editar();
                    				break;
                                case 2:
                                    printf(" >>> Saindo...");
                                    choice = 1;
                                    escape = true;
                                    break;
							}
						}
						else if(key == 27){
							escape = true;
						}
						else{
							handleSelection(key);
						}
					}while(!escape);
                    break;
                case 4:
                    do{  
                    	printApagar(choice);
                    	key = _getch();
                    	
                    	if (key == 13){
                    		corSelecionado();
                    		switch (choice) { 
                    			case 1: 
                                    sendToExcl();
                    				break;
                                case 2: 
                                    takeFromExcl();
                    				break;
                                case 3:
                                    printf(" >>> Saindo...");
                                    choice = 1;
                                    escape = true;
                                    break;
							}
						}
						else if(key == 27){
							escape = true;
						}
						else{
							handleSelection(key);
						}
					}while(!escape);
                    break;
                case 5:
                    printf(" Saindo do programa\n");
                    Sleep(10);
                    return 1;
                    break;
            }
        } 
        else if(key == 27){
			return 1;
		}
        else {
            handleSelection(key);
        }
    } while (1);

    return 0;
}