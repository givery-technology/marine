SRCS := src/GameCharacter.cpp
TESTS := test/GameCharacterTest.cpp test/TestMain.cpp
PROGNAME := app

GTEST_INC_PATH := /usr/local/include
GTEST_LIB_PATH:= /usr/local/lib

OUTDIR := build
PROG := $(OUTDIR)/$(PROGNAME)
CODES := $(SRCS) $(TESTS)
OBJS := $(CODES:%.cpp=$(OUTDIR)/%.o)

DEPS := $(CODES:%.cpp=$(OUTDIR)/%.d)

CXX := clang++
CPPFLAGS += -I$(GTEST_INC_PATH) -I./src -DGTEST_TAP_PRINT_TO_STDOUT -DGTEST_TAP_13_DIAGNOSTIC
CXXFLAGS += -std=c++11

LDFLAGS += -L$(GTEST_LIB_PATH)
LDLIBS += -lpthread -lgtest

all: $(PROG)

clean:
	rm -rf $(OUTDIR)

$(PROG): $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)

$(OUTDIR)/%.o: %.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) -MMD -MP $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

-include $(DEPS)
