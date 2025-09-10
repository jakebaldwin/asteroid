#ifndef LOGGER_H
#define LOGGER_H
#include <format>
#include <iostream>

enum class LogLevel { None, Debug, Info, Error };

template <LogLevel Level> class Logger {
public:
  template <typename... Args>
  static void log(std::format_string<Args...> format,
                  Args &&...args) { // This line must change
    if constexpr (Level == LogLevel::Info) {
      std::cout << "[DEBUG] "
                << std::format(format, std::forward<Args>(args)...)
                << std::endl;
    }
  }
};
#endif
