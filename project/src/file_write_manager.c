#include <stdio.h>

#include "client_t.h"

#define CLIENT_DATA_WRITE_PATTERN	"%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n"
#define TRANSACTION_WRITE_PATTERN	"%-3d%-6.2f\n"

void write_client_data(FILE *file, client_t client) {
	fprintf(file,
			CLIENT_DATA_WRITE_PATTERN,
			client.account_number,
			client.name,
			client.surname,
			client.address,
			client.telephone_number,
			client.indebtedness,
			client.credit_limit,
			client.cash_payments
	);
}

void write_transaction_data(FILE *file, client_t transaction) {
	fprintf(file,
			TRANSACTION_WRITE_PATTERN,
			transaction.account_number,
			transaction.cash_payments
	);
}
