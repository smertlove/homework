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
    size_t mime_num;
} data_t;

typedef enum {
    L_ANY_CHAR,
    L_COLON,
    L_NEWLINE,
    L_WHITESPACE,
    L_HEAD_END,
    L_COUNT,
    L_ERR
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
        case ' ': return  L_WHITESPACE;
        case '\r': {
            if (prev_state == S_NEWLINE) {
                return L_HEAD_END;
            } else {
                return L_ANY_CHAR;
            }
        }
        default: return L_ANY_CHAR;
    }
    return L_ERR;
}


static bool compare_headers (string_t *found_header, const char *searched_header) {
    return strncmp(found_header->data, searched_header, sizeof(searched_header) - 1) == 0;
}

static string_t* get_boundary (string_t *header_value) {
    char *ptr = strstr(header_value->data, "boundary=") + 9;
        
    string_t *boundary = init_string();
    if (*ptr == '"') {
        ++ptr;
        while (*ptr != '"') {
            add_char(boundary, *ptr);
            ++ptr;
        }
        return boundary;
    }
    printf("%s", ptr);
    boundary->data = ptr;
    return boundary;
    }


static size_t calculate_parts(string_t *boundary, FILE *eml) {
    size_t counter = 0;
    char *buf = calloc(boundary->size+1, 1);
    while (fgets(buf, boundary->size, eml)!=NULL) {
        if (strcmp(boundary->data, buf) == 0) {
            ++counter;
        }
    }
    printf("%zu", counter);
    return counter;

}

static bool parse_eml_headers(FILE *eml) {

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

        if((state == S_HDR_BEGIN && prev_state == S_NEWLINE) || state == S_HEAD_END) {

            if (compare_headers(header, "From")) {
                data.from = value;
            } else if (compare_headers(header, "To")) {
                data.to = value;
            } else if (compare_headers(header, "Date")) {
                data.date = value;
            } else if (compare_headers(header, "Content-Type")) {
                string_t *b = get_boundary(value);
                
                calculate_parts(b, eml);
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
            return false;
        }
    }
    printf("%s\n%s\n%s\n", data.from->data, data.to->data, data.date->data);
    return state == S_HEAD_END;
}





bool emlparse(FILE *eml) {
    if (eml == NULL) {
        return false;
    }

    if (!parse_eml_headers(eml)) {
        return false;
    }
    return true;
}



