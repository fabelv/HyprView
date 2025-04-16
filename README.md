
# HyprView

[![Code Coverage](https://app.deepsource.com/gh/fabelv/HyprView.svg/?label=code+coverage&show_trend=true&token=fKkgwXDw-xh90oVJeIu92EW7)](https://app.deepsource.com/gh/fabelv/HyprView/)
[![Active Issues](https://app.deepsource.com/gh/fabelv/HyprView.svg/?label=active+issues&show_trend=true&token=fKkgwXDw-xh90oVJeIu92EW7)](https://app.deepsource.com/gh/fabelv/HyprView/)
[![Resolved Issues](https://app.deepsource.com/gh/fabelv/HyprView.svg/?label=resolved+issues&show_trend=true&token=fKkgwXDw-xh90oVJeIu92EW7)](https://app.deepsource.com/gh/fabelv/HyprView/)

[![Quality Gate](https://sonarcloud.io/api/project_badges/measure?project=fabelv_HyprView&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=fabelv_HyprView)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=fabelv_HyprView&metric=bugs)](https://sonarcloud.io/summary/new_code?id=fabelv_HyprView)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=fabelv_HyprView&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=fabelv_HyprView)
[![Duplicated Lines](https://sonarcloud.io/api/project_badges/measure?project=fabelv_HyprView&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=fabelv_HyprView)

---

**HyprView** is a Qt-based monitor layout manager for [Hyprland](https://github.com/hyprwm/Hyprland).  
Easily visualize and configure multi-monitor setups with a modern UI.

<p align="center">
  <img src="./res/app.png" alt="App Screenshot" width="600"/>
</p>

---

## Try out Tool
```
nix run github:fabelv/HyprView
```

---

## Setup

```bash
git clone https://github.com/fabelv/HyprView.git
cd HyprView
nix develop
make
```

That's it — the project will be built and ready to run!

To launch:
```bash
./build/hyprview
```

---

## Project Structure

- `src/` - Main application logic
- `lib/` - Core components (logic, models, managers)
- `include/` - Header files
- `test/` - Unit and integration tests
- `res/` - Assets like images and QML resources
- `flake.nix` / `shell.nix` - Nix Flake setup for reproducible dev environments
- `CMakeLists.txt` - Build configuration

---

## Dev Tools

- Qt 6
- C++23
- CMake + Ninja
- GoogleTest for unit testing
- Clangd + `compile_commands.json` for IDE support
- DeepSource & SonarCloud for static analysis

---

## CI & Quality Checks

GitHub Actions runs:
- Build & test
- Static analysis with cppcheck & clang-tidy
- Code coverage reports (optional)

See `.github/workflows/ci.yaml` for details.

---

## Testing

To run tests locally:
```bash
make test
```

---


