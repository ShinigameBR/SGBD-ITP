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
    while (IsRunning) {
        menu();
        int Option;
        scanf("%d", &Option);
        switch (Option)
        {
        case 0:
            IsRunning = false;
            exitProject();
            break;
        case 1:
            clearDisplay();
            printf("\n\t\t **** Criar Nova Tabela ****\n\n");
            createTable();
            break;
        case 2:
            clearDisplay();
            printf("\n\t\t **** Listagem de Tabelas ****\n\n");
            listTables();
            waitOrExit(15);
            break;
        case 3:
            clearDisplay();
            printf("\n\t\t **** Editor de Tabelas - Nova Entrada ****\n\n");
            createRow();
            break;
        case 4:
            clearDisplay();
            printf("\n\t\t **** Editor de Tabelas - Deletar Entrada ****\n\n");
            deleteRow();
            break;
        case 5:
            clearDisplay();
            printf("\n\t\t **** Editor de Tabelas - Dados da Tabela ****\n\n");
            displayTable();
            break;
        case 6:
            clearDisplay();
            printf("\n\t\t **** Excluir uma Tabela ****\n\n");
            listAndDeleteFiles();
            break;
        case 7:
            clearDisplay();
            aboutUs();
            break;
        default:
            IsRunning = false;
            exitProject();
            break;
        }
    }
    return 0;
}
