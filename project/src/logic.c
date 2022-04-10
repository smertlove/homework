#include <stdlib.h>
#include <stdio.h>

#include "logic.h"
#include "record_manager.h"
#include "client_t.h"

enum action {
    ENTER_CLIENT_DATA = 1,
    ENTER_TRANSACTION_DATA,
    UPDATE_DATA_BASE
};

#define TRANSACTION_FILENAME    "transaction.dat"
#define RECORD_FILENAME         "record.dat"
#define BLACKRECORD_FILENAME    "blackrecord.dat"
#define FILE_ACCESS_ERROR       "--- ERROR: NO SUCH FILE HERE ---\n"
#define FILE_CREATION_MSG       "--- FILE HAS BEEN CREATED ---\n"



void run_enter_data_case(const char *filename, void (*manager_to_execute)(FILE*, client_t)) {
    FILE *file = fopen(filename, "r+");
    client_t data = {0};
    if (file == NULL) {
        puts(FILE_CREATION_MSG);
        file = fopen(filename, "w");
    }
    manager_to_execute(file, data);
    fclose(file);
}


void run_update_data_base_case(void) {
    FILE *clients_db = fopen(RECORD_FILENAME, "r");
    if (clients_db == NULL) {
        puts(FILE_ACCESS_ERROR);
        return;
    }
    FILE *transaction_data = fopen(TRANSACTION_FILENAME, "r");
    if (transaction_data == NULL) {
        fclose(clients_db);
        puts(FILE_ACCESS_ERROR);
        return;
    }
    FILE *blackrecord = fopen(BLACKRECORD_FILENAME, "w");
    if (blackrecord == NULL) {
        fclose(clients_db);
        fclose(transaction_data);
        puts(FILE_ACCESS_ERROR);
        return;
    }
    client_t client_data = {0};
    client_t transfer = {0};
    manage_blackrecord_file(clients_db, transaction_data, blackrecord, client_data, transfer);
    fclose(clients_db);
    fclose(transaction_data);
    fclose(blackrecord);
}


void run_case_manager_logic(void) {
    int case_choice = get_case_choice();
    while (case_choice > 0 && case_choice < 4) {
        switch (case_choice) {
            case ENTER_CLIENT_DATA: {
                run_enter_data_case(RECORD_FILENAME, manage_record_file);
                break;
            }
            case ENTER_TRANSACTION_DATA: {
                run_enter_data_case(TRANSACTION_FILENAME, manage_transaction_file);
                break;
            }
            case UPDATE_DATA_BASE: {
                run_update_data_base_case();
                break;
            }
            default: {
                puts("error\n");
                break;
            }
        }
        case_choice = get_case_choice();
    }
}
