CXX = g++
CXXFLAGS = -Wall -g -std=c++11

INC = -I./include

LIBS = $(shell pkg-config --cflags --libs opencv4)

TARGET = app.out

SRC_DIRS ?= ./src
SRCS := $(shell find $(SRC_DIRS) -name *.cpp)

MKDIRS = mkdir -p out

main: mkdirs
	$(CXX) $(CXXFLAGS) $(INC) $(LIBS) $(SRCS) -o $(TARGET)

mkdirs:
	$(MKDIRS)

.PHONY: clean all
clean:
	\rm -f app.out
	\rm -f -r out
