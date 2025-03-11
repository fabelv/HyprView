BUILD_DIR = build
EXECUTABLE = hyprview
CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=1

all: clean configure build update_compile_commands

clean:
	@rm -rf $(BUILD_DIR) compile_commands.json

configure:
	@cmake -B $(BUILD_DIR) $(CMAKE_FLAGS)

build:
	@cmake --build $(BUILD_DIR)

update_compile_commands:
	@mv $(BUILD_DIR)/compile_commands.json . 

run: build
	@./$(BUILD_DIR)/$(EXECUTABLE)

# Phony targets
.PHONY: all clean configure build update_compile_commands run
