#ifndef file_h
#define file_h

int createDatabaseFolder();
void saveTableToFile(struct Table *table);
void readTableFromFile(struct Table *table, char *filename);
void listAndDeleteFiles();
void addNewRow(struct Table *table);
void showTableRows(struct Table *table);
void deleteRowById(struct Table *table);

#endif