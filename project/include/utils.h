#ifndef ROJECT_INCLUDE_UTILS_H_
#define ROJECT_INCLUDE_UTILS_H_

#include <stdio.h>

#define filename "transaction.dat"

void masterWrite(FILE *ofPTR, Client_data Client);
void transactionWrite(FILE *ofPTR, Client_data transfer);
void blackRecord(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Client_data client_data, Client_data transfer);

#endif // ROJECT_INCLUDE_UTILS_H_
