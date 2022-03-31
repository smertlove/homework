#ifndef PROJECT_INCLUDE_CLIENT_T_H_
#define PROJECT_INCLUDE_CLIENT_T_H_


typedef struct client_s {
    int		account_number;
    char	name[20];
    char	surname[20];
    char	address[30];
    char	telephone_number[15];
    double	indebtedness;
    double	credit_limit;
    double	cash_payments;
} client_t;


#endif // PROJECT_INCLUDE_CLIENT_T_H_
