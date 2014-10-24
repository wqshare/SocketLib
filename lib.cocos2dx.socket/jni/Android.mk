LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := lnsocket_shared

LOCAL_LDFLAGS := -llog -lm

LOCAL_SRC_FILES := 	$(LOCAL_PATH)/../src/ln_socket.cpp \
					$(LOCAL_PATH)/../src/ln_msg_types.cpp 
					
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include

include $(BUILD_SHARED_LIBRARY)

