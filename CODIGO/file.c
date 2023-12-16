#ifdef _WIN32
#include <direct.h>
#endif
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "funcs.h"
#include "table.h"

//Função para criar a pasta onde ficam salvas as tabelas
int createDatabaseFolder()
{
    struct stat st = {0};

    // Verifica se o diretório já existe
    if (stat("DATABASE", &st) == -1) {
        // Se não existe, tenta criá-lo
#ifdef _WIN32
        if (_mkdir("../DATABASE") != 0){
#else
            if (mkdir("../DATABASE", 0777) != 0){
#endif
                perror("Erro ao criar o diretório");
                return 1; // Retorna com erro
            }
    }
    return 0; // Retorna sem erros
}

// Função para salvar a tabela em um arquivo
void saveTableToFile(struct Table *table)
{
    if (table == NULL || table->name == NULL || table->columns == NULL || table->entries == NULL) {
        fprintf(stderr, "Erro: Tabela inválida ou nao inicializada.\n");
        return;
    }

    char filePath[MAX_STRING_SIZE];
    snprintf(filePath, sizeof(filePath), "../DATABASE/%s", table->name);

    FILE *file = fopen(filePath, "w+");
    if (file == NULL) {
        fprintf(stderr, "Erro ao criar/abrir o arquivo %s\n", filePath);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Nome da tabela: %s\n", table->name);
    fprintf(file, "Numero de colunas: %d\n", table->numColumns);
    fprintf(file, "Chave primaria: %s - Tipo: %d\n", table->columns[0].name, table->columns[0].type);
    fprintf(file, "Numero de linhas: %d\n", table->numEntries);
    fprintf(file, "Colunas:\n");

    for (int i = 1; i <= table->numColumns; ++i) {
        if (strlen(table->columns[i].name) == 0) {
            break;
        }

        fprintf(file, "  Nome: %s - Tipo: %d\n", table->columns[i].name, table->columns[i].type);
    }

    fprintf(file, "Linhas:\n");

    if (table->numEntries > 0) {
        for (int i = 0; i < table->numEntries; ++i) {
            fprintf(file, "  ");
            for (int j = 0; j <= table->numColumns; ++j) {
                if (strlen(table->entries[i].columns[j].name) == 0) {
                    break;
                }
                fprintf(file, "- %s ", table->entries[i].columns[j].name);
            }
            fprintf(file, "-\n");
        }
    }

    fflush(file);
    fclose(file);
    waitWithMessage(3, "Estamos salvando seu arquivo.");
}

// Função para carregar uma tabela de um arquivo
void readTableFromFile(struct Table *table, char *filename)
{
    if (table == NULL) {
        fprintf(stderr, "Erro: Tabela nao inicializada.\n");
        return;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    fscanf(file, "Nome da tabela: %s\n", table->name);

    fscanf(file, "Numero de colunas: %d\n", &(table->numColumns));
    // Alocar memória para as colunas
    table->columns = malloc((table->numColumns + 1) * sizeof(struct Column));
    
    int type;
    fscanf(file, "Chave primaria: %s - Tipo: %d\n", table->columns[0].name, &type);
    table->columns[0].type = (enum DataType)type;

    fscanf(file, "Numero de linhas: %d\n", &table->numEntries);
    // Alocar memória para as entradas
    table->entries = malloc(table->numEntries * sizeof(struct Entry));

    // Ler as colunas
    fscanf(file, "Colunas:\n");
    for (int i = 1; i <= table->numColumns; ++i) {
        fscanf(file, "  Nome: %s - Tipo: %d\n", table->columns[i].name, &table->columns[i].type);
    }
    // Ler as entradas
    fscanf(file, "Linhas:\n");
    for (int i = 0; i < table->numEntries; ++i) {
        table->entries[i].columns = malloc((table->numColumns + 1) * sizeof(struct Column));
        for (int j = 0; j < table->numColumns + 1; ++j) {
            if (fscanf(file, "- %s ", table->entries[i].columns[j].name) != 1) {
                break;
            }
        }
        fscanf(file, "-\n");
    }

    fclose(file);
}

// Função para adicionar uma entrada na tabela
void addNewRow(struct Table *table)
{
    if (table == NULL || table->columns == NULL || table->entries == NULL) {
        fprintf(stderr, "Erro: Tabela invalida ou nao inicializada.\n");
        return;
    }

    // Alocar memória para a nova entrada
    table->entries = realloc(table->entries, (table->numEntries + 1) * sizeof(struct Entry));

    // Alocar memória para as colunas da nova entrada
    table->entries[table->numEntries].columns = malloc((table->numColumns + 1) * sizeof(struct Column));

    // Verificar a chave primária
    clearDisplay();
    printf("Digite o valor para chave primaria: ");
    char primaryKeyValue[MAX_STRING_SIZE];
    scanf("%s", primaryKeyValue);

    for (int i = 0; i < table->numEntries; ++i) {
        if (strcmp(table->entries[i].columns[0].name, primaryKeyValue) == 0) {
            printf("Erro: Chave primaria duplicada. O registro nao sera inserido.\n");
            return;
        }
    }
    strcpy(table->entries[table->numEntries].columns[0].name, primaryKeyValue);

    // Solicitar valores para cada coluna
    for (int i = 1; i <= table->numColumns ; ++i) {
        clearDisplay();
        printf("Digite o valor para a coluna %s: ", table->columns[i].name);
        scanf("%s", table->entries[table->numEntries].columns[i].name);
    }
    clearDisplay();

    // Incrementar o número de entradas
    table->numEntries++;

    saveTableToFile(table);
    printf("Registro adicionado com sucesso!\n");
}

// Função para mostrar as linhas da tabela
void showTableRows(struct Table *table) {
    printf("Linhas da tabela:\n");

    if (table->numEntries > 0) {
        for (int i = 0; i < table->numEntries; ++i) {
            printf("  %s: %s | ", table->columns[0].name, table->entries[i].columns[0].name);
            for (int j = 0; j < table->numColumns; ++j) {
                printf("%s: %s | ", table->columns[j + 1].name, table->entries[i].columns[j + 1].name);
            }
            printf("\n");
        }
    }
    else {
        printf("A tabela esta vazia.\n");
    }
}

// Função para apagar uma linha com base no ID
void deleteRowById(struct Table *table) 
{
    clearDisplay();
    char idToDelete[MAX_STRING_SIZE];
    showTableRows(table);

    printf("\nDigite o ID da linha que deseja apagar: ");
    scanf("%s", &idToDelete);

    if (atoi(idToDelete) <= 0) {
        printf("ID invalido. Operacao cancelada.\n");
        return;
    }

    for (int i = 0; i < table->numEntries; i++)
    {
        if (strcmp(table->entries[i].columns[0].name, idToDelete) == 0)
        {
            // Liberando a memória alocada para a entrada a ser deletada
            free(table->entries[i].columns);
        }
    }
    

    // Movendo as entradas subsequentes para preencher o espaço da entrada deletada
    for (int i = 0; i < table->numEntries - 1; ++i) {
        table->entries[i] = table->entries[i + 1];
    }

    // Reduzindo o número de entradas na tabela
    table->numEntries--;

    //Salvando a tabela
    saveTableToFile(table);
    printf("Linha deletada com sucesso.\n");
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

    if (remove(filePath) == 0) {
        printf("Tabela excluida com sucesso.\n");
    }
    else {
        printf("Erro ao excluir o arquivo");
    }
}