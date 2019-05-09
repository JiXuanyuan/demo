#ifndef _COMMON_ALLOC_H_
#define _COMMON_ALLOC_H_

#include <stdlib.h>

#include "log.h"

	#define common_malloc(...)		malloc(__VA_ARGS__)
	#define common_realloc(...)		realloc(__VA_ARGS__)
	#define common_free(...)		free(__VA_ARGS__)

	#ifdef DEBUG
		static int common_alloc_count = 0;
		
		#undef common_malloc
		#define common_malloc(...)		malloc(__VA_ARGS__); \
				LOG_DEBUG("alloc, malloc: %d", ++common_alloc_count)
		
		#undef common_realloc
		#define common_realloc(...)		realloc(__VA_ARGS__); \
				LOG_DEBUG("alloc, realloc: %d", common_alloc_count)
		
		#undef common_free
		#define common_free(...)		free(__VA_ARGS__); \
				LOG_DEBUG("alloc, free: %d", --common_alloc_count)
	#endif

#endif