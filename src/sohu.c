#include "sohu.h"
#include "regex.h"
#include "http.h"
#include "json.h"
#include "util.h"

char* get_sohu_vid(char *url)
{
	int i, ret;
	char *result = NULL;
	char **strArr;
	for(i=0; i<3; i++){
		ret = request(url);
		if(ret < 1) return NULL;
		result = response();
		if(result != NULL) break;
	}
	strArr = preg_match("var[\\s]+vid=\"([0-9]+)\"", result);
	if(strArr == NULL) preg_match("var[\\s]+vid[\\s]+=[\\s]+\'([0-9]+)\'", result);
	if(strArr == NULL) preg_match(",vid:[\\s]+\'([0-9]+)\'", result); 
	if(strArr != NULL) return strArr[1];
	return NULL;
}

static json_object *get_video_flash(int fmt_type, char *key)
{
	int i, ret;
	char *result;
	for(i=0; i<3; i++){
		char *url = "http://hot.vrs.sohu.com/vrs_flash.action?vid=";
		url = join_str(url, key);
		ret = request(url);
		if(ret < 1) return json_tokener_parse("[]");
		set_refer("http://tv.sohu.com");
		result = response();
		if(result != NULL) break; 
	}
	json_object *json, *su, *video, *arr;
	json = json_tokener_parse(result);
	json = json_object_object_get(json, "data");
	su   = json_object_object_get(json, "su");
	ret =  json_object_array_length(su);
	arr = json_object_new_array();
	if(ret > 0){
		char *host = "http://sohu.vodnew.lxdns.com";
		for(i = 0; i < ret; i++)
		{
			video = json_object_array_get_idx(su, i);
			char *video_url = (char*)json_object_get_string(video);
			video_url = join_str(host, video_url);
			json = json_object_new_object();
			json_object_object_add(json, "url", json_object_new_string(video_url));
			json_object_array_add(arr, json);
		}
	}
	return arr;
}

static json_object *get_video_html5(int fmt_type, char *key)
{
	json_object *arr, *json;
	arr = json_object_new_array();
	char *url = "http://hot.vrs.sohu.com/ipad";
	char *param = ".m3u8";
	url = join_str(url, key);
	url = join_str(url, param);
	json = json_object_new_object();
	json_object_object_add(json, "url", json_object_new_string(url));
	json_object_array_add(arr, json);
	return arr;
	
}

char *get_sohu_video(int fmt_type, char *key)
{
	json_object *arr = get_video_flash(fmt_type, key);
	if(json_object_array_length(arr) < 1){
		arr = get_video_html5(fmt_type, key);
	}
	return (char*)json_object_to_json_string(arr);
}