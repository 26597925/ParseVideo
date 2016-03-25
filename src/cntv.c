/*
 *
 * Copyright (c) wenford.li
 * wenford.li <26597925@qq.com>
 *
 */
#include "cntv.h"
#include "regex.h"
#include "http.h"
#include "json.h"
#include "util.h"

char* get_cntv_vid(char *url){
	char *pattern;
	char **strArr;
	int ret;
	pattern = "xiyou\\.cntv\\.cn/v-([0-9a-z-]+)\\.html";
	strArr = preg_match(pattern, url);
	if(strArr == NULL)
	{
		ret = request(url);
		if(ret < 1) return NULL;
		char *result = response();
		strArr = preg_match("contentid\"\\s+content=\"([0-9a-z]+)\">", result);
		if(strArr == NULL) preg_match("videoCenterId\",\"([0-9a-z]+)\"", result);
		if(strArr == NULL) preg_match("<!--repaste.video.code.begin-->([0-9a-z]+)<!--repaste.video.code.end-->", result); 
	}
	if(strArr != NULL) return strArr[1];
	return NULL;
}

static char* getResult(char *key){
	int i, ret;
	char *result = NULL;
	for(i=0; i<3; i++){
		char *url = "http://vdn.apps.cntv.cn/api/getHttpVideoInfo.do?pid=";
		url = join_str(url, key);
		ret = request(url);
		if(ret < 1) return NULL;
		set_refer("http://www.cntv.cn");
		result = response();
		if(result != NULL) break;
	}
	return result;
}

static json_object *get_video_flash(int fmt_type, char *key)
{
	if(fmt_type > 2) return json_tokener_parse("[]");
	int i, ret;
	char *result;
	char *fmt_arr[3] = {"lowChapters", "chapters", "chapters2"};
	result = getResult(key);
	json_object *json, *arr, *obj;
	json = json_tokener_parse(result);
	json = json_object_object_get(json, "video");
	char *fmt = fmt_arr[fmt_type];
	json = json_object_object_get(json, fmt);
	ret = json_object_array_length(json);
	arr = json_object_new_array();
	for(i=0; i < ret; i++) {
		obj = json_object_array_get_idx(json, i);
		char *video_url = get_json_string_val(obj, "url");
		obj = json_object_new_object();
		json_object_object_add(obj, "url", json_object_new_string(video_url));
		json_object_array_add(arr, obj);
	}
	return arr;
}

static json_object *get_video_html5(int fmt_type, char *key)
{
	char *result;
	result = getResult(key);
	if(result == NULL) return json_tokener_parse("[]"); 
	json_object *json, *arr;
	json = json_tokener_parse(result);
	char *video_url = get_json_string_val(json, "hls_url");
	arr = json_object_new_array();
	json = json_object_new_object();
	json_object_object_add(json, "url", json_object_new_string(video_url));
	json_object_array_add(arr, json);
	return arr;
}

char* get_cntv_url(char *key){
	char *url = "http://tv.cntv.cn/video/gwiyomi/";
	url = join_str(url, key);
	return url;
}

char *get_cntv_video(int fmt_type, char *key){
	json_object *arr = get_video_flash(fmt_type, key);
	if(json_object_array_length(arr) < 1){
		arr = get_video_html5(fmt_type, key);
	}
	return (char*)json_object_to_json_string(arr);
}