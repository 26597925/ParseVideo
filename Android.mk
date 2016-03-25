LOCAL_PATH := $(call my-dir)
MY_LOCAL_PATH := $(LOCAL_PATH)

define all-c-files-under
$(patsubst ./%,%, \
	$(shell cd $(LOCAL_PATH) ; \
		find $(1) -name "*.c" -and -not -name ".*") \
  )
 endef

include $(CLEAR_VARS)
LOCAL_MODULE    := parsevideo
LOCAL_SRC_FILES :=  $(call all-c-files-under, src)

LOCAL_C_INCLUDES := $(MY_LOCAL_PATH)/lib/libevent $(MY_LOCAL_PATH)/lib/libcurl/include $(MY_LOCAL_PATH)/lib/libxml2/include $(MY_LOCAL_PATH)/lib/libpcre $(MY_LOCAL_PATH)/lib/libjson

LOCAL_STATIC_LIBRARIES := libevent libcurl libxml2 libpcre libjson

LOCAL_SHARED_LIBRARIES += libssl libcrypto libz
LOCAL_SHARED_LIBRARIES += liblog libcutils

LOCAL_LDLIBS := -ldl

#include $(BUILD_SHARED_LIBRARY) 
include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_MODULE    := libvideo
#armeabi armeabi-v7a mips
#APP_ABI         := x86
LOCAL_SRC_FILES :=  $(call all-c-files-under, src)

LOCAL_C_INCLUDES := $(MY_LOCAL_PATH)/lib/libevent $(MY_LOCAL_PATH)/lib/libcurl/include $(MY_LOCAL_PATH)/lib/libxml2/include $(MY_LOCAL_PATH)/lib/libpcre $(MY_LOCAL_PATH)/lib/libjson

LOCAL_STATIC_LIBRARIES := libevent libcurl libxml2 libpcre libjson

LOCAL_SHARED_LIBRARIES += libssl libcrypto libz
LOCAL_SHARED_LIBRARIES += liblog libcutils

LOCAL_LDLIBS := -ldl

include $(BUILD_SHARED_LIBRARY)

include $(MY_LOCAL_PATH)/lib/libevent/Android.mk
include $(MY_LOCAL_PATH)/lib/libcurl/Android.mk
include $(MY_LOCAL_PATH)/lib/libxml2/Android.mk
include $(MY_LOCAL_PATH)/lib/libpcre/Android.mk
include $(MY_LOCAL_PATH)/lib/libjson/Android.mk


