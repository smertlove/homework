#ifndef PROJECT_INCLUDE_RECORD_MANAGER_H_
#define PROJECT_INCLUDE_RECORD_MANAGER_H_

#include <stdio.h>

#include "client_t.h"

void transactionWrite(FILE *file, client_t transfer);
void masterWrite(FILE *file, client_t client);
void blackRecord(FILE *client_db, FILE  *transfer_db, FILE *main_db, client_t client, client_t transfer);
int get_case_choice(void);
void clean_buffer(void);


#endif // PROJECT_INCLUDE_RECORD_MANAGER_H_