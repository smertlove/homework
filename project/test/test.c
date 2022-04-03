#include <stdio.h>
#include <string.h>

#include "test.h"
#include "file_write_manager.h"


#define SAMPLE_RECORD_NAME       "sample_record.dat.gold"
#define SAMPLE_TRANSACTION_NAME  "sample_transaction.dat.gold"


void make_sample_file(void) {
    FILE *sample_file = fopen(SAMPLE_RECORD_NAME, "w");
    fprintf(sample_file,
            "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
            1,
            "Charles",
            "Darvin",
            "Shrewsbury",
            "telnum",
            777.0,
            666.0,
            322.0);
    fclose(sample_file);
}

void test_file_write(void) {
    const char *filepath = "sample_record.dat";
    FILE *sample_record = fopen(filepath, "r+");
    if (sample_record == NULL) {
        sample_record = fopen(filepath, "w");
    }
    client_t sample_client = {
        1,
        "Charles",
        "Darvin",
        "Shrewsbury",
        "telnum",
        777,
        666,
        555
    };
    write_client_data(sample_record, sample_client);
    fclose(sample_record);
}

int main(void) {
    make_sample_file();
    test_file_write();
    return 0;
}