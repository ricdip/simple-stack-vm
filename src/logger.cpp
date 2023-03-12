#include "include/logger.hpp"

#include <iostream>

std::ostream &Logger::info() { return std::cout << " [INFO]\t "; }

std::ostream &Logger::error() { return std::cout << "[ERROR]\t "; }
