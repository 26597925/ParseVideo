LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES :=  \
  pcre_chartables.c	\
	pcre_ucd.c	\
	pcre_compile.c \
	pcre_config.c \
	pcre_exec.c \
	pcre_fullinfo.c \
	pcre_get.c \
	pcre_globals.c \
	pcre_maketables.c \
	pcre_newline.c \
	pcre_ord2utf8.c \
	pcre_refcount.c \
	pcre_study.c \
	pcre_tables.c \
	pcre_valid_utf8.c \
	pcre_version.c \
	pcre_xclass.c \
	pcre_jit_compile.c

LOCAL_COPY_HEADERS := pcre.h
LOCAL_COPY_HEADERS_TO := libpcre

LOCAL_CFLAGS += -O3 -I. -DHAVE_CONFIG_H

LOCAL_MODULE := libpcre
LOCAL_MODULE_CLASS := STATIC_LIBRARIES

include $(BUILD_STATIC_LIBRARY)