#include <stdio.h>

#include "scan_manager.h"
#include "client_t.h"

#define CLIENT_DATA_SCAN_PATTERN	"%1d%10s%10s%10s%10s%1lf%1lf%1lf"
#define TRANSACTION_SCAN_PATTERN	"%d %lf"

int scan_client_data(client_t *client) {
	int argc = scanf(	CLIENT_DATA_SCAN_PATTERN,
						&client->account_number,
						client->name,
						client->surname,
						client->address,
						client->telephone_number,
						&client->indebtedness,
						&client->credit_limit,
						&client->cash_payments
	);
	return argc;
}

int scan_transaction_data(client_t *client) {
	int argc = scanf(	TRANSACTION_SCAN_PATTERN,
						&client->account_number,
						&client->cash_payments
	);
	return argc;
}

int read_client_data(FILE *file, client_t *client) {
    int argc = fscanf(	file,
						CLIENT_DATA_SCAN_PATTERN,
						&client->account_number,
						client->name,
						client->surname,
						client->address,
						client->telephone_number,
						&client->indebtedness,
						&client->credit_limit,
						&client->cash_payments
	);
    return argc;
}

int read_transaction_data(FILE *file, client_t *transfer) {
    int argc = fscanf(	file,
						TRANSACTION_SCAN_PATTERN,
						&transfer->account_number,
						&transfer->cash_payments
	);
    return argc;
}
