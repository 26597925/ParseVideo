/*
 *
 * Copyright (c) wenford.li
 * wenford.li <26597925@qq.com>
 *
 */
#include "regex.h"

static regex_t *regexec(char *pattern, char *subject)
{
	regex_t *regex;
	const char *error;
	int erroffset;
	int exec_offset = 0;
	regex = (regex_t *)malloc(sizeof(regex_t));;
	regex->re = pcre_compile(
	  pattern,              
	  PCRE_CASELESS | PCRE_DOTALL | PCRE_MULTILINE,             
	  &error,               
	  &erroffset,           
	  NULL);
    if (regex->re == NULL ) {
        printf("compilation failed at offset%d: %s\n", erroffset, error);
        return NULL;
    }
	regex->rc = pcre_exec( regex->re, NULL, subject, strlen(subject), exec_offset, 0, regex->ovector, oveccount );
	
	if (regex->rc == 0)
	{
	  regex->rc = oveccount/3;
	  printf("ovector only has room for %d captured substrings\n", regex->rc - 1);
	}
	
	if(regex->rc < 0){
		return NULL;
	}
	return regex;
}

char **preg_match(char *pattern, char *subject)
{
	regex_t *regex;
	int i;
	regex = regexec(pattern, subject);
	if(regex == NULL){
		return NULL;
	}
	const char *captured_string;
	char **str_arr = malloc(sizeof(char)*regex->rc);
	for (i = 0; i < regex->rc; i++)
	{
		pcre_get_substring(subject, regex->ovector, regex->rc, i, &captured_string);
		str_arr[i] = (char *)captured_string;
		//printf("captured_string string : %s\n", str_arr[i]);
	}
	free(regex->re);
	return str_arr;
}



