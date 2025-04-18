BUILD_DIR = build
EXECUTABLE = hyprview
TEST_EXECUTABLE = hyprview_tests
CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Debug -DCODE_COVERAGE=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=1

CPPCHECK_FLAGS = --enable=all --inconclusive --suppress=missingIncludeSystem --include=cppcheck-qt.cfg
SRC_FILES := $(shell find lib src -name '*.cpp')
INCLUDE_DIRS = -Iinclude -Isrc -I$(BUILD_DIR) 

all: clean configure build update_compile_commands

clean:
	@rm -rf $(BUILD_DIR) compile_commands.json

configure:
	@cmake -B $(BUILD_DIR) $(CMAKE_FLAGS) -G Ninja

build: configure
	@cmake --build $(BUILD_DIR)

lib: configure
	@cmake --build $(BUILD_DIR) --target hyprview_core

update_compile_commands:
	@cp $(BUILD_DIR)/compile_commands.json .

run: build
	@./$(BUILD_DIR)/$(EXECUTABLE)

format:
	@find include lib src test \( -name "*.cpp" -o -name "*.h" \) -exec clang-format --dry-run --Werror {} +

fix-format:
	@find include lib src test \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -i {} +

test: build
	@./$(BUILD_DIR)/$(TEST_EXECUTABLE)

lint: configure
	@clang-tidy $(SRC_FILES) -p $(BUILD_DIR) --extra-arg=-std=c++23 --extra-arg=-Iinclude --extra-arg=-Isrc

analyze:
	@cppcheck $(CPPCHECK_FLAGS) $(INCLUDE_DIRS) $(SRC_FILES)

deps: clean configure update_compile_commands

# Phony targets
.PHONY: all clean configure build update_compile_commands run test lint analyze deps

