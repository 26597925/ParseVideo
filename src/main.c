/*
 *
 * Copyright (c) wenford.li
 * wenford.li <26597925@qq.com>
 *
 */

#include "qq.h"
#include "56.h"
#include "cntv.h"
#include "sohu.h"
#include "yinyuetai.h"
#include "youku.h"

int main(int argc, char **argv)
{
	int ret = 0;
	/*ret = request("http://vedio.yunos-tv.com/?r=api/index/loadBackgroud");
	if(ret < 1) return ret; 
	set_follow_location(0);
	char *result = response();
	printf("%s", result);*/
	//http://v.qq.com/iframe/player.html?vid=d0186m2epm2&width=670&height=502.5&auto=0
	//get_vid("http://v.qq.com/iframe/player.html?vid=d0186m2epm2");
	//get_vid("http://static.video.qq.com/TPout.swf?ads=ii233&vid=d0186m2epm2");
	//char *key = get_vid("http://v.qq.com/cover/8/8rv6wur9xiezs02.html?vid=v01879ucipn");
	//char *key = get_vid("http://v.qq.com/cover/4/43mjrvgrl4a9832.html?vid=q0019lphyh4");
	//char *key = get_vid("http://film.qq.com/cover/5/53el1qwq1gnm5fn.html");
	//printf("%s \n", argv[1]);
	//char *key = get_qq_vid("http://v.qq.com/cover/4/43mjrvgrl4a9832.html?vid=q0019lphyh4");
	//char *url = get_video_url(key);
	//char* data = get_qq_video(2, key);
	//printf("%s \n", data);
	/*char *key = get_56_vid("http://www.56.com/u85/v_MTM2MTYyOTE0.html");
	printf("%s \n", key);
	char* data = get_56_video(0, key);
	printf("%s \n", data);
	char *key = get_cntv_vid("http://tv.cntv.cn/video/VSET100157955652/4578e895c6d54968a8f1b76db2204f54");
	char* data = get_cntv_video(0, key);
	printf("%s \n", data);
	char *key = get_sohu_vid("http://tv.sohu.com/20160315/n440438165.shtml");
	char* data = get_sohu_video(0, key);
	printf("%s \n", data);*/
	char *key = get_youku_vid("http://v.youku.com/v_show/id_XMTUwMTA2NzQxNg==.html?f=26886163");
	char* data = get_youku_video(0, key);
	printf("%s \n", data);
	return ret;
}