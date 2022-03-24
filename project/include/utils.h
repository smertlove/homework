#ifndef ROJECT_INCLUDE_UTILS_H_
#define ROJECT_INCLUDE_UTILS_H_

#include <stdio.h>

void masterWrite(FILE *ofPTR, client_t Client);
void transactionWrite(FILE *ofPTR, client_t transfer);
void blackRecord(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, client_t client_data, client_t transfer);

#endif // ROJECT_INCLUDE_UTILS_H_
