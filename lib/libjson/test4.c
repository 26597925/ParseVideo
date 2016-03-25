/*
 * gcc -o utf8 utf8.c -I/home/y/include -L./.libs -ljson
*/

#include <stdio.h>
#include <string.h>
#include "json.h"

void print_hex( const unsigned char* s) {
        const unsigned char *iter = s;
        unsigned char ch;
        while ((ch = *iter++) != 0) {
           if( ',' != ch)
            printf("%x ", ch);
           else
            printf( ",");
        }
        printf("\n");
}

int main() {
    const char *input = "\"\\ud840\\udd26,\\ud840\\udd27,\\ud800\\udd26,\\ud800\\udd27\"";
    const char *expected = "\xF0\xA0\x84\xA6,\xF0\xA0\x84\xA7,\xF0\x90\x84\xA6,\xF0\x90\x84\xA7";
    struct json_object *parse_result = json_tokener_parse((char*)input);
    const char *unjson = json_object_get_string(parse_result);

    printf("input: %s\n", input);

    int strings_match = !strcmp( expected, unjson);
    if (strings_match) {
        printf("JSON parse result is correct: %s\n", unjson);
        printf("PASS\n");
        return(0);
    } else {
        printf("JSON parse result doesn't match expected string\n");
        printf("expected string bytes: ");
        print_hex((const unsigned char *) expected);
        printf("parsed string bytes:   ");
        print_hex((const unsigned char *) unjson);
        printf("FAIL\n");
        return(1);
    }
}
