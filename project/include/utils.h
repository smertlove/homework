#ifndef ROJECT_INCLUDE_UTILS_H_
#define ROJECT_INCLUDE_UTILS_H_

#define filename "transaction.dat"

void masterWrite(FILE *ofPTR, Data Client),
void transactionWrite(FILE *ofPTR, Data transfer),
void blackRecord(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer);

#endif // ROJECT_INCLUDE_UTILS_H_
