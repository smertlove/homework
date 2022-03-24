#ifndef ROJECT_INCLUDE_UTILS_H_
#define ROJECT_INCLUDE_UTILS_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct client_t {
	int			account_number;
	char		name[20];
	char		surname[20];
	char		address[30];
	char		telephone_number[15];
	double		indebtedness;
	double		credit_limit;
	double		cash_payments;
} client_t;


void masterWrite(FILE *ofPTR, client_t Client);
void transactionWrite(FILE *ofPTR, client_t transfer);
void blackRecord(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, client_t client_data, client_t transfer);

#endif // ROJECT_INCLUDE_UTILS_H_
