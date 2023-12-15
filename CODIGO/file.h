#ifndef file_h
#define file_h

int createDatabaseFolder();
void saveTableToFile(struct Table table);
void listAndDeleteFiles();
struct Table loadTableFromFile(const char *filepath);
void addEntryToTable();

#endif