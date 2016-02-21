build_dir = build
include_dir = include
src_files := $(wildcard src/*.cpp)
obj_files := $(src_files:src/%.cpp=$(build_dir)/%.o)
test_src_files := $(filter-out tests/tests.cpp,$(wildcard tests/*.cpp))
test_obj_files := $(test_src_files:%.cpp=$(build_dir)/%.o)

dep_json_url = https://raw.githubusercontent.com/nlohmann/json/2468631dc9407ce0be46e96e720d628e1b38b967/src/json.hpp
dep_json_name := $(shell basename $(dep_json_url))
dep_catch_url = https://raw.githubusercontent.com/philsquared/Catch/c7243562b0df490f80637a9481a7af250aec908b/single_include/catch.hpp
dep_catch_name := $(shell basename $(dep_catch_url))

CXX ?= g++
CXXFLAGS += -std=c++14 -pthread -I $(include_dir) -I src

comp = $(CXX) $(CXXFLAGS)

# .SILENT:
.PHONY: all test run_tests clean docs debug

all: dependencies $(build_dir) chess_backend

dependencies: $(include_dir) $(include_dir)/$(dep_json_name)

$(include_dir):
	mkdir -p $@

$(include_dir)/$(dep_json_name):
	wget -O $@ -q $(dep_json_url)

$(build_dir):
	mkdir $(build_dir)

chess_backend: main.cpp $(obj_files)
	$(comp) -o $(build_dir)/$@ $^

$(build_dir)/%.o: src/%.cpp src/%.hpp
	mkdir -p $(shell dirname $@)
	$(comp) -c -o $@ $<

$(build_dir)/%.o: src/%.cpp
	mkdir -p $(shell dirname $@)
	$(comp) -c -o $@ $<

test: include_tests/$(dep_catch_name) $(build_dir)/run_tests run_tests

$(build_dir)/run_tests: tests/tests.cpp $(test_obj_files) $(obj_files)
	$(comp) -I include_tests -o $@ $^

$(build_dir)/tests/%.o: tests/%.cpp
	mkdir -p $(shell dirname $@)
	$(comp) -c -I include_tests -o $@ $<

run_tests: $(build_dir)/run_tests
	./$(build_dir)/run_tests

include_tests/$(dep_catch_name):
	mkdir -p $(shell dirname $@)
	echo "fetching $(dep_catch_name)..."
	wget -q -O $@ $(catch_url)

clean:
	rm -rf $(build_dir)
	$(MAKE) -C docs clean

docs:
	$(MAKE) -C docs

debug:
	echo $(src_files)
	echo $(obj_files)
	echo $(test_src_files)
	echo $(test_obj_files)
