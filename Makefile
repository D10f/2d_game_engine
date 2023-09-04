# -*- Makefile -*-

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wfatal-errors
TARGET   = game
SRCDIRS  = ./src
INCDIRS  = ./include ./lib/glm ./lib/lua ./lib/imgui ./lib/sol
LIBS     = lua5.4 SDL2 SDL2_image SDL2_mixer SDL2_ttf

SOURCES  = $(foreach D,$(SRCDIRS),$(wildcard $(D)/*.cpp))
INCLUDE  = $(foreach D,$(INCDIRS),-I$(D))
LDLIBS   = $(foreach L,$(LIBS), -l$(L))
OBJS     = $(addprefix build/,$(notdir $(SOURCES:.cpp=.o)))
DEPS     = $(OBJS:.o=.d)

all: $(TARGET)

build/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(INCLUDE) -c -MMD -o $@ $<

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^ $(LDLIBS)

-include $(DEPS)

.PHONY: all clean

clean:
	@rm -rvf $(TARGET) $(OBJS) $(DEPS)
