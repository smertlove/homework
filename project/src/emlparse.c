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
    if (prev_state == S_NEWLINE) {
        switch (cur_sym) {
            case '\n': return L_HEAD_END;
            case ' ' : return L_ANY_CHAR;
            case '\t': return L_ANY_CHAR;
            case '\r': return L_NEWLINE;
            default  : break;
        }
     }

    switch (cur_sym) {
        case '\n': return L_NEWLINE;
        case ':': return  L_COLON;
        case ' ': return  L_WHITESPACE;
        case '\t':return  L_WHITESPACE;
        case '\r':   return L_WHITESPACE;
        default: return L_ANY_CHAR;
    }
    return L_ERR;
}

static bool compare_headers(string_t *found_header, const char *searched_header) {
    return strcmp(found_header->data, searched_header) == 0;
}

static string_t* get_boundary(string_t *header_value) {
    string_t *boundary = init_string();
    char *ptr = strstr(header_value->data, "boundary=");
    if (ptr == NULL) {
        ptr = strstr(header_value->data, "BOUNDARY=");
    }
    if (ptr == NULL) {
        return boundary;
    }
    if (*(ptr - 1) == 'x') {  return boundary;  }
    ptr += 9;

    if (*ptr == '"') {
        ++ptr;
    }
    while (*ptr != '"' && *ptr != ' ' && *ptr != '\n' && *ptr != '\r' && *ptr != '\0') {
        add_char(boundary, *ptr);
        ++ptr;
    }
    return boundary;
}


static size_t calculate_parts(string_t *boundary, char *eml_body) {
    size_t counter = 0;
    char *flg = strstr(eml_body, boundary->data);
    char *ptr = eml_body;
    while (flg != NULL) {
        ++counter;
        ptr = flg;
        flg = strstr(flg + boundary->size, boundary->data);
    }
    while (*ptr != '\n' && *ptr != '\0') { ++ptr; }
    while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t' || *ptr == '\r' || *ptr == '.' || *ptr == '=') ++ptr;
    if (counter != 0 && *ptr == '\0') {
        return counter - 1;
    } else {
        return counter;
    }
}



static data_t parse_eml_headers(FILE *eml) {
    data_t data = {0};
    string_t *header = init_string();
    string_t *value = init_string();
    state_t state = S_HEAD_BEGIN;
    state_t prev_state = state;
    while (state != S_HEAD_END) {
        char cur_sym = fgetc(eml);
        lexeme_t lexeme = get_lexeme(cur_sym, prev_state);
        prev_state = state;
        state = transitions[state][lexeme];
        if ((state == S_HDR_BEGIN && prev_state == S_NEWLINE) || state == S_HEAD_END) {
            if (compare_headers(header, "From")) {
                data.from = value;
            } else if (compare_headers(header, "To")) {
                data.to = value;
            } else if (compare_headers(header, "Date")) {
                data.date = value;
            } else if (compare_headers(header, "Content-Type")) {
                data.boundary = get_boundary(value);
                free_string(value);
            } else {
                free_string(value);
            }
            free_string(header);

            header = init_string();
            value = init_string();
            add_char(header, cur_sym);
        } else if (state == S_HDR_BEGIN) {
            add_char(header, cur_sym);
        } else if (state == S_HDR_VAL) {
            add_char(value, cur_sym);
        } else if (state == S_ERR) {
            return data;
        }
    }
    free_string(header);
    
    free_string(value);
    return data;
}


bool emlparse(FILE *eml) {
    if (eml == NULL) {
        puts("if is true: no such eml");
        return false;
    }

    // getting length of eml
    fseek(eml, 0, SEEK_END);
    int eml_length = ftell(eml);
    fseek(eml, 0, SEEK_SET);

    // parsing head
    data_t data = parse_eml_headers(eml);

    // getting body as a string
    int body_length = eml_length - ftell(eml);
    char *eml_body = calloc(1, body_length + 1);
    fread(eml_body, 1, body_length, eml);
    eml_body[body_length] = '\0';

    // counting eml body parts
    data.part_count = (data.boundary == NULL) || (data.boundary->data == NULL) ?
    1 : calculate_parts(data.boundary, eml_body);

    // outputting data
    printf("%s|%s|%s|%zu",
        data.from == NULL ? "" : data.from->data,
        data.to == NULL ? "" : data.to->data,
        data.date == NULL ? "" : data.date->data,
        data.part_count);

    // freeing heap
    free(eml_body);
    free_string(data.date);
    free_string(data.from);
    free_string(data.to);
    
    free_string(data.boundary);
    
    return true;
}
