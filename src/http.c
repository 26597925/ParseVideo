/*
 *
 * Copyright (c) wenford.li
 * wenford.li <26597925@qq.com>
 *
 */
#include "http.h"
struct curl_slist *headers = NULL;
CURL *curl;
CURLcode res;
int timeout = 30;//超时时间
int location = 1;//默认允许跳转
	
int request(char *url)
{
	curl = curl_easy_init();
	if (NULL == curl)  
    {
        curl_global_cleanup();   
        return 0;  
    }
	curl_easy_setopt(curl, CURLOPT_URL, url);
	return 1;
}

void add_header(char *header)
{
	curl_slist_append(headers, header);
}

void add_params(char *param)
{
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, param);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, sizeof(param));
}

void add_proxy(char *proxy_port, char *proxy_user_password)
{
	curl_easy_setopt(curl, CURLOPT_PROXY, proxy_port);
	curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, proxy_user_password);
}

void set_proxy_type(long type)
{
	curl_easy_setopt(curl, CURLOPT_PROXYTYPE, type);//CURLPROXY_SOCKS4,默认http
}

void add_cookie(char *cookie)
{
	curl_easy_setopt(curl, CURLOPT_COOKIE, cookie);
}

void set_refer(char *refer){
	curl_easy_setopt(curl, CURLOPT_REFERER, refer);
}

void set_user_agent(char *use_agent){
	curl_easy_setopt(curl, CURLOPT_USERAGENT, use_agent);
}

void set_time_out(int tout)
{
	timeout = tout;
}

void set_follow_location(int flocation)
{
	location = flocation;
}



static size_t write_data(void *data, size_t size, size_t nmemb, void *content)
{
	size_t realsize = size * nmemb;
    char *p = *(char **)content;
    size_t len = p ? strlen(p) : 0;
    *(char **)content = realloc(p, len + realsize + 1);
    p = *(char **)content;

    if (NULL == p)
    {
        fprintf(stderr,"not enouth memory");
        return -1;
    }

    memcpy(p + len, data, realsize);
    p[len + realsize] = '\0';

    return  realsize;
}

char* response(){
	char *result = NULL;
	if(headers != NULL) res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);//设置非0则，输出包含头信息
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&result);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, location);
	res = curl_easy_perform(curl);
	long retcode = 0;
	res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE , &retcode);
	if(location == 0 && (retcode == 301 || retcode == 302)) {
		res = curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL , &result);
	}
	if(CURLE_OK != res) result = NULL;
	curl_easy_cleanup(curl);		
	if(headers != NULL) curl_slist_free_all(headers);
	return result;
}