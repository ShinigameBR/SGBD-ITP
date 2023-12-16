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

    for (int i = 1; i <= table.numColumns; ++i) {
        clearDisplay();
        printf("Digite o nome da coluna %d: ", i);
        scanf("%s", table.columns[i].name);

        int type = 5;
        //Checando o tipo de dado da coluna
        while (!(type >= 0 && type <= 4)) {
            printf("Digite o tipo da coluna %d (0: char, 1: int, 2: float, 3: double, 4: string): ", i);
            scanf("%d", &type);
            if (!(type >= 0 && type <= 4)) {
                clearDisplay();
                printf("Valor invalido, tente novamente.\n");
            }
        }
        table.columns[i].type = (enum DataType)type;
    }

    //Salva a tabela no arquivo
    saveTableToFile(&table);
}

// Função para listar as tabelas
void listTables()
{
    DIR *dir;
    struct dirent *ent;

    // Abre o diretório "DATABASE"
    if ((dir = opendir("../DATABASE")) != NULL) {
        // Lê todos os arquivos no diretório
        while ((ent = readdir(dir)) != NULL) {
            // Ignora os diretórios '.' e '..'
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
                // Assume que todos os arquivos no diretório são tabelas
                printf("- %s\n", ent->d_name);
            }
        }
        closedir(dir);
    }
    else {
        // Se não for possível abrir o diretório, exibe uma mensagem de erro
        printf("Nao foram encontradas tabelas.");
    }
}

// Função para adicionar linha
void createRow()
{
    printf("Tabelas disponiveis para adicionar linha:\n");
    listTables();

    char fileNameToAddRow[MAX_STRING_SIZE];
    printf("\nDigite o nome da tabela que deseja adicionar uma nova linha: ");
    scanf("%s", fileNameToAddRow);

    // Determinando o pathing da tabela na qual será adicionada uma linha
    char filePath[MAX_STRING_SIZE];
    snprintf(filePath, sizeof(filePath), "../DATABASE/%s", fileNameToAddRow);

    struct Table table;
    
    // Abrindo o arquivo e adicionando a linha
    readTableFromFile(&table, filePath);
    addNewRow(&table);
}

// Função para apagar uma linha de uma tabela
void deleteRow()
{
    printf("Tabelas disponiveis para apagar linha:\n");
    listTables();

    char fileNameToDelteRow[MAX_STRING_SIZE];
    printf("\nDigite o nome da tabela que deseja apagar uma linha: ");
    scanf("%s", fileNameToDelteRow);

    // Determinando o pathing da tabela na qual será apagada uma linha
    char filePath[MAX_STRING_SIZE];
    snprintf(filePath, sizeof(filePath), "../DATABASE/%s", fileNameToDelteRow);

    struct Table table;
    
    // Abrindo o arquivo e apagando a linha
    readTableFromFile(&table, filePath);
    deleteRowById(&table);

}

// Função para exibir os detalhes da tabela
void displayTable()
{
    struct Table table;

    printf("Tabelas disponiveis para mostrar:\n");
    listTables();

    char fileNameToShow[MAX_STRING_SIZE];
    printf("\nDigite o nome da tabela que deseja visualizar: ");
    scanf("%s", fileNameToShow);

    char filePath[MAX_STRING_SIZE];
    snprintf(filePath, sizeof(filePath), "../DATABASE/%s", fileNameToShow);
    readTableFromFile(&table, filePath);

    // Exibir os dados lidos
    printf("Nome da tabela: %s\n", table.name);
    printf("Numero de colunas: %d\n", table.numColumns);
    printf("Numero de linhas: %d\n", table.numEntries);

    // Exibir as colunas
    printf("Colunas:\n");
    for (int i = 0; i <= table.numColumns; ++i) {
        printf("  Nome: %s - Tipo: %d\n", table.columns[i].name, table.columns[i].type);
    }

    // Exibir as entradas
    showTableRows(&table);
    waitOrExit(15);

    // Liberar a memória alocada
    free(table.columns);
    for (int i = 0; i < table.numEntries; ++i) {
        free(table.entries[i].columns);
    }
    free(table.entries);
}