#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#include "emlparse.h"
#include "custom_string.h"

typedef struct {
    string_t *from;
    string_t *to;
    string_t *date;
    string_t *boundary;
    size_t part_count;
} data_t;

typedef enum {
    L_ANY_CHAR,
    L_COLON,
    L_NEWLINE,
    L_WHITESPACE,
    L_HEAD_END,
    L_COUNT,
    L_ERR,
    L_SKIP_CHAR
} lexeme_t;

typedef enum {
    S_HEAD_BEGIN,
    S_HDR_BEGIN,
    S_COLON,
    S_HDR_VAL,  
    S_NEWLINE,
    S_WHITESPACE,
    S_HEAD_END,
    S_COUNT,
    S_ERR
} state_t;

static state_t transitions[S_COUNT][L_COUNT] = {
//                    L_ANY_CHAR       L_COLON         L_NEWLINE      L_WHITESPACE      L_HEAD_END
/* S_HEAD_BEGIN */   {S_HDR_BEGIN,     S_ERR,          S_NEWLINE,     S_HEAD_BEGIN,     S_HEAD_END },
/* S_HDR_BEGIN */    {S_HDR_BEGIN,     S_COLON,        S_NEWLINE,     S_HDR_BEGIN,      S_ERR      },
/* S_COLON */        {S_HDR_VAL,       S_ERR,          S_NEWLINE,     S_COLON,          S_ERR      },
/* S_HDR_VAL */      {S_HDR_VAL,       S_HDR_VAL,      S_NEWLINE,     S_HDR_VAL,        S_HEAD_END },
/* S_NEWLINE */      {S_HDR_BEGIN,     S_ERR,          S_HEAD_END,    S_HDR_VAL,        S_HEAD_END },
/* S_WHITESPACE */   {S_HDR_VAL,       S_COLON,        S_NEWLINE,     S_WHITESPACE,     S_HEAD_END },
/* S_HEAD_END */     {S_ERR,           S_ERR,          S_ERR,         S_ERR,            S_HEAD_END }
};

static lexeme_t get_lexeme(char cur_sym, state_t prev_state) {
    switch (cur_sym) {
        case '\n': {
            if (prev_state == S_NEWLINE) {
                return L_HEAD_END;
            } else {
                return L_NEWLINE;
            }
        }
        case ':': return  L_COLON;
        case ' ': {
            if (prev_state == S_NEWLINE) {
                return L_ANY_CHAR;
            }
            return  L_WHITESPACE;
        }
        case '\t': {
            if (prev_state == S_NEWLINE) {
                return L_ANY_CHAR;
            }
            return  L_WHITESPACE;
        }
        case '\r': {
            if (prev_state == S_NEWLINE) {
                return L_NEWLINE;
            } else {
                return L_WHITESPACE;
            }
        }
        default: return L_ANY_CHAR;
    }
    return L_ERR;
}
// sizeof(searched_header) - 1

static bool compare_headers (string_t *found_header, const char *searched_header) {
    return strncmp(found_header->data, searched_header, strlen(searched_header) ) == 0;
}

static string_t* get_boundary (string_t *header_value) {
    // puts("entered 'get boundary' func");
    string_t *boundary = init_string();
    char *ptr = strstr(header_value->data, "boundary=");
    if (ptr == NULL) {
        // puts("no boundary found");
        return boundary;
    }
    ptr += 9;
    
    if (*ptr == '"') {
        ++ptr;
    }
    // printf("got boundary coordinates: ptr = %c\n", *ptr);
    // int c= 0;
    while (*ptr != '"' && *ptr != ' ' && *ptr != '\n' && *ptr != '\r' && *ptr != '\0') {
        add_char(boundary, *ptr);
        ++ptr;
        // c++;
        // if (c == 40) {
        //     puts("40 loops break");
        //     break;
        // }
        // printf("looking at next char: ptr = \"%c\", %d\n", *ptr, *ptr);
    }
    return boundary;
    }


