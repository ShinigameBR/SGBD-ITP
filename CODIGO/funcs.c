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
    #include <termios.h>
    #include <fcntl.h>
    #define Espera(segundos) sleep(segundos)
    #define Limpar() system("clear");
#else
    #error "Sistema operacional nao suportado"
#endif

int kbhit() {
#ifdef _WIN32
    return _kbhit();
#elif __unix__
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
#endif
}

void Menu()
{
    Limpar();
    printf("\t\t\tMENU PRINCIPAL\n");
    printf("\t\t=======================\n");
    printf("\t\t[1] Criar nova tabela.\n");
    printf("\t\t[2] Listar todas as tabelas.\n");
    printf("\t\t[3] Adicionar linha em uma tabela.\n");
    // printf("\t\t[4] Apagar linha em uma tabela.\n");
    printf("\t\t[5] Mostrar todos os dados de uma tabela.\n");
    // printf("\t\t[6] Pesquisar um dado em uma tabela.\n");

    printf("\t\t[8] Excluir tabela.\n");
    printf("\t\t[9] Sobre.\n");
    printf("\t\t[0] Sair.\n");
    printf("\t\t=======================\n");
    printf("\t\tDigite sua escolha: ");
}

void AboutUs()
{
    Limpar();
    printf("\n\t\t **** Sobre ****\n\n");
    printf(" Algumas observacoes importantes que voce deve lembrar:\n");
    printf(" -> Este e um projeto simples de sistema de gerenciamento de banco de dados.\n");
    printf(" -> Voce pode modificar o codigo-fonte como quiser.\n");
    printf(" -> Voce pode usar este projeto apenas para quaisquer fins, se possivel de os creditos.\n\n");

    printf(" ->> Visite https://github.com/ShinigameBR para mais projetos como este. <<-\n\n");
    WaitOrExit(20);
}

void ExitProject()
{
    Limpar();
    char ThankYou[100] = " ========= Obrigado por usar! =========\n";
    char SeeYouSoon[100] = " ========= Ate a proxima vez. =========\n";
    for (int i = 0; i < strlen(ThankYou); i++)
    {
        printf("%c", ThankYou[i]);
        Espera(0.2);
    }
    for (int i = 0; i < strlen(SeeYouSoon); i++)
    {
        printf("%c", SeeYouSoon[i]);
        Espera(0.2);
    }
    Limpar();
    exit(0);
}

void WaitOrExit(int segundos) {
    for (int i = 0; i < segundos; i++) {
        printf("Aguardando %d segundos... Pressione uma tecla para sair.\r", segundos - i);
        fflush(stdout);
        Espera(1);
        if (kbhit()) {
            printf("Tecla pressionada. Saindo...\n");
            return;
        }
    }
    printf("\n");
}

void WaitWithMessage(int segundos, char *message) {
    if(message){
        printf("%s\n", message);
    }
    for (int i = 0; i < segundos; i++) {
        printf("Aguardando %d segundos...\r", segundos - i);
        fflush(stdout);
        Espera(1);
    }
    printf("\n");
}

void ClearDisplay(){
    fflush(stdout);
    fflush(stdin);
    Limpar();
}
