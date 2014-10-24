APP_STL := c++_static
NDK_TOOLCHAIN_VERSION=clang

APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -std=c++11 -fsigned-char -llog
APP_LDFLAGS := -latomic

APP_OPTIM := release

APP_ABI := armeabi armeabi-v7a x86