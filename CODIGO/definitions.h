#ifndef definitions_h
#define definitions_h

#define MAX_STRING_SIZE 256
// Definindo tipos de dados possíveis para as colunas
enum DataType {
    C_CHAR,
    C_INT,
    C_FLOAT,
    C_DOUBLE,
    C_STRING
};

//Definindo a estrutura das linhas
struct Entry {
    struct Column *columns;
};

// Definindo a estrutura da coluna
struct Column {
    char name[MAX_STRING_SIZE];  // Nome da coluna
    enum DataType type;  // Tipo de dado da coluna
};

// Definindo a estrutura da tabela
struct Table {
    char name[MAX_STRING_SIZE];  // Nome da tabela
    int numColumns; // Número de colunas
    int numEntries;  // Número de linhas
    struct Column *columns;  // Array de colunas (pode ajustar o tamanho conforme necessário)
    struct Entry *entries;  // Array de linhas
};

#endif