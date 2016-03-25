/*
 *
 * Copyright (c) wenford.li
 * wenford.li <26597925@qq.com>
 *
 */
#include "qq.h"
#include "regex.h"
#include "http.h"
#include "json.h"
#include "util.h"

char* get_qq_vid(char *url)
{
	char *pattern;
	char **strArr;
	int ret;
	pattern = "http\\://v\\.qq\\.com/iframe/player\\.html\\?vid=(\\w+)";
	strArr = preg_match(pattern, url);
	if(strArr == NULL)
	{
		pattern = "http\\://static\\.video\\.qq\\.com/TPout\\.swf\\?[0-9a-z&=_-]*vid=(\\w+)";
		strArr = preg_match(pattern, url);
	}
	if(strArr == NULL)
	{
		ret = request(url);
		if(ret < 1) return NULL;
		set_refer("http://v.qq.com");
		char *result = response();
		strArr = preg_match("vid\\:\"([0-9a-z]+)\",", result);
	}
	if(strArr == NULL)
	{
		ret = request(url);
		if(ret < 1) return NULL;
		char *result = response();
		strArr = preg_match("vid=(\\w+)", result);
	}
	if(strArr != NULL) return strArr[1];
	return NULL;
}

char *get_qq_url(char *key)
{
	char *url = "http://v.qq.com/iframe/player.html?vid=";
	char *param = "&tiny=0&auto=0";
	url = join_str(url, key);
	url = join_str(url, param);
	return url;
}

static json_object *get_video_flash(int fmt_type, char *key)
{
	if(fmt_type > 4) return json_tokener_parse("[]");
	int ret = -1, i, fc;
	char *fmt_arr[4] = {"sd", "shd", "hd", "fhd"};
	char *url = "http://vv.video.qq.com/getinfo?defaultfmt=";
	url = join_str(url, fmt_arr[fmt_type]);
	url = join_str(url, "&otype=json&platform=11&vids=");
	url = join_str(url, key);
	ret = request(url);
	if(ret < 1) return json_tokener_parse("[]");
	char **strArr;
	set_refer("http://v.qq.com");
	char *result = response();
	strArr = preg_match("QZOutputJson\\s*=\\s*(.*);", result);

	json_object *json, *vi, *ui, *cl, *ci, *temp, *arr;
	char *vt, *vurl, *fn, *keyid;
	
	json = json_tokener_parse(strArr[1]);
	json = json_object_object_get(json, "vl");
	vi = json_object_object_get(json, "vi");
	
	ui = json_object_array_get_idx(vi, 0);
	ui = json_object_object_get(ui, "ul");
	ui = json_object_object_get(ui, "ui");
	temp = json_object_array_get_idx(ui, 1);
	vt = get_json_string_val(temp, "vt");
	temp = json_object_array_get_idx(ui, 0);
	vurl = get_json_string_val(temp, "url");
	temp = json_object_array_get_idx(vi, 0);
	fn = get_json_string_val(temp, "fn");
	
	char **fn_arr = split_str(fn, ".");
	cl = json_object_object_get(temp, "cl");
	arr = json_object_new_array();
	if(json_object_object_exist(cl, "ci") > 0){
		ci = json_object_object_get(cl, "ci");
		ci = json_object_array_get_idx(ci, 0);
		keyid = get_json_string_val(ci, "keyid");
		char **keyid_arr = split_str(keyid, ".");
		fc = json_object_get_int(json_object_object_get(cl, "fc"));
		char *key_base_url = "http://vv.video.qq.com/getkey?platform=11&otype=json&vid=";
		key_base_url = join_str(key_base_url, key);
		key_base_url = join_str(key_base_url, "&vt=");
		key_base_url = join_str(key_base_url, vt);
		char *vname_pre = fn_arr[0];
		vname_pre = join_str(vname_pre, ".");
		vname_pre = join_str(vname_pre, fn_arr[1]);
		vname_pre = join_str(vname_pre, ".");
		char *vanme_next = ".";
		vanme_next = join_str(vanme_next, fn_arr[2]);
		char *vname, *key_url;
		for(i = 0; i < fc; i++){
			char str[10];
			itoa((i+1),str,10);
			vname = join_str(vname_pre, str);
			vname = join_str(vname, vanme_next);
			key_url = join_str(key_base_url, "&format=");
			key_url = join_str(key_url, keyid_arr[1]);
			key_url = join_str(key_url, "&filename=");
			key_url = join_str(key_url, vname);
			ret = request(key_url);
			if(ret < 1) return json_tokener_parse("[]");
			set_refer("http://v.qq.com");
			result = response();
			strArr = preg_match("QZOutputJson\\s*=\\s*(.*);", result);
			json = json_tokener_parse(strArr[1]);
			if(json_object_object_exist(json, "key") == 0) return json_tokener_parse("[]");
			char *k_key = get_json_string_val(json, "key");
			char *video_url = join_str(vurl, vname);
			video_url = join_str(video_url, "?platform=0&fmt=");
			video_url = join_str(video_url, fmt_arr[fmt_type]);
			video_url = join_str(video_url, "&level=0&vkey=");
			video_url = join_str(video_url, k_key);
			
			json = json_object_new_object();
			json_object_object_add(json, "url", json_object_new_string(video_url));
			json_object_array_add(arr, json);
		}
	}
	
	return arr;
}

static json_object *get_video_html5(int fmt_type, char *key)
{
	int ret = -1;
	char **strArr;
	char *url = "http://vv.video.qq.com/geturl?vid=";
	url = join_str(url, key);
	url = join_str(url, "&otype=json");
	ret = request(url);
	if(ret < 1) return json_tokener_parse("[]");
	set_refer("http://v.qq.com");
	set_user_agent("Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.99 Safari/537.36");
	char *result = response();
	strArr = preg_match("QZOutputJson\\s*=\\s*(.*);", result);
	
	json_object *json, *arr;
	json = json_tokener_parse(strArr[1]);
	json = json_object_object_get(json, "vd");
	json = json_object_object_get(json, "vi");
	json = json_object_array_get_idx(json, 0);
	
	if(json_object_object_exist(json, "url") == 0) return json_tokener_parse("[]");
	url = get_json_string_val(json, "url");
	arr = json_object_new_array();
	json = json_object_new_object();
	json_object_object_add(json, "url", json_object_new_string(url));
	json_object_array_add(arr, json);
	
	return arr;
}

char* get_qq_video(int fmt_type, char *key){
	json_object *arr = get_video_flash(fmt_type, key);
	if(json_object_array_length(arr) < 1){
		arr = get_video_html5(fmt_type, key);
	}
	return (char*)json_object_to_json_string(arr);
}