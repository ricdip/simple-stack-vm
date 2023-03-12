#pragma once

#include <ostream>

class Logger {
public:
  /**
   * @brief Function used to do INFO level logging
   */
  static std::ostream &info();

  /**
   * @brief Function used to do ERROR level logging
   */
  static std::ostream &error();
};
