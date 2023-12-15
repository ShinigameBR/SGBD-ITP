#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "definitions.h"
#include "file.h"
#include "funcs.h"
#include "table.h"

bool IsRunning = true;

int main()
{
    createDatabaseFolder();
    while (IsRunning)
    {
        Menu();
        int Option;
        scanf("%d", &Option);
        switch (Option)
        {
        case 0:
            IsRunning = false;
            ExitProject();
            break;
        case 1:
            ClearDisplay();
            printf("\n\t\t **** Criar Nova Tabela ****\n\n");
            createTable();
            break;
        case 2:
            ClearDisplay();
            printf("\n\t\t **** Listagem de Tabelas ****\n\n");
            listTables();
            WaitOrExit(15);
            break;
        case 3:
            ClearDisplay();
            printf("\n\t\t **** Editor de Tabelas - Nova Entrada ****\n\n");
            addEntryToTable();
            break;

        case 5:
            ClearDisplay();
            printf("\n\t\t **** Dados da Tabela ****\n\n");
            displayTable();
            break;
        case 8:
            ClearDisplay();
            printf("\n\t\t **** Excluir uma Tabela ****\n\n");
            listAndDeleteFiles();
            break;
        case 9:
            ClearDisplay();
            AboutUs();
            break;
        default:
            IsRunning = false;
            ExitProject();
            break;
        }
    }
    return 0;
}
