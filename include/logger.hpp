#pragma once

#include <ostream>

class Logger {
public:
  static std::ostream &info();
  static std::ostream &error();
};
