LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := PX2Graphics

FILE_LIST := $(wildcard $(LOCAL_PATH)/*cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/Renderers/OpenGLES2Renderer/*cpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_EXPORT_LDLIBS := -llog -lGLESv2

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_LDLIBS := -lGLESv2 -lEGL -llog 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
$(LOCAL_PATH)/Renderers/OpenGLES2Renderer/ \
$(PX2_ROOT)/PX2SDK/Include/ \
$(PX2_ROOT)/ThirdPartiesLibs/OGLES/

include $(BUILD_STATIC_LIBRARY)
