#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

char logo[] =
        " /## /########                           /##                          \n"
        "|__/|__  ##__/                          | ##                          \n"
        " /##   | ##  /######  /######   /#######| ##   /##  /######   /###### \n"
        "| ##   | ## /##__  ##|____  ## /##_____/| ##  /##/ /##__  ## /##__  ##\n"
        "| ##   | ##| ##  \\__/ /#######| ##      | ######/ | ########| ##  \\__/ \n"
        "| ##   | ##| ##      /##__  ##| ##      | ##_  ## | ##_____/| ##      \n"
        "| ##   | ##| ##     |  #######|  #######| ## \\  ##|  #######| ##      \n"
        "|__/   |__/|__/      \\_______/ \\_______/|__/  \\__/ \\_______ |__/      \n";

int choice = 1;
int maxChoice = 5;
bool escape = false;

//info
/*
int codCliente;
char nome[20];
char cpf[14];
char telefone[14];
char endereco[30];
char cep[9];
char cidade[20];
char estado[2];
*/

int codCliente = 1;

struct Cliente {
    char nome[20];
    char cpf[14];
    char telefone[14];
    char endereco[30];
    char cep[9];
    char cidade[20];
    char estado[2];
};


//stupid stuff
int k;
double sin() ,cos();


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
    printf("%s\n", logo);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("[=========================== Menu Inicial ============================]\n\n");
    
    maxChoice = 6;

    for (int i = 1; i <= maxChoice; i++) {
        if (i == currentChoice) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        } else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | 0);
        }
        switch (i) {
            case 1:
                printf("<< [Cadastrar] >>\n");
                break;
            case 2:
                printf("<< [Pesquisar] >>\n");
                break;
            case 3:
                printf("<< [Editar]    >>\n");
                break;
            case 4:
                printf("<< [Donut!]    >>\n");
                break;
            case 5:
                printf("<< [Apagar]    >>\n");
                break;
            case 6:
                printf("<< [Sair]      >>\n");
                break;
        }
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | 0);
    //printf("\n>>> Use as setas ou 'W'/'S' para selecionar uma opcao e pressione 'Enter' para confirmar:\n");
    printf("\n[w/s]:mover [Esc]:voltar\n[Enter]: Selecionar\n");
}

void printCadastrar(int currentChoice, Cliente *clientes) { 
    system("cls");
    printf("%s\n", logo);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("[========================== Modo Cadastrar ===========================]\n\n");
    
    maxChoice = 12;

    for (int i = 1; i <= maxChoice; i++) {
        if (i == currentChoice) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        } else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | 0);
        }

        switch (i) {
            case 1:
            	printf(" [Codigo do cliente].: %i\n", codCliente - 1);
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
                printf(" [Estado]............: %s\n", clientes[codCliente].estado);
                break;
            case 9:
                printf(" [Observacao]........: \n\n");
                break;
            case 10:
                printf(" [Registrar]\n");
                break;
            case 11:
                printf(" [Apagar]\n");
                break;
            case 12:
                printf(" [Voltar]\n");
                break;
        }
    }
    
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | 0);
    printf("\n>>> Use as setas ou 'W'/'S' para selecionar uma opcao e pressione 'Enter' para confirmar:\n");
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

void printDonut() {
	
	float A=0, B=0, i, j, z[1760];
    char b[1760];
    system("cls");
    for(; ; ) {
        memset(b,32,1760);
        memset(z,0,7040);
        for(j=0; 6.28>j; j+=0.07) {
            for(i=0; 6.28 >i; i+=0.02) {
                float sini=sin(i),
                      cosj=cos(j),
                      sinA=sin(A),
                      sinj=sin(j),
                      cosA=cos(A),
                      cosj2=cosj+2,
                      mess=1/(sini*cosj2*sinA+sinj*cosA+5),
                      cosi=cos(i),
                      cosB=cos(B),
                      sinB=sin(B),
                      t=sini*cosj2*cosA-sinj* sinA;
                int x=40+30*mess*(cosi*cosj2*cosB-t*sinB),
                    y= 12+15*mess*(cosi*cosj2*sinB +t*cosB),
                    o=x+80*y,
                    N=8*((sinj*sinA-sini*cosj*cosA)*cosB-sini*cosj*sinA-sinj*cosA-cosi *cosj*sinB);
                if(22>y&&y>0&&x>0&&80>x&&mess>z[o]){
                    z[o]=mess;
                    b[o]=".,-~:;=!*#$@"[N>0?N:0];
                }
            }
        }
        printf("\x1b[d");
        for(k=0; 1761>k; k++)
            putchar(k%80?b[k]:10);
        A+=0.04;
        B+= 0.02;
    }
}

