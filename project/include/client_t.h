#ifndef ROJECT_INCLUDE_CLIENT_T_H_
#define ROJECT_INCLUDE_CLIENT_T_H_


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


#endif // ROJECT_INCLUDE_CLIENT_T_H_
