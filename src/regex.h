/*
 *
 * Copyright (c) wenford.li
 * wenford.li <26597925@qq.com>
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pcre.h"
#define oveccount 30

typedef struct {
  pcre *re;
  int ovector[oveccount];
  int rc;
} regex_t;

char **preg_match(char *pattern, char *subject);