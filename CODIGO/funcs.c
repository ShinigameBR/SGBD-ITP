#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "definitions.h"
#include "funcs.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#define Espera(segundos) Sleep(segundos * 1000)
#define Limpar() system("cls");
#elif __unix__
#include <unistd.h>
#define Espera(segundos) sleep(segundos)
#define Limpar() system("clear");
#else
#error "Sistema operacional nao suportado"
#endif

void menu()
{
    Limpar();
    printf("\t\t\tMENU PRINCIPAL\n");
    printf("\t\t=======================\n");
    printf("\t\t[1] Criar nova tabela.\n");
    printf("\t\t[2] Listar todas as tabelas.\n");
    printf("\t\t[3] Adicionar linha em uma tabela.\n");
    printf("\t\t[4] Apagar linha em uma tabela.\n");
    printf("\t\t[5] Mostrar todos os dados de uma tabela.\n");
    printf("\t\t[6] Excluir tabela.\n");
    // printf("\t\t[6] Pesquisar um dado em uma tabela.\n"); :/

    printf("\t\t[7] Sobre.\n");
    printf("\t\t[0] Sair.\n");
    printf("\t\t=======================\n");
    printf("\t\tDigite sua escolha: ");
}

void aboutUs()
{
    Limpar();
    printf("\n\t\t **** Sobre ****\n\n");
    printf(" Algumas observacoes importantes que voce deve lembrar:\n");
    printf(" -> Este e um projeto simples de sistema de gerenciamento de banco de dados.\n");
    printf(" -> Voce pode modificar o codigo-fonte como quiser.\n");
    printf(" -> Voce pode usar este projeto apenas para quaisquer fins, se possivel de os creditos.\n\n");

    printf(" ->> Visite https://github.com/ShinigameBR e https://github.com/Iuques para mais projetos como este. <<-\n\n");
    waitOrExit(20);
}

void exitProject()
{
    clearDisplay();
    char ThankYou[100] = " ========= Obrigado por usar! =========\n";
    char SeeYouSoon[100] = " ========= Ate a proxima vez. =========\n";

    // Usar size_t para i
    for (size_t i = 0; i < strlen(ThankYou); i++) {
        printf("%c", ThankYou[i]);
#ifdef _WIN32
        Espera(0.2);
#elif __unix__
        Espera(2);
#endif
    }

    // Usar size_t para i
    for (size_t i = 0; i < strlen(SeeYouSoon); i++) {
        printf("%c", SeeYouSoon[i]);
#ifdef _WIN32
        Espera(0.2);
#elif __unix__
        Espera(2);
#endif
    }

    clearDisplay();
    exit(0);
}

void waitOrExit(int segundos)
{
    #ifdef _WIN32
    for (int i = 0; i < segundos; i++) {
        printf("Aguardando %d segundos... Pressione uma tecla para sair.\r", segundos - i);
        fflush(stdout);
        Espera(1);
        
        if (kbhit()) {
            printf("Tecla pressionada. Saindo...\n");
            return;
        }
    }
    #elif __unix__
        for (int i = 0; i < segundos; i++) {
        printf("Aguardando %d segundos...\r", segundos - i);
        fflush(stdout);
        Espera(1);
    }
    #endif

    printf("\n");
}

void waitWithMessage(int segundos, char *message)
{
    if (message) {
        printf("%s\n", message);
    }
    for (int i = 0; i < segundos; i++) {
        printf("Aguardando %d segundos...\r", segundos - i);
        fflush(stdout);
        Espera(1);
    }
    printf("\n");
}

void clearDisplay()
{
    fflush(stdout);
    fflush(stdin);
    Limpar();
}
