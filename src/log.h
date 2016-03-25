#define LOGFILEDIR "/mnt/sdcard/"
#define LOGFILEPATH "tvshop_"
//根据日志级别写日志
#define LOG_ERR		0	//0=记录错误日志
#define LOG_NORMAL	1	//1=记录日常日志和错误日志
#define LOG_DEBUG	2	//2=记录错误日志日常日志调试日志
#define LOG_LEVEL	LOG_DEBUG   



void my_log(int loglev,const char * format, ... );
void my_loghex(int loglev,unsigned char *logmsg,int len);
