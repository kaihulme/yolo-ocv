CCX = g++
# CXXFLAGS = -Wall -g -std=c++11

# SRC_DIRS ?= ./src
# SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
SRC = src/app.cpp
TARGET = app.out

LIBS = `pkg-config --cflags --libs opencv4`
INC = -I./include

MKDIRS = mkdir -p out

$(TARGET) : $(SRC) 
	$(CCX) $(SRC) -o $(TARGET) $(LIBS) $(INC)
	$(MKDIRS)

.PHONY: clean all
clean:
	\rm -f app.out
	\rm -f -r out
