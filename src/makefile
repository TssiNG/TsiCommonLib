export BUILD_VER := RELEASE
export CXXFLAGS := -Wall -std=c++11
export RM := rm -f

.PHONY:release debug clean_release clean_debug

release:
	make -f tsiCom.makefile

debug:
	make BUILD_VER=DEBUG -f tsiCom.makefile

clean_release:
	make -f tsiCom.makefile clean

clean_debug:
	make BUILD_VER=DEBUG -f tsiCom.makefile clean