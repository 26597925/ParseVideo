####################################
# Build libevent as separate library

include $(CLEAR_VARS)

LOCAL_MODULE:= libevent
LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES := \
    lib/libevent/event.c \
    lib/libevent/evutil.c \
    lib/libevent/epoll.c \
    lib/libevent/log.c \
    lib/libevent/poll.c \
    lib/libevent/select.c \
    lib/libevent/signal.c

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/lib/libevent \
    $(LOCAL_PATH)/lib/libevent/android

LOCAL_CFLAGS := -DHAVE_CONFIG_H -DANDROID -fvisibility=hidden

include $(BUILD_STATIC_LIBRARY)