void sendToTxt(Cliente *clientes) {
    FILE *arquivoOriginal = fopen("test2.txt", "r");
    FILE *arquivoNovo = fopen("temporario.txt", "w");

    int numeroLinha = codCliente - 1;

    char buffer[1024];
    int linhaAtual = 0;

    while (fgets(buffer, sizeof(buffer), arquivoOriginal) != NULL) {
        if (linhaAtual == numeroLinha) {
            fprintf(arquivoNovo, "%i,%s,%s,%s,%s,%s,%s,%s\n", codCliente-1, clientes[codCliente].nome, clientes[codCliente].cpf, clientes[codCliente].telefone, clientes[codCliente].endereco, clientes[codCliente].cep, clientes[codCliente].cidade, clientes[codCliente].estado);
        } else {
            fprintf(arquivoNovo, "%s", buffer);
        }
        linhaAtual++;
    }

    fclose(arquivoOriginal);
    fclose(arquivoNovo);

    remove("test2.txt");
    rename("temporario.txt", "test2.txt");
}

void setCodCliente(){
    FILE *arquivo = fopen("test2.txt", "r");

    char buffer[1024];
    int numeroLinha = 0;

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        numeroLinha++;

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        if (strlen(buffer) == 0) {
            codCliente = numeroLinha;
            break;
        }
    }

    fclose(arquivo);
}


int main() {

    int numClientes = 100;
    struct Cliente *clientes = NULL;
    free(clientes);
    clientes = (struct Cliente *)malloc(numClientes * sizeof(struct Cliente));
    setCodCliente();

    char key;
    do {
    	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN); 
        printMenu(choice);
        key = _getch();
        escape = false;

        if (key == 13) { // 13 codigo ASCII para Enter
            switch (choice) {
                case 1:
                	do{
                		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);   
                    	printCadastrar(choice, clientes);
                    	key = _getch();
                    	
                    	if (key == 13){
                    		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    		switch (choice) { 
                    			case 1: 
                    				printf(">>> Digite o codigo do cliente: ");
                    				scanf("%i", &codCliente);
                    				break;
                    			case 2:
                    				printf(">>> Digite seu nome: ");
                    				scanf("%s", &clientes[codCliente].nome);
                    				break;
                    			case 3:
                    				printf(">>> Digite seu CPF:" );
                    				scanf(" %s", &clientes[codCliente].cpf);
                    				break;
                                case 4:
                    				printf(">>> Digite seu Telefone:" );
                    				scanf(" %s", &clientes[codCliente].telefone);
                    				break;
                                case 5:
                    				printf(">>> Digite seu endereco:" );
                    				scanf(" %s", &clientes[codCliente].endereco);
                    				break;
                                case 6:
                    				printf(">>> Digite seu cep:" );
                    				scanf(" %s", &clientes[codCliente].cep);
                    				break;
                                case 7:
                    				printf(">>> Digite sua cidade:" );
                    				scanf(" %s", &clientes[codCliente].cidade);
                    				break;
                                case 8:
                    				printf(">>> Digite seu estado:" );
                    				scanf(" %s", &clientes[codCliente].estado);
                    				break;
                                case 10:
                                    setCodCliente();
                                    sendToTxt(clientes);
                                    break;
                                    
                    			case 12:
                    				printf(">>> Saindo...");
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
                    printPesquisar();
                    break;
                case 3:
                    printEditar();
                    break;
                case 4:
                    printDonut();
                    break;
                case 5:
                    printApagar();
                    break;
                case 6:
                    printf("Saindo do programa\n");
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

