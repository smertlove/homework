#include "utils.h"

enum action {
	ENTER_CLIENT_DATA = 1,
	ENTER_TRANSACTION_DATA,
	UPDATE_DATA_BASE
};

#define TRANSACTION_FILENAME 	"transaction.dat"
#define RECORD_FILENAME			"record.dat"
#define BLACKRECORD_FILENAME	"blackrecord.dat"

struct client_t {
	int			account_number;
	char		name[20];
	char		surname[20];
	char		address[30];
	char		telephone_number[15];
	double		indebtedness;
	double		credit_limit;
	double		cash_payments;
};
typedef struct client_t client_t;

int main(void){
	int case_choice = get_case_choice();
	FILE *Ptr;
	FILE *Ptr_2;
	FILE *blackrecord;
	client_t client_data;
	client_t transfer;

	while (case_choice != -1) {
		switch(case_choice) {
			case ENTER_CLIENT_DATA: {
				Ptr = fopen(RECORD_FILENAME, "r+");
				if (Ptr == NULL) {
					puts("Not acess");
				} else {
					masterWrite(Ptr, client_data);
					fclose(Ptr);
				}
				break;
			}
			case ENTER_TRANSACTION_DATA: {
				Ptr = fopen(TRANSACTION_FILENAME, "r+");
					if (Ptr == NULL) {
					puts("Not acess");
					}
				else{
					transactionWrite(Ptr, transfer);
					fclose(Ptr);
				}
				break;
			}
			case UPDATE_DATA_BASE: {
				Ptr = fopen(RECORD_FILENAME, "r");
				Ptr_2 = fopen(TRANSACTION_FILENAME, "r");
				blackrecord = fopen(BLACKRECORD_FILENAME, "w");
				if (Ptr == NULL || Ptr_2 == NULL || blackRecord == NULL) {
					puts("exit");
				} else {
					blackRecord(Ptr, Ptr_2, blackrecord, client_data, transfer);
					free(Ptr);
					fclose(Ptr);
					fclose(Ptr_2);
					fclose(blackrecord);
				}
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

void masterWrite(FILE *ofPTR, client_t Client) {
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
			"1 Number account: ",
			"2 Client name: ",
			"3 Surname: ",
			"4 Addres client: ",
			"5 Client Telnum: ",
			"6 Client indebtedness: ",
			"7 Client credit limit: ",
			"8 Client cash payments: ");
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
		printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
				"1 Number account: ",
				"2 Client name: ",
				"3 Surname: ",
				"4 Addres client: ",
				"5 Client Telnum: ",
				"6 Client indebtedness: ",
				"7 Client credit limit: ",
				"8 Client cash payments:");
	}
}

void transactionWrite(FILE *ofPtr, client_t transfer) {
	printf("%s\n%s\n",
		   "1 Number account: ",
		   "2 Client cash payments: ");
	while(scanf("%d %lf", &transfer.account_number, &transfer.cash_payments) != -1) {
		fprintf(TRANSACTION_FILENAME, "%-3d%-6.2f\n", transfer.account_number, transfer.cash_payments);
		printf("%s\n%s\n",
				"1 Number account:",
				"2 Client cash payments: ");
	}
}

void blackRecord(FILE *ofPTR, FILE  *ofPTR_2, FILE *blackrecord, client_t client_data, client_t transfer) {
    int count = 0;
    int ccount = 0;
	while((fscanf(ofPTR,
		"%d%s%s%s%s%lf%lf%lf",
		&client_data.account_number,
		client_data.name,
		client_data.surname,
		client_data.address,
		client_data.telephone_number,
		&client_data.indebtedness,
		&client_data.credit_limit,
		&client_data.cash_payments) != -1) && count < 100) {
			while ((fscanf(ofPTR_2, "%d %lf", &transfer.account_number, &transfer.cash_payments) != -1) && ccount < 100) {
				if(client_data.account_number == transfer.account_number && transfer.cash_payments != 0) {
					client_data.credit_limit += transfer.cash_payments;
                    count++;
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
        count++;
		}
}

int get_case_choice(void) {
	printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
	int case_choice;
	scanf("%d", &case_choice);
	return case_choice;
}
