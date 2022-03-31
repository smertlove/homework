#ifndef PROJECT_INCLUDE_SCAN_MANAGER_H_
#define PROJECT_INCLUDE_SCAN_MANAGER_H_

#include <stdio.h>

#include "client_t.h"

int scan_client_data(client_t *client);
int scan_transaction_data(client_t *client);
int read_client_data(FILE *file, client_t *client);
int read_transaction_data(FILE *file, client_t *transfer);




#endif // PROJECT_INCLUDE_SCAN_MANAGER_H_
