#pragma once

#include <iostream>

namespace core {

enum class LogLevel { Info, Warning, Error, Debug };

inline void log(LogLevel level, const std::string &message) {
  switch (level) {
  case LogLevel::Info:
    std::cout << "[INFO] ";
    break;
  case LogLevel::Warning:
    std::cout << "[WARNING] ";
    break;
  case LogLevel::Error:
    std::cerr << "[ERROR] ";
    std::cerr << message << std::endl;
    return;
  case LogLevel::Debug:
    std::cout << "[DEBUG] ";
    break;
  default:
    std::cout << "[INFO] ";
    break;
  }
  std::cout << message << std::endl;
}

} // namespace core
