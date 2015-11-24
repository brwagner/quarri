HEADERS = $(wildcard src/*.hpp)
OBJECTS = $(addprefix out/, $(notdir $(subst .hpp,.o,$(HEADERS))))

TEST_HEADERS = $(wildcard test/*TestSuite.hpp)
TESTS = $(addprefix out/, $(notdir $(subst .hpp,.cpp,$(TEST_HEADERS))))

BUILD_DIR := $(CURDIR)/build
LIB_DIR := $(CURDIR)/lib
SRC_DIR := src
RES_DIR := res
LEVEL_DIR := $(RES_DIR)/level

CXXTEST_HOME = $(LIB_DIR)/cxxtest-4.4
CXXTEST_GEN = $(CXXTEST_HOME)/bin/cxxtestgen
CXXTEST_INCLUDE = $(CXXTEST_HOME)

SDL_SOURCE_PATH := $(LIB_DIR)/SDL2-2.0.3
SDL_BUILD_PATH := $(BUILD_DIR)/SDL2_Build
SDL_LIB := -L$(SDL_BUILD_PATH)/lib
SDL_INCLUDE := -I$(SDL_BUILD_PATH)/include/SDL2
SDL_FLAGS := -lSDL2

SDL_GFX_SOURCE_PATH := $(LIB_DIR)/SDL2_gfx-1.0.1
SDL_GFX_BUILD_PATH := $(BUILD_DIR)/SDL2_GFX_Build
SDL_GFX_LIB := -L$(SDL_GFX_BUILD_PATH)/lib
SDL_GFX_INCLUDE := -I$(SDL_GFX_BUILD_PATH)/include/SDL2
SDL_GFX_FLAGS := -lSDL2_gfx

.PHONY: all clean

all: main
	./main

main: $(OBJECTS) out/main.o
	g++ $^ $(SDL_LIB) $(SDL_GFX_LIB) $(SDL_INCLUDE) $(SDL_GFX_INCLUDE) $(SDL_FLAGS) $(SDL_GFX_FLAGS) -o main

out/%.o: src/%.cpp $(HEADERS)
	g++ -c $(SDL_INCLUDE) $(SDL_GFX_INCLUDE) $< -o $@

clean:
	rm -f QuarriDist.zip
	rm -f out/*
	git checkout lib/cxxtest-4.4/python/cxxtest/*

clean-test:
	rm -r -f out/*.cpp

clean-misc:
	git checkout lib/cxxtest-4.4/python/cxxtest/*

clean-install:
	rm -r -f $(SDL_GFX_SOURCE_PATH) $(SDL_SOURCE_PATH) $(BUILD_DIR)

install:
	@mkdir -p $(BUILD_DIR)
	@if ! [ -d $(SDL_SOURCE_PATH) ]; then tar -zxvf $(SDL_SOURCE_PATH).tar.gz -C $(LIB_DIR); fi; \
	if ! [ -d $(SDL_GFX_SOURCE_PATH) ]; then tar xvf $(SDL_GFX_SOURCE_PATH).tar.gz -C $(LIB_DIR); fi; \
	if [ -d $(SDL_BUILD_PATH) ]; \
		then echo SDL Install complete. Please remove folder $(SDL_BUILD_PATH) if you want to reinstall; \
	else \
		echo Installing SDL; \
		mkdir $(SDL_BUILD_PATH); \
		cd $(SDL_SOURCE_PATH); \
		./configure --prefix=$(SDL_BUILD_PATH); \
		make all; \
		make install; \
		export SDL_CONFIG=$(SDL_BUILD_PATH)/bin/sdl2-config; \
		if [ -d $(SDL_GFX_BUILD_PATH) ]; \
			then echo SDL GFX Install complete. Please remove folder $(SDL_GFX_BUILD_PATH) if you want to reinstall; \
		else \
			echo Installing SDL_GFX; \
			mkdir $(SDL_GFX_BUILD_PATH); \
			cd $(SDL_GFX_SOURCE_PATH); \
			./autogen.sh; \
			./configure --prefix=$(SDL_GFX_BUILD_PATH); \
			make all; \
			make install; \
			rm -f $(SDL_GFX_BUILD_PATH)/lib/libSDL2_gfx-*; \
		fi; \
	fi

test: runner
	./runner

runner: out/runner.cpp $(TESTS) $(HEADERS) $(OBJECTS)
	g++ out/runner.cpp $(OBJECTS) $(TESTS) -I$(SRC_DIR) -I$(CXXTEST_INCLUDE) $(SDL_INCLUDE) $(SDL_GFX_INCLUDE) $(SDL_LIB) $(SDL_GFX_LIB) $(SDL_FLAGS) $(SDL_GFX_FLAGS) -o $@

out/runner.cpp: 
	$(CXXTEST_GEN) --root --error-printer -o $@

out/%TestSuite.cpp: test/%TestSuite.hpp
	$(CXXTEST_GEN) --part --error-printer $< -o $@

dist: main runner $(LEVEL_DIR)
	zip QuarriDist.zip -r $^
