/*
 *
 * Copyright (c) wenford.li
 * wenford.li <26597925@qq.com>
 *
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

int request(char *url);

void add_header(char *header);

void add_params(char *param);

void add_proxy(char *proxy_port, char *proxy_user_password);

void set_proxy_type(long type);

void add_cookie(char *cookie);

void set_refer(char *refer);

void set_user_agent(char *use_agent);

void set_time_out(int tout);

void set_follow_location(int flocation);

char *response();

