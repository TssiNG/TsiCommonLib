# 加载路径
vpath %.h ../Common
vpath %.cpp commonLib
vpath %.cpp tsiLog

.PHONY: all clean clean_cache

#变量声明
CXXFLAGS += -fPIC
CXXINCLUDES = -I ../Common
SRCS_COMMON_WITHPATH = $(wildcard ./commonLib/*.cpp)
SRCS_COMMON = $(SRCS_COMMON_WITHPATH:./commonLib/%.cpp=%.cpp)
OBJS_COMMON_WITHPATH = $(SRCS_COMMON:%.cpp=./compile/%.o)
OBJS_COMMON = $(SRCS_COMMON:.cpp=.o)
DEPS_COMMON = $(SRCS_COMMON:.cpp=.d)
DEPS_COMMON_WITHPATH = $(SRCS_COMMON:%.cpp=./.d/%.d)
TARGET_COMMON = libtsicom.so
OUTDIR = ../../../lib/

ifeq ($(BUILD_VER), DEBUG)
CXXFLAGS += -g3
TARGET_COMMON :=libtsicomD.so
endif

ifeq ($(BUILD_VER), RELEASE)
CXXFLAGS += -O2
endif

-include $(DEPS_COMMON)

# 为每一个cpp单独生成一个.d依赖文件
# .d = .o --> .cpp + .h
# 当.h文件被修改时, .o文件会被重新编译
%.d:$(SRCS_COMMON)
	@set -e;\
	$(RM) $@;\
	$(CXX) $(CXXINCLUDES) -MM $< > .d/$@;

# 生成每一个.o文件
# $@代表目标 : $<代表首个依赖
%.o:%.cpp
	$(CXX) $(CXXINCLUDES) $(CXXFLAGS) -c $< -o ./compile/$@

# 生成解决方案
all:$(TARGET_COMMON)

$(TARGET_COMMON):$(OBJS_COMMON)
	$(CXX) -shared -o $(OUTDIR)$(TARGET_COMMON) $(OBJS_COMMON_WITHPATH)

clean:
	$(RM) $(OUTDIR)$(TARGET_COMMON) $(OBJS_COMMON_WITHPATH) $(DEPS_COMMON_WITHPATH)