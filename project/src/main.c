#include "utils.h"



enum Action {
	ENTER_CLIENT_DATA = 1,
	ENTER_TRANSACTION_DATA,
	UPDATE_DATA_BASE
};

#define DATA_REQUEST_MESSAGE "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n"
#define TRANSACTION_FILENAME "transaction.dat"

struct Client_data {
	int			Number;
	char		Name[20];
	char		Surname[20];
	char		addres[30];
	char		TelNumber[15];
	double		indebtedness;
	double		credit_limit;
	double		cash_payments;
};
typedef struct Client_data Client_data;

int main(void){
	int choice = 0;
	FILE *Ptr, *Ptr_2 , *blackrecord;
	Client_data client_data, transfer;
	printf("%s", DATA_REQUEST_MESSAGE);

	while (scanf("%d", &choice) != -1) {
		switch(choice) {
			case ENTER_CLIENT_DATA: {
				Ptr = fopen("record.dat", "r+");
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
				Ptr = fopen("record.dat", "r");
				Ptr_2 = fopen("transaction.dat", "r");
				blackrecord = fopen("blackrecord.dat", "w");
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
	printf("%s", DATA_REQUEST_MESSAGE);
	}
	return 0;
}

void masterWrite(FILE *ofPTR, Client_data Client) {
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
					&Client.Number,
					Client.Name,
					Client.Surname,
					Client.addres,
					Client.TelNumber,
					&Client.indebtedness,
					&Client.credit_limit,
					&Client.cash_payments
				) != -1) {
		fprintf(ofPTR,
				"%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
				Client.Number,
				Client.Name,
				Client.Surname,
				Client.addres,
				Client.TelNumber,
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

void transactionWrite(FILE *ofPtr, Client_data transfer) {
	printf("%s\n%s\n",
		   "1 Number account: ",
		   "2 Client cash payments: ");
	while(scanf("%d %lf", &transfer.Number, &transfer.cash_payments) != -1) {
		fprintf(TRANSACTION_FILENAME, "%-3d%-6.2f\n", transfer.Number, transfer.cash_payments);
		printf("%s\n%s\n",
				"1 Number account:",
				"2 Client cash payments: ");
	}
}

void blackRecord(FILE *ofPTR, FILE  *ofPTR_2, FILE *blackrecord, Client_data client_data, Client_data transfer) {
    int count = 0;
    int ccount = 0;
	while((fscanf(ofPTR,
		"%d%s%s%s%s%lf%lf%lf",
		&client_data.Number,
		client_data.Name,
		client_data.Surname,
		client_data.addres,
		client_data.TelNumber,
		&client_data.indebtedness,
		&client_data.credit_limit,
		&client_data.cash_payments) != -1) && count < 100) {
			while ((fscanf(ofPTR_2, "%d %lf", &transfer.Number, &transfer.cash_payments) != -1) && ccount < 100) {
				if(client_data.Number == transfer.Number && transfer.cash_payments != 0) {
					client_data.credit_limit += transfer.cash_payments;
                    count++;
				}
			}
		fprintf(blackrecord,
				"%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
				client_data.Number,
				client_data.Name,
				client_data.Surname,
				client_data.addres,
				client_data.TelNumber,
				client_data.indebtedness,
				client_data.credit_limit ,
				client_data.cash_payments);
		rewind(ofPTR_2);
        count++;
		}
}
