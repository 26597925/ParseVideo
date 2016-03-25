LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE:= libjson
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES := \
    arraylist.c \
	debug.c \
	json_object.c \
	json_tokener.c \
	json_util.c \
	linkhash.c \
	printbuf.c

LOCAL_C_INCLUDES := \
    arraylist.h \
	bits.h \
	debug.h \
	json.h \
	json_config.h \
	json_inttypes.h \
	json_object.h \
	json_object_private.h \
	json_tokener.h \
	json_util.h \
	linkhash.h \
	printbuf.h

include $(BUILD_STATIC_LIBRARY)
