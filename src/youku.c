/*
 *
 * Copyright (c) wenford.li
 * wenford.li <26597925@qq.com>
 *
 */
#include "youku.h"
#include "regex.h"
#include "http.h"
#include "json.h"
#include "util.h"
#define HZ "_youku"
#define SG "_"
char* get_youku_vid(char *url){
	char **strArr;
	strArr = preg_match("sid/(.*?)/v", url);
	if(strArr == NULL) strArr = preg_match("/id_(.*?)\\.html", url);
	if(strArr != NULL) return strArr[1];
	return NULL;
}

char *get_youku_video(int fmt_type, char *key){
	char str[4];
	int ret;
	char *url = "http://play.youku.com/play/get.json?vid=XMTUwMTA2NzQxNg==&ct=12&ran=";
	int rd = crand(0, 9999);
	itoa(rd, str, 10);
	url = join_str(url, str);
	ret = request(url);
	if(ret < 1) return NULL;
	set_refer("http://static.youku.com/");
	char *result = response();
	json_object *json, *security;
	char *encrypt_string, *stream;
	json = json_tokener_parse(result);
	json = json_object_object_get(json, "data");
	security = json_object_object_get(json, "security");
	encrypt_string = get_json_string_val(security, "encrypt_string");
	if(strcmp(encrypt_string, "") == 0){
		return NULL;
	}
	stream = get_json_string_val(json, "stream");
	printf("encrypt_string:%s,stream:%s", encrypt_string, stream);
	return "";
}