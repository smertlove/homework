#include <stdio.h>

#include "client_t.h"
#include "record_manager.h"
#include "print_manager.h"
#include "file_write_manager.h"
#include "scan_manager.h"

static char *data_fields[8] = {
    " Number account: ",
    " Client name: ",
    " Surname: ",
    " Addres client: ",
    " Client Telnum: ",
    " Client indebtedness: ",
    " Client credit limit: ",
    " Client cash payments: "
};

void transactionWrite(FILE *file, client_t transfer) {
    char *data_fields_to_print[2] = {data_fields[0], data_fields[7]};
    print_client_data_fields(data_fields_to_print, 2);
    while (scan_transaction_data(&transfer) != -1) {
        int c;
        if (((c = getchar()) != '\n') && c != EOF) {
            scanf("%*[^\n]");
            break;
        }
        write_transaction_data(file, transfer);
        print_client_data_fields(data_fields_to_print, 2);
    }
}


void masterWrite(FILE *file, client_t client) {
    print_client_data_fields(data_fields, 8);
    fseek(file, 0, SEEK_END);
    while (scan_client_data(&client) == 8 || scan_client_data(&client) != EOF) {
        write_client_data(file, client);
        // chistim buffer
        int c;
        if (((c = getchar()) != '\n') && c != EOF) {
            scanf("%*[^\n]");
            break;
        }
        print_client_data_fields(data_fields, 8);
    }
}

void blackRecord(FILE *client_db, FILE  *transfer_db, FILE *main_db, client_t client, client_t transfer) {
    while (read_client_data(client_db, &client) != -1) {
            while (read_transaction_data(transfer_db, &transfer) != -1) {
                if (client.account_number == transfer.account_number && transfer.cash_payments != 0) {
                    client.credit_limit += transfer.cash_payments;
                }
            }
        write_client_data(main_db, client);
        rewind(transfer_db);
        }
}

int get_case_choice(void) {
    puts("please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    int case_choice;
    scanf("%d", &case_choice);
    return case_choice;
}