static size_t calculate_parts(string_t *boundary, char *eml_body) {
    size_t counter = 0;
    char *flg = strstr(eml_body, boundary->data);
    while (flg != NULL) {
        ++counter;
        flg = strstr(flg + boundary->size, boundary->data);
    }
    
    
    return counter - 1;

}



static data_t parse_eml_headers(FILE *eml) {

    data_t data = {0};

    string_t *header = init_string();
    string_t *value = init_string();

    state_t state = S_HEAD_BEGIN;
    state_t prev_state = state;
    // puts ("initialized variables");
    while (state != S_HEAD_END) {
        
        char cur_sym = fgetc(eml);
        lexeme_t lexeme = get_lexeme(cur_sym, prev_state);
        prev_state = state;
        state = transitions[state][lexeme];
        // printf("%c; %d; %d\n", cur_sym, lexeme, state);
        if((state == S_HDR_BEGIN && prev_state == S_NEWLINE) || state == S_HEAD_END) {

            if (compare_headers(header, "From")) {
                data.from = value;
                // printf("%zu\n\n", value->size);
                // for (size_t i = 0; i < strlen(data.from->data); ++i) {
                //     printf("%d\t", data.from->data[i]);
                //     printf("%c\t", data.from->data[i]);
                //     printf("%ld\n",i);
                // }
                // printf("\n");
                // for (size_t i = 0; i < strlen(data.from->data); ++i) {
                //     printf("%c ", data.from->data[i]);
                //     printf("%ld/\t",i);
                // }
                // printf("\n");
                // printf("from -- %s\n", data.from->data);
                // puts("got from");
            } else if (compare_headers(header, "To")) {
                data.to = value;
                // puts("got to");
                //printf("to -- %s\n", data.to->data);

            } else if (compare_headers(header, "Date")) {
                data.date = value;
                // puts("got date");
                //printf("date -- %s\n", data.date->data);
            } else if (compare_headers(header, "Content-Type")) {
                // printf("%s\n%s\n", header->data, value->data);
                // puts("start boundary extraction");
                data.boundary = get_boundary(value);
                // puts("got boundary");
                // printf("boundary -- %s\n", data.boundary->data);
            } else {
                free_string(value);
            }


            free_string(header);
            
            header = init_string();
            value = init_string();
            add_char(header, cur_sym);
        } else if (state == S_HDR_BEGIN){
            add_char(header, cur_sym);
        } else if (state == S_HDR_VAL) {
            add_char(value, cur_sym);
        } else if (state == S_ERR) {
            return data;
        }
    }
    
    return data;
}

// static void print_string_codes(string_t *str) {
//     static int counter = 0;
//     char *ptr = str->data;
//     for (size_t i = 0; i < str->size; i++) {
//         printf("%d -- %c\n", *ptr, *ptr);
//         ++ptr;
//         ++counter;
//     }
//     printf("counter = %d", counter);
// }

bool emlparse(FILE *eml) {
    if (eml == NULL) {
        return false;
    }
    // puts("entered parse function");
    // getting length of eml
    fseek(eml, 0, SEEK_END);
    int eml_length = ftell(eml);
    fseek(eml, 0, SEEK_SET);
    // puts("got length of eml");
    // parsing head
    data_t data = parse_eml_headers(eml);
    // puts("done parsing headers");
    // getting body as a string
    int body_length = eml_length - ftell(eml);
    char *eml_body = calloc(1, body_length);
    fread(eml_body,1, body_length, eml);
    
    // puts("put body into string");
    // counting eml body parts
    data.part_count = data.boundary->data == NULL ? 1 : calculate_parts(data.boundary, eml_body);
    // puts("counted parts of body");


    // print_string_codes(data.from);
    // print_string_codes(data.to);
    // print_string_codes(data.date);

    // puts("\n\n\n");
    printf("%s|%s|%s|%zu",
        data.from == NULL ? "" : data.from->data, 
        data.to == NULL ? "" : data.to->data, 
        data.date == NULL ? "" : data.date->data, 
        data.part_count);

    
    free_string(data.date);
    free_string(data.from);
    free_string(data.to);

    free_string(data.boundary);

    return true;
}



