#ifndef PROJECT_INCLUDE_LOGIC_H_
#define PROJECT_INCLUDE_LOGIC_H_

#include <stdlib.h>
#include <stdio.h>

#include "client_t.h"


void run_logic(void);
void run_enter_data_case(const char *filename, void (*manager_to_execute)(FILE*, client_t));

#endif  // PROJECT_INCLUDE_LOGIC_H_
