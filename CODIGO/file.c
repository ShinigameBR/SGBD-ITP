#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "funcs.h"
#include "table.h"

// Mapeamento de enum para texto
const char *DataTypeText[] = {
    "caracter",
    "inteiro",
    "float",
    "double",
    "string",
};

int createDatabaseFolder()
{
    // Verifica se a pasta já existe
    struct stat st = {0};
    if (stat("DATABASE", &st) == -1)
    {
#ifdef _WIN32
        // Se estiver no Windows, use _mkdir
        if (_mkdir("../DATABASE") != 0)
        {
#else
        // Caso contrário, use mkdir (para sistemas compatíveis com POSIX)
        if (mkdir("../DATABASE", 0777) != 0)
        {
#endif
            return 1;
        }
    }
    return 0; // Retorna sem erros
}

// Função para salvar a tabela em um arquivo
void saveTableToFile(struct Table table)
{
    char caminhoArquivo[MAX_STRING_SIZE];
    snprintf(caminhoArquivo, sizeof(caminhoArquivo), "../DATABASE/%s", table.name);

    FILE *file = fopen(caminhoArquivo, "w"); // Abre o arquivo para escrita ("w")

    if (file == NULL)
    {
        printf("Erro ao criar o arquivo");
        exit(EXIT_FAILURE);
    }

    // Escreve os detalhes da tabela no arquivo
    fprintf(file, "Nome da tabela: %s\n", table.name);
    fprintf(file, "Chave primaria: %s - Tipo: %d\n", table.columns[0].name, table.columns[0].type);
    fprintf(file, "Numero de colunas: %d\n", table.numColumns);
    fprintf(file, "Numero de linhas: %d\n", table.numEntries);
    fprintf(file, "Colunas:\n");

    for (int i = 1; i <= table.numColumns; ++i)
    {
        if (strlen(table.columns[i].name) == 0)
        {
            break;
        }

        fprintf(file, "  Nome: %s - Tipo: %d\n", table.columns[i].name, table.columns[i].type);
    }
    fprintf(file, "Linhas:\n");

    // Não há entradas ao criar a tabela
    if (table.numEntries > 0)
    {
        for (int i = 0; i < table.numEntries; ++i)
        {
            fprintf(file, "  ");
            for (int j = 0; j < table.numColumns; ++j)
            {
                if (strlen(table.entries[i].columns[j].name) == 0)
                {
                    break;
                }
                fprintf(file, "%s - ", table.entries[i].columns[j].name);
            }
            fprintf(file, "%s\n", table.entries[i].columns[table.numColumns].name);
        }
    }

    fclose(file); // Fecha o arquivo
    free(table.columns);
    free(table.entries);
    WaitWithMessage(3, "Estamos salvando seu arquivo.");
}

// Função para carregar uma tabela de um arquivo
struct Table loadTableFromFile(const char *filepath)
{
    struct Table table;

    FILE *file = fopen(filepath, "r"); // Abre o arquivo para leitura ("r")
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Lê os detalhes da tabela do arquivo
    fscanf(file, "Nome da tabela: %s\n", table.name);

    char primaryKeyName[MAX_STRING_SIZE];
    int primaryKeyType;
    fscanf(file, "Chave primaria: %s - Tipo: %d\n", primaryKeyName, &primaryKeyType);

    table.columns = (struct Column *)malloc(1 * sizeof(struct Column));

    strcpy(table.columns[0].name, primaryKeyName);
    table.columns[0].type = (enum DataType)primaryKeyType;
    fscanf(file, "Numero de colunas: %d\n", &table.numColumns);
    
    fscanf(file, "Numero de linhas: %d\n", &table.numEntries);
    table.entries = (struct Entry *)malloc((table.numEntries + 1) * sizeof(struct Entry));

    fscanf(file, "Colunas:\n");

    for (int i = 1; i <= table.numColumns; ++i)
    {
        fscanf(file, "  Nome: %s - Tipo: %d\n", table.columns[i].name, &table.columns[i].type);
    }

    fscanf(file, "Linhas:\n");
    if (table.numEntries > 0)
    {
        for (int i = 0; i < table.numEntries; ++i)
        {
            fscanf(file, "  ");
            for (int j = 0; j < table.numColumns; ++j)
            {
                fscanf(file, "  %s - ", table.entries[i].columns[j].name);
            }
            fscanf(file, "%s\n", table.entries[i].columns[table.numColumns].name);
        }
    }

    fclose(file); // Fecha o arquivo

    return table;
}

// Função para adicionar uma entrada na tabela
void addEntryToTable()
{
    printf("Tabelas disponiveis para adicionar uma nova linha:\n");
    listTables();

    char fileNameToEdit[MAX_STRING_SIZE];
    printf("\nDigite o nome da tabela que deseja adicionar uma nova linha: ");
    scanf("%s", fileNameToEdit);

    char filePath[MAX_STRING_SIZE];
    snprintf(filePath, sizeof(filePath), "../DATABASE/%s", fileNameToEdit);

    struct Table table = loadTableFromFile(filePath);
    ClearDisplay();

    table.entries = (struct Entry *)realloc(table.entries, (table.numEntries + 1) * sizeof(struct Entry));
    snprintf(table.entries[table.numEntries].columns[0].name, MAX_STRING_SIZE, "%d", table.numEntries + 1);
    table.entries[table.numEntries].columns[0].type = 0;

    for (int i = 1; i <= table.numColumns; ++i)
    {
        printf("Digite o valor para a coluna %s do tipo %s: ", table.columns[i].name, DataTypeText[table.columns[i].type]);
        table.entries[table.numEntries].columns[i].type = table.columns[i].type;
        switch (table.columns[i].type)
        {
        case 0:
            scanf(" %c", &table.entries[table.numEntries].columns[i].name);
            break;
        case 1:
            scanf("%d", &table.entries[table.numEntries].columns[i].name);
            break;
        case 2:
            scanf("%f", &table.entries[table.numEntries].columns[i].name);
            break;
        case 3:
            scanf("%lf", &table.entries[table.numEntries].columns[i].name);
            break;
        case 4:
            scanf("%s", table.entries[table.numEntries].columns[i].name);
            break;
        default:
            printf("Tipo de dado desconhecido\n");
            exit(EXIT_FAILURE);
        }
    }
    table.numEntries += 1;
    saveTableToFile(table);
    free(table.columns);
    free(table.entries);
}

// Função para listar e perguntar ao usuário qual arquivo excluir
void listAndDeleteFiles()
{
    printf("Tabelas disponiveis para exclusao:\n");
    listTables();

    char fileNameToDelete[MAX_STRING_SIZE];
    printf("\nDigite o nome da tabela que deseja excluir: ");
    scanf("%s", fileNameToDelete);

    char filePath[MAX_STRING_SIZE];
    snprintf(filePath, sizeof(filePath), "../DATABASE/%s", fileNameToDelete);

    if (remove(filePath) == 0)
    {
        printf("Tabela excluida com sucesso.\n");
    }
    else
    {
        printf("Erro ao excluir o arquivo");
    }
}