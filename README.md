# HyprView  

HyprView is a Qt-based C++ application for managing monitor layouts in Hyprland.  

## Setup  

### Development Shell  
Run the following command to enter the development environment:  
`nix develop`  

This provides:  
- Qt5 for UI development  
- Clangd for LSP support  
- CMake and Ninja for building  

### Build the Project  
To build the project manually, run:  
```
cmake -B build  
cmake --build build  
./build/hyprview  
```

### Generate `compile_commands.json`  
To enable Clangd autocompletion in Neovim, generate the compilation database with:  
`sh compile_commands_cmake.sh`  

### Build with Nix  
To build using Nix Flakes, run:  
```
nix build .#hyprview  
./result/bin/hyprview  
```
