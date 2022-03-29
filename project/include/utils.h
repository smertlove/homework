#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <stdio.h>
#include "client_t.h"

void masterWrite(FILE *file, client_t client);
void transactionWrite(FILE *file, client_t transfer);
void blackRecord(FILE *client_db, FILE *transfer_db, FILE *main_db, client_t client, client_t transfer);

#endif // PROJECT_INCLUDE_UTILS_H_
