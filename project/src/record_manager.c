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

#define    STATUS_INVALID_INPUT = -1

void manage_transaction_file(FILE *file, client_t transfer) {
    char *data_fields_to_print[2] = {data_fields[0], data_fields[7]};
    print_client_data_fields(data_fields_to_print, 2);
    while (scan_transaction_data(&transfer) == 2) {
        int c;
        if (((c = getchar()) != '\n') && c != EOF) {
            scanf("%*[^\n]");
            break;
        }
        write_transaction_data(file, transfer);
        print_client_data_fields(data_fields_to_print, 2);
    }
}


void manage_record_file(FILE *file, client_t client) {
    print_client_data_fields(data_fields, 8);
    fseek(file, 0, SEEK_END);
    while (scan_client_data(&client) == 8 || scan_client_data(&client) != EOF) {
        int c;
        if (((c = getchar()) != '\n') && c != EOF) {
            scanf("%*[^\n]");
            break;
        }
        write_client_data(file, client);
        print_client_data_fields(data_fields, 8);
    }
}

void manage_blackrecord_file(
    FILE *client_db,
    FILE  *transfer_db,
    FILE *main_db,
    client_t client,
    client_t transfer) {
    while (read_client_data(client_db, &client) == 8) {
        while (read_transaction_data(transfer_db, &transfer) == 2) {
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
    int case_choice = 0;
    if(scanf("%d", &case_choice) != 1) {
        scanf("%*[^\n]");
        return STATUS_INVALID_INPUT;
    };
    return input_status[case_choice];
}
