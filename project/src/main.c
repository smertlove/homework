#include <stdlib.h>

#include "record_manager.h"
#include "client_t.h"

enum action {
    ENTER_CLIENT_DATA = 1,
    ENTER_TRANSACTION_DATA,
    UPDATE_DATA_BASE
};

#define TRANSACTION_FILENAME	"transaction.dat"
#define RECORD_FILENAME			"record.dat"
#define BLACKRECORD_FILENAME	"blackrecord.dat"
#define FILE_ACCESS_ERROR		"--- ERROR: NO ACCESS ---"


int main(void){
    int case_choice = get_case_choice();
    while (case_choice > 0 && case_choice < 4) {
        printf("case choice: %d\n", case_choice);
        switch(case_choice) {
            case ENTER_CLIENT_DATA: {
                FILE *clients_db = fopen(RECORD_FILENAME, "r+");
                if (clients_db == NULL) {
                    puts(FILE_ACCESS_ERROR);
                    break;
                }
                client_t client_data = {.account_number = 0};
                masterWrite(clients_db, client_data);
                fclose(clients_db);
                break;
            }
            case ENTER_TRANSACTION_DATA: {
                FILE *transaction_data = fopen(TRANSACTION_FILENAME, "r+");
                if (transaction_data == NULL) {
                    puts(FILE_ACCESS_ERROR);
                    break;
                }
                client_t transfer = {.account_number = 0};
                transactionWrite(transaction_data, transfer);
                fclose(transaction_data);
                break;
            }
            case UPDATE_DATA_BASE: {
                FILE *clients_db = fopen(RECORD_FILENAME, "r");
                FILE *transaction_data = fopen(TRANSACTION_FILENAME, "r");
                FILE *blackrecord = fopen(BLACKRECORD_FILENAME, "w");
                if (clients_db == NULL || transaction_data == NULL || blackrecord == NULL) {
                    puts(FILE_ACCESS_ERROR);
                    break;
                }
                client_t client_data = {.account_number = 0};
                client_t transfer = {.account_number = 0};
                blackRecord(clients_db, transaction_data, blackrecord, client_data, transfer);
                fclose(clients_db);
                fclose(transaction_data);
                fclose(blackrecord);
                break;
            }
            default: {
                printf("case choice: %d\n", case_choice);
                puts("error");
                break;
            }
        }
    case_choice = get_case_choice();
    }
    return 0;
}




