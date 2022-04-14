#include <stdio.h>
#include <stdbool.h>

#include "emlparse.h"

// typedef enum {
//     L_HEAD_END,
//     L_HDR_BEGIN,
//     L_HDR_VAL,
//     L_COLON,
//     L_NEWLINE,
//     L_WHITESPACE,
//     L_COUNT,
//     L_ERR
// } lexeme_t;

typedef enum {
    L_HEAD_END,
    L_ANY_CHAR,
    L_COLON,
    L_NEWLINE,
    L_WHITESPACE,
    L_COUNT,
    L_ERR
} lexeme_t;

typedef enum {
    S_HEAD_BEGIN,
    S_HDR_BEGIN,
    S_HDR_VAL,
    S_COLON,
    S_NEWLINE,
    S_WHITESPACE,
    S_HEAD_END,
    S_COUNT,
    S_ERR
} state_t;


typedef bool (*action_t)(const char *s, const char **end);

// typedef struct {
//     state_t state;
//     action_t action;
// } rule_t;

typedef struct {
    state_t state;
    action_t action;
} rule_t;

static lexeme_t get_lexeme(const char *s, const char **end);
static lexeme_t get_hdr_value(const char *s, const char **end);

static void return_string(void) {
    return;
}





// static rule_t transitions[S_COUNT][L_COUNT] = {
// //                      L_HDR_BEGIN               L_HDR_VAL               L_COLON                 L_NEWLINE               L_WHITESPACE
// /* S_HEAD_BEGIN */   {{ S_HDR_BEGIN, NULL },    { S_ERR, NULL },        { S_ERR, NULL },        { S_NEWLINE, NULL },    { S_HEAD_BEGIN, NULL }},
// /* S_HDR_BEGIN */    {{ S_ERR, NULL },          { S_ERR, NULL },        { S_HDR_VAL, NULL },    { S_NEWLINE, NULL },    { S_HDR_BEGIN, NULL }},
// /* S_COLON */        {{ S_ERR, NULL },          { S_HDR_VAL, NULL },    { S_ERR, NULL },        { S_NEWLINE, NULL },    { S_COLON, NULL }},
// /* S_HDR_VAL */      {{ S_ERR, NULL },          { S_HDR_VAL, NULL },    { S_HDR_VAL, NULL },    { S_NEWLINE, NULL },    { S_HDR_VAL, NULL }},
// /* S_NEWLINE */      {{ S_HDR_BEGIN, NULL },    { S_ERR, NULL },        { S_ERR, NULL },        { S_HEAD_END, NULL },   { S_HDR_VAL, NULL }},
// /* S_WHITESPACE */   {{ S_HDR_BEGIN, NULL },    { S_HDR_VAL, NULL },    { S_COLON, NULL },      { S_NEWLINE, NULL },    { S_WHITESPACE, NULL }},
// /* S_HEAD_END */     {{ S_ERR, NULL },          { S_ERR, NULL },        { S_ERR, NULL },        { S_ERR, NULL },        { S_ERR, NULL }}
// };


static rule_t transitions[S_COUNT][L_COUNT] = {
//                    L_ANY_CHAR       L_COLON         L_NEWLINE      L_WHITESPACE      L_HEAD_END
/* S_HEAD_BEGIN */   {S_HDR_BEGIN,     S_ERR,          S_NEWLINE,     S_HEAD_BEGIN,     S_HEAD_END },
/* S_HDR_BEGIN */    {S_HDR_BEGIN,     S_HDR_VAL,      S_NEWLINE,     S_HDR_BEGIN,      S_ERR      },
/* S_COLON */        {S_HDR_VAL,       S_ERR,          S_NEWLINE,     S_COLON,          S_ERR      },
/* S_HDR_VAL */      {S_HDR_VAL,       S_HDR_VAL,      S_NEWLINE,     S_HDR_VAL,        S_HEAD_END },
/* S_NEWLINE */      {S_HDR_BEGIN,     S_ERR,          S_HEAD_END,    S_HDR_VAL,        S_HEAD_END },
/* S_WHITESPACE */   {S_HDR_VAL,       S_COLON,        S_NEWLINE,     S_WHITESPACE,     S_HEAD_END },
/* S_HEAD_END */     {S_ERR,           S_ERR,          S_ERR,         S_ERR,            S_HEAD_END }
};



static lexeme_t get_string(const char *s, const char **end) {
    ++s;
    while (*s != ':') {
        ++s;
    }
    if (*s == '\0') {
        return L_ERR;
    }
    *end = s + 1;
    return L_STR;
}

static lexeme_t get_lexeme(const char *eml_ptr, state_t prev_state) {
    switch (*eml_ptr) {
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


static bool parse_eml_headers(const char *eml_ptr) {
    state_t state = S_HEAD_BEGIN;
    state_t prev_state = state;
    while (state != S_HEAD_END) {
        lexeme_t lexeme = get_lexeme(eml_ptr, prev_state);             
        state = transitions[state][lexeme];
        ++eml_ptr;
        if (state == S_COLON) {
            char *name;
            char *value;

        }
    }
    return state == S_HEAD_END;
}


bool emlparse(const char *eml) {
    if (eml == NULL) {
        return false;
    }

    if (!parse_eml_headers(eml)) {
        return false;
    }
    return true;
}



