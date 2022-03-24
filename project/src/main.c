#include <stdlib.h>
#include "utils.h"

enum action {
	ENTER_CLIENT_DATA = 1,
	ENTER_TRANSACTION_DATA,
	UPDATE_DATA_BASE
};

#define TRANSACTION_FILENAME 	"transaction.dat"
#define RECORD_FILENAME			"record.dat"
#define BLACKRECORD_FILENAME	"blackrecord.dat"
#define FILE_ACCESS_ERROR		"--- ERROR: NO ACCESS ---"




int get_case_choice(void) {
	puts("please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
	int case_choice;
	scanf("%d", &case_choice);
	return case_choice;
}

void print_client_data_fields(void) {
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
			"1 Number account: ",
			"2 Client name: ",
			"3 Surname: ",
			"4 Addres client: ",
			"5 Client Telnum: ",
			"6 Client indebtedness: ",
			"7 Client credit limit: ",
			"8 Client cash payments: ");
}

void masterWrite(FILE *ofPTR, client_t Client) {
	print_client_data_fields();
	while (scanf(	"%d%s%s%s%s%lf%lf%lf",
					&Client.account_number,
					Client.name,
					Client.surname,
					Client.address,
					Client.telephone_number,
					&Client.indebtedness,
					&Client.credit_limit,
					&Client.cash_payments
				) != -1) {
		fprintf(ofPTR,
				"%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
				Client.account_number,
				Client.name,
				Client.surname,
				Client.address,
				Client.telephone_number,
				Client.indebtedness,
				Client.credit_limit,
				Client.cash_payments);
		print_client_data_fields();
		while(getchar() != '\n');
	}
}

void transactionWrite(FILE *ofPtr, client_t transfer) {
	printf("%s\n%s\n",
		   "1 Number account: ",
		   "2 Client cash payments: ");
	while(scanf("%d %lf", &transfer.account_number, &transfer.cash_payments) != -1) {
		fprintf(ofPtr, "%-3d%-6.2f\n", transfer.account_number, transfer.cash_payments);
		printf("%s\n%s\n",
				"1 Number account:",
				"2 Client cash payments: ");
	}
}

void blackRecord(FILE *ofPTR, FILE  *ofPTR_2, FILE *blackrecord, client_t client_data, client_t transfer) {
	while(fscanf(ofPTR,
		"%d%s%s%s%s%lf%lf%lf",
		&client_data.account_number,
		client_data.name,
		client_data.surname,
		client_data.address,
		client_data.telephone_number,
		&client_data.indebtedness,
		&client_data.credit_limit,
		&client_data.cash_payments) != -1) {
			while ((fscanf(ofPTR_2, "%d %lf", &transfer.account_number, &transfer.cash_payments) != -1)) {
				if(client_data.account_number == transfer.account_number && transfer.cash_payments != 0) {
					client_data.credit_limit += transfer.cash_payments;
				}
			}
		fprintf(blackrecord,
				"%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
				client_data.account_number,
				client_data.name,
				client_data.surname,
				client_data.address,
				client_data.telephone_number,
				client_data.indebtedness,
				client_data.credit_limit ,
				client_data.cash_payments);
		rewind(ofPTR_2);
		}
}





int main(void){
	// int count = 0;
	// int a;
	// 	int b;
	// 	char c;
	// 	int scn;
	// 		while(1){
	// 	printf("%s\n", "enter some digits");
		
	// 	scn = scanf("%d%d%s", &a, &b, &c);

	// 	while(getchar() != '\n');

	// 	printf("int a = %d\nint b = %d\nchar c = %s\n", a, b, &c);
	// 	printf("scan_return = %d\n--- COUNT %d ---\n",  scn, count);
	// 	count++;
	// }
	
	int case_choice = get_case_choice();
	while (case_choice != -1) {
		switch(case_choice) {
			case ENTER_CLIENT_DATA: {
				FILE *clients_db = fopen(RECORD_FILENAME, "r+");
				if (clients_db == NULL) {
					puts(FILE_ACCESS_ERROR);
					break;
				}
				client_t client_data;
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
				client_t transfer;
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
				client_t client_data;
				client_t transfer;
				blackRecord(clients_db, transaction_data, blackrecord, client_data, transfer);
				free(clients_db);
				fclose(clients_db);
				fclose(transaction_data);
				fclose(blackrecord);
				break;
			}
			default: {
				puts("error");
				break;
			}
		}
	case_choice = get_case_choice();
	}
	return 0;
}




