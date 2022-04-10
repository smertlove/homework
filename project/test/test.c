#include <stdio.h>
#include <string.h>

#include "test.h"
#include "file_write_manager.h"


#define SAMPLE_RECORD_NAME       "sample_record.dat.gold"
#define FILE_TO_COMPARE_NAME     "sample_record.dat"
#define ERROR_NO_ACCESS          "no such file, unfortunately..."

void make_sample_file(void) {
    FILE *sample_file = fopen(SAMPLE_RECORD_NAME, "w");
    fprintf(
        sample_file,
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
    FILE *sample_record = fopen(FILE_TO_COMPARE_NAME, "r+");
    if (sample_record == NULL) {
        sample_record = fopen(FILE_TO_COMPARE_NAME, "w");
    }
    puts("file successfully made...\n");
    client_t sample_client = {
        1,
        "Charles",
        "Darvin",
        "Shrewsbury",
        "telnum",
        777,
        666,
        322
    };
    write_client_data(sample_record, sample_client);
    puts("test data written...\n");
    fclose(sample_record);
    puts("file successfully closed...\n");
}

void compare_files(void) {
    FILE *sample_file = fopen(SAMPLE_RECORD_NAME, "r");
    if (sample_file == NULL) {
        puts(ERROR_NO_ACCESS);
        return;
    }
    puts("sample file opened successfully\n");
    FILE *file_to_compare = fopen(FILE_TO_COMPARE_NAME, "r");
    if (file_to_compare == NULL) {
        fclose(sample_file);
        puts(ERROR_NO_ACCESS);
        return;
    }
    puts("file to compare opened successfully\n");
    char sample_file_data[201];
    fgets(sample_file_data, 200, sample_file);
    printf("1st file data: %s", sample_file_data);
    char file_to_compare_data[201];
    fgets(file_to_compare_data, 200, file_to_compare);
    printf("2nd file data: %s", file_to_compare_data);
    if (strcmp(sample_file_data, file_to_compare_data) != 0) {
        puts("files mismatch...\n");
    } else {
        puts("files match!\n");
    }
    fclose(sample_file);
    fclose(file_to_compare);
}

int main(void) {
    make_sample_file();
    test_file_write();
    compare_files();
    return 0;
}