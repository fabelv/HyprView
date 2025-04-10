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
    break;
  case LogLevel::Debug:
    std::cout << "[DEBUG] ";
    break;
  }
  std::cout << message << std::endl;
}

} // namespace core
