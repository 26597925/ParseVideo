#include "yinyuetai.h"
#include "regex.h"
#include "http.h"
#include "json.h"
#include "util.h"

char* get_yinyuetai_vid(char *url)
{
	char **strArr;
	strArr = preg_match("video/([0-9a-zA-Z]+/)*([0-9]+)", url);

	if(strArr != NULL) return strArr[2];
	return NULL;
}

char* get_yinyuetai_url(char *key)
{
	char *url = "http://v.yinyuetai.com/video/";
	url = join_str(url, key);
	return url;
}

char* get_yinyuetai_video(int fmt_type, char *key)
{
	if(fmt_type > 2) return "[]";
	int i, ret;
	char *result;
	//char *fmt_arr[3] = {"hc", "hd", "he"};
	for(i=0; i<3; i++){
		char *url = "http://www.yinyuetai.com/insite/get-video-info?flex=true&videoId=";
		url = join_str(url, key);	
		ret = request(url);
		if(ret < 1) return "[]";
		set_refer("http://www.yinyuetai.com");
		result = response();
		if(result != NULL) break; 
	}
	
	
	char **strArr;
	char *pattern1,*pattern2,*pattern3;

	pattern1 = "http://h.*?sc=[0-9A-Za-z]+&br=[0-9A-Za-z]+";
	pattern2 = "http://h.*?sc=[0-9A-Za-z]+";
	pattern3 = "http://h.*?.flv";
	
		strArr = preg_match(pattern1, result);
	if(strArr == NULL){
		strArr = preg_match(pattern2, result);
	}
	if(strArr == NULL){
		strArr = preg_match(pattern3, result);
	}
	if(strArr == NULL){
		strArr = preg_match(pattern3, result);
	}
	json_object *json,*arr;
	arr = json_object_new_array();
	if(strArr != NULL){
		json = json_object_new_object();
		json_object_object_add(json, "url", json_object_new_string(strArr[0]));
		json_object_array_add(arr, json);
	}
		
	return (char*)json_object_to_json_string(arr);
}