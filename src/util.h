/*
 *
 * Copyright (c) wenford.li
 * wenford.li <26597925@qq.com>
 *
 */

#include<stdio.h>  
#include<stdlib.h>
#include<string.h>
#include<time.h>

char* join_str(char *s1, char *s2);

char* join_str1(char *s1, char *s2);

char *str_dup(const char *str);

char **split_str(char* s,const char* delim);

void split(char **arr, char *str, const char *del);

/*将str1字符串中第一次出现的str2字符串替换成str3*/  
void replaceFirst(char *str1, char *str2, char *str3);

/*将str1出现的所有的str2都替换为str3*/  
void replace(char *str1, char *str2, char *str3);

/*截取src字符串中,从下标为start开始到end-1(end前面)的字符串保存在dest中(下标从0开始)*/  
void substring(char *dest, char *src, int start, int end);

/*返回src中下标为index的字符*/  
char charAt(char *src, int index);

/*返回str2第一次出现在str1中的位置(下表索引),不存在返回-1*/  
int indexOf(char *str1, char *str2);

/*返回str1中最后一次出现str2的位置(下标),不存在返回-1*/  
int lastIndexOf(char *str1, char *str2);

/*删除str左边第一个非空白字符前面的空白字符(空格符和横向制表符)*/  
void ltrim(char *str);

/*删除str最后一个非空白字符后面的所有空白字符(空格符和横向制表符)*/  
void rtrim(char *str);

/*删除str两端的空白字符*/  
void trim(char *str);

/*数字转化为字符串*/
char* itoa(int num, char* str, int radix);

/*生成随机数*/
int crand(int min, int max);