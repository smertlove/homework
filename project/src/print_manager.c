#include <stdio.h>

#include "client_t.h"

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

int get_case_choice(void) {
	puts("please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
	int case_choice;
	scanf("%d", &case_choice);
	return case_choice;
}

void print_client_data_fields(char *data_fields_to_print[], size_t array_size) {
	// size_t array_size = sizeof(*data_fields_to_print) / sizeof(*data_fields_to_print[0]);
	for (size_t i = 0; i < array_size; i++) {
		printf("%zu %s\n", i + 1, data_fields_to_print[i]);
	}
}