/*
 *
 * Copyright (c) wenford.li
 * wenford.li <26597925@qq.com>
 *
 */
#include "util.h"

char* join_str(char *s1, char *s2)
{  
    char *result = malloc(strlen(s1)+strlen(s2)+1); 
    if (result == NULL) return NULL;
	
    strcpy(result, s1);  
    strcat(result, s2);
	
    return result;  
}  

char* join_str1(char *s1, char *s2)
{  
    char *str3 = (char *) malloc(strlen(s1) + strlen(s2) + 1); //�ֲ���������malloc�����ڴ�  
    if (str3 == NULL) return NULL;  
    char *tempc = str3; //���׵�ַ������  
    while (*s1 != '\0') {  
        *str3++ = *s1++;  
    }  
    while ((*str3++ = *s2++) != '\0') {  
        ;  
    }  
    //ע�⣬��ʱָ��c�Ѿ�ָ��ƴ��֮����ַ����Ľ�β'\0' !  
    return tempc;//����ֵ�Ǿֲ�malloc�����ָ����������ں������ý�����free֮  
}

char *str_dup(const char *str)
{
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if(dup)
    {
        strcpy(dup, str);
    }
    return dup;
}

char **split_str(char* s,const char* delim){
	char *ts = str_dup(s);
	char *p = strtok(s, delim);
	int rows=0;
	while(p!=NULL){
		rows+=1;
		p=strtok(NULL, delim);
	}
	char **str_arr = malloc(sizeof(char)*(rows+1));
	rows = 0;
	p = strtok(ts, delim);
	while(p!=NULL){
		str_arr[rows] = p;
		rows+=1;
		p=strtok(NULL, delim);
	}
	return str_arr;
}

void split(char **arr, char *str, const char *del) {  
    char *s = strtok(str, del);  
    while (s != NULL) {  
        *arr++ = s;  
        s = strtok(NULL, del);  
    }  
}

void replaceFirst(char *str1, char *str2, char *str3) {  
    char str4[strlen(str1) + 1];  
    char *p;  
    strcpy(str4, str1);  
    if ((p = strstr(str1, str2)) != NULL)/*pָ��str2��str1�е�һ�γ��ֵ�λ��*/ {  
        while (str1 != p && str1 != NULL)/*��str1ָ���ƶ���p��λ��*/ {  
            str1++;  
        }  
        str1[0] = '\0'; /*��str1ָ��ָ���ֵ���/0,�Դ����ض�str1,����str2���Ժ�����ݣ�ֻ����str2��ǰ������*/  
        strcat(str1, str3); /*��str1��ƴ����str3,�����str1*/  
        strcat(str1, strstr(str4, str2) + strlen(str2)); /*strstr(str4,str2)��ָ��str2���Ժ������(����str2),strstr(str4,str2)+strlen(str2)���ǽ�ָ����ǰ�ƶ�strlen(str2)λ������str2*/  
    }  
}

void replace(char *str1, char *str2, char *str3) {  
    while (strstr(str1, str2) != NULL) {  
        replaceFirst(str1, str2, str3);  
    }  
}

void substring(char *dest, char *src, int start, int end) {
    int i = start;  
    if (start > strlen(src))return;  
    if (end > strlen(src))  
        end = strlen(src);  
    while (i < end) {  
        dest[i - start] = src[i];  
        i++;  
    }  
    dest[i - start] = '\0';  
    return;  
}

char charAt(char *src, int index) {  
    char *p = src;  
    int i = 0;  
    if (index < 0 || index > strlen(src))  
        return 0;  
    while (i < index)i++;  
    return p[i];  
}

int indexOf(char *str1, char *str2) {  
    char *p = str1;  
    int i = 0;  
    p = strstr(str1, str2);  
    if (p == NULL)  
        return -1;  
    else {  
        while (str1 != p) {  
            str1++;  
            i++;  
        }  
    }  
    return i;  
}

int lastIndexOf(char *str1, char *str2) {
    char *p = str1;  
    int i = 0, len = strlen(str2);  
    p = strstr(str1, str2);  
    if (p == NULL)return -1;  
    while (p != NULL) {  
        for (; str1 != p; str1++)i++;  
        p = p + len;  
        p = strstr(p, str2);  
    }  
    return i;  
}

void ltrim(char *str) {  
    int i = 0, j, len = strlen(str);  
    while (str[i] != '\0') {  
        if (str[i] != 32 && str[i] != 9)break; /*32:�ո�,9:�����Ʊ��*/  
        i++;  
    }  
    if (i != 0)  
        for (j = 0; j <= len - i; j++) {  
            str[j] = str[j + i]; /*��������ַ�˳��ǰ��,����ɾ���Ŀհ�λ��*/  
        }  
}

void rtrim(char *str) {  
    char *p = str;  
    int i = strlen(str) - 1;  
    while (i >= 0) {  
        if (p[i] != 32 && p[i] != 9)break;  
        i--;  
    }  
    str[++i] = '\0';  
}

void trim(char *str) {  
    ltrim(str);  
    rtrim(str);  
}

char* itoa(int num, char* str, int radix)
{/*������*/
	char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned unum;/*�м����*/
	int i=0,j,k;
	/*ȷ��unum��ֵ*/
	if(radix==10&&num<0)/*ʮ���Ƹ���*/
	{
		unum=(unsigned)-num;
		str[i++] = '-';
	}
	else unum = (unsigned)num;/*�������*/
	/*ת��*/
	do{
		str[i++]=index[unum%(unsigned)radix];
		unum/=radix;
	}while(unum);
	str[i]='\0';
	/*����*/
	if(str[0]=='-')k=1;/*ʮ���Ƹ���*/
	else k=0;
	char temp;
	for(j=k;j<=(i-1)/2;j++)
	{
		temp=str[j];
		str[j]=str[i-1+k-j];
		str[i-1+k-j]=temp;
	}
	return str;
}

int crand(int min, int max){
	srand(time(NULL));
	return min + (int) (max*1.0*rand()/(RAND_MAX + min*1.0));
}