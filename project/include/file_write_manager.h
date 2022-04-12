#ifndef PROJECT_INCLUDE_FILE_WRITE_MANAGER_H_
#define PROJECT_INCLUDE_FILE_WRITE_MANAGER_H_

#include <stdio.h>

#include "client_t.h"

void write_client_data(FILE *file, client_t client);
void write_transaction_data(FILE *file, client_t transaction);




#endif  // PROJECT_INCLUDE_FILE_WRITE_MANAGER_H_
