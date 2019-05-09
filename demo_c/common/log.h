#ifndef _COMMON_LOG_H_
#define _COMMON_LOG_H_
	
#include <stdio.h>

	#define LOG_LEVEL_DEBUG		1
	#define LOG_LEVEL_INFO		2
	#define LOG_LEVEL_WARN		3
	#define LOG_LEVEL_ERROR		4
	#define LOG_LEVEL_FATAL		5

	#define LOG_LEVEL 	LOG_LEVEL_WARN

	/*
	* 宏定义多参数格式
	* #define log(level, args...) do { if ((level) >= LOG_LEVEL) printf(args); } while(0)
	* #define log(level, ...) do { if ((level) >= LOG_LEVEL) printf(__VA_ARGS__); } while(0)
	*/
	#define LOG(level, tag, ...)	do { \
										if ((level) >= LOG_LEVEL) { \
											printf("# %s, %s, %d, %s 	# 	", \
												tag, __FILE__, __LINE__, __FUNCTION__); \
											printf(__VA_ARGS__); \
											printf("\n"); \
										} \
									} while(0)

	#define LOG_DEBUG(...)		LOG(LOG_LEVEL_DEBUG, "DEBUG", __VA_ARGS__)
	#define LOG_INFO(...)		LOG(LOG_LEVEL_INFO, "INFO", __VA_ARGS__)
	#define LOG_WARN(...)		LOG(LOG_LEVEL_WARN, "WARN", __VA_ARGS__)
	#define LOG_ERROR(...)		LOG(LOG_LEVEL_ERROR, "ERROR", __VA_ARGS__)
	#define LOG_FATAL(...)		LOG(LOG_LEVEL_FATAL, "FATAL", __VA_ARGS__)

	/*
	* 模式：DEBUG（调试）、BATE（内测）、 其他 
	*/
	#ifdef DEBUG
		#undef LOG_LEVEL
		#define LOG_LEVEL 	LOG_LEVEL_DEBUG 
	#else
	#ifdef BATE
		#undef LOG_LEVEL
		#define LOG_LEVEL 	LOG_LEVEL_INFO 
	#else
		#undef LOG_DEBUG
		#define LOG_DEBUG(...)
		#undef LOG_INFO
		#define LOG_INFO(...)
	#endif
	#endif

#endif
