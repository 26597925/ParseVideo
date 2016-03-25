#include "56.h"
#include "regex.h"
#include "http.h"
#include "json.h"
#include "util.h"

char* get_56_vid(char *url){
	char *pattern;
	char **strArr;
	pattern = "/open_([0-9A-Za-z]+).swf";
	strArr = preg_match(pattern, url);
	if(strArr == NULL)
	{
		pattern = "/v_([0-9A-Za-z]+).html";
		strArr = preg_match(pattern, url);
	}
	if(strArr == NULL)
	{
		pattern = "/vid-([0-9A-Za-z]+).html";
		strArr = preg_match(pattern, url);
	}
	if(strArr != NULL) return strArr[1];
	return NULL;
}

char* get_56_url(char *key){
	char *url = "http://www.56.com/u99/v_";
	char *param = ".html";
	url = join_str(url, key);
	url = join_str(url, param);
	return url;
}

char *get_56_video(int fmt_type, char *key){
	if(fmt_type > 2) return "[]";
	int i, ret;
	char *result;
	char *fmt_arr[3] = {"normal", "clear", "super"};
	for(i=0; i<3; i++){
		char *url = "http://vxml.56.com/json/";
		url = join_str(url, key);
		url = join_str(url, "/?src=out");
		ret = request(url);
		if(ret < 1) return "[]";
		set_refer("http://vxml.56.com");
		result = response();
		if(result != NULL) break; 
	}
	json_object *json, *rfiles, *arr;
	json = json_tokener_parse(result);
	json = json_object_object_get(json, "info");
	rfiles = json_object_object_get(json, "rfiles");
	ret = json_object_array_length(rfiles);
	arr = json_object_new_array();
	for(i=0; i < ret; i++) {
		json_object *obj = json_object_array_get_idx(rfiles, i);
		char *video_url = get_json_string_val(obj, "url");
		char *video_type = get_json_string_val(obj, "type");
		if(strcmp(video_type, fmt_arr[fmt_type]) == 0){
			json = json_object_new_object();
			json_object_object_add(json, "url", json_object_new_string(video_url));
			json_object_array_add(arr, json);
		}
	}
	if(json_object_array_length(arr) == 0){
		json_object *obj = json_object_array_get_idx(rfiles, ret - 1);
		char *video_url = get_json_string_val(obj, "url");
		json = json_object_new_object();
		json_object_object_add(json, "url", json_object_new_string(video_url));
		json_object_array_add(arr, json);
	}
	return (char*)json_object_to_json_string(arr);
}