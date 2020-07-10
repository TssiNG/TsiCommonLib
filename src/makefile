# 加载路径
vpath %.h ../Common
vpath %.cpp commonLib
vpath %.cpp ezLog

#变量声明
CXX           = g++
AR            = ar
RM            = rm -f
ARFLAGS       = -rcs
CXXFLAGS      = -g -c -w
CXXINCLUDES   = -I ../Common
MM            = -MM
SOURCE_COMMON = mathLib.cpp strLib.cpp timeLib.cpp windowsUtil.cpp unixUtil.cpp
SOURCE_EZLOG  = ezLog.cpp strLib.cpp timeLib.cpp
SOURCE_TEST   = testTsi.cpp
OBJS_COMMON   = mathLib.o strLib.o timeLib.o unixUtil.o
OBJS_EZLOG    = ezLog.o strLib.o timeLib.o
OBJS_TEST     = mathLib.o strLib.o
TARGET_COMMON = TsiCommonLib.a
TARGET_EZLOG  = ezLog.so
TARGET_TEST   = testTsi
OUTDIR        = ../../../lib/
DEPS          = $(SOURCE_COMMON:.cpp=.d)

-include $(DEPS)

# 为每一个cpp单独生成一个.d依赖文件
# .d = .o --> .cpp + .h
# 当.h文件被修改时, .o文件会被重新编译
%.d:$(SOURCE_COMMON)
	@set -e;\
	$(RM) $@;\
	$(CXX) $(CXXINCLUDES) $(MM) $< > .d/$@;

# 生成每一个.o文件
# $@代表目标 : $<代表首个依赖
%.o:$(SOURCE_COMMON)
	$(CXX) $(CXXINCLUDES) $(CXXFLAGS) $< -o $(OUTDIR)$@

# 强制伪目标
.PHONY:all clean

# 生成解决方案
all: $(OBJS_TEST) $(TARGET_COMMON)

$(TARGET_COMMON):$(OBJS_TEST)
	cd $(OUTDIR);\
	$(AR) $(ARFLAGS) $@ $^

clean:
	$(RM) $(OUTDIR)*.a
	$(RM) $(OUTDIR)*.so
	$(RM) $(OUTDIR)*.o