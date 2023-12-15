#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "definitions.h"
#include "file.h"
#include "funcs.h"

// Função para criar uma tabela
void createTable()
{
    struct Table table;

    printf("Digite o nome da tabela: ");
    scanf("%s", table.name);
    
    printf("Digite o numero de colunas (sem contar a chave primaria): ");
    scanf("%d", &table.numColumns);
    int numColumns = table.numColumns + 1;
    //Alocando memória para o número de colunas digitado
    table.columns = (struct Column *)malloc((numColumns) * sizeof(struct Column));
    //Deixando as entradas de dados vazias por enquanto
    table.entries = (struct Entry *)malloc((1) * sizeof(struct Entry));
    table.numEntries = 0;

    printf("Digite um nome de coluna para ser a chave primaria: ");
    scanf("%s", table.columns[0].name);
    //Pondo a chave primaria como inteiro
    table.columns[0].type = (enum DataType)1;

    for (int i = 1; i <= table.numColumns; ++i)
    {
        ClearDisplay();
        printf("Digite o nome da coluna %d: ", i);
        scanf("%s", table.columns[i].name);

        printf("Digite o tipo da coluna %d (0: char, 1: int, 2: float, 3: double, 4: string): ", i);
        int type;
        scanf("%d", &type);
        table.columns[i].type = (enum DataType)type;
    }

    saveTableToFile(table);
    free(table.columns);
    free(table.entries);
}

// Função para listar as tabelas
void listTables()
{
    DIR *dir;
    struct dirent *ent;

    // Abre o diretório "DATABASE"
    if ((dir = opendir("../DATABASE")) != NULL)
    {
        // Lê todos os arquivos no diretório
        while ((ent = readdir(dir)) != NULL)
        {
            // Ignora os diretórios '.' e '..'
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
            {
                // Assume que todos os arquivos no diretório são tabelas
                printf("- %s\n", ent->d_name);
            }
        }
        closedir(dir);
    }
    else
    {
        // Se não for possível abrir o diretório, exibe uma mensagem de erro
        printf("Nao foram encontradas tabelas.");
    }
}



// Função para exibir os detalhes da tabela
void displayTable()
{
    printf("Tabelas disponiveis para leitura:\n");
    listTables();
    
    char fileNameToShow[MAX_STRING_SIZE];
    printf("\nDigite o nome da tabela que deseja visualizar: ");
    scanf("%s", fileNameToShow);


    char filePath[MAX_STRING_SIZE];
    snprintf(filePath, sizeof(filePath), "../DATABASE/%s", fileNameToShow);

    ClearDisplay();
    struct Table table = loadTableFromFile(filePath);

    printf("Nome da tabela: %s\n", table.name);
    printf("Chave primaria: %s, Tipo: %d\n", table.columns[0].name, table.columns[0].type);
    printf("Numero de colunas: %d\n", table.numColumns);
    printf("Colunas:\n");

    for (int i = 1; i <= table.numColumns; ++i)
    {
        if (strlen(table.columns[i].name) == 0)
        {
            break;
        }

        printf("  Nome: %s, Tipo: %d\n", table.columns[i].name, table.columns[i].type);
    }

    printf("\n");
    WaitOrExit(15);
}