#ifndef PROJECT_INCLUDE_RECORD_MANAGER_H_
#define PROJECT_INCLUDE_RECORD_MANAGER_H_

#include <stdio.h>

#include "client_t.h"

void manage_transaction_file(FILE *file, client_t transfer);
void manage_record_file(FILE *file, client_t client);
void manage_blackrecord_file(FILE *client_db,
                             FILE  *transfer_db,
                             FILE *main_db,
                             client_t client,
                             client_t transfer);
int get_case_choice(void);
void clean_buffer(void);


#endif  // PROJECT_INCLUDE_RECORD_MANAGER_H_
