#include "chunk.h"
#include <cstddef>
#include <vector>
namespace std {
  template struct vector<std::byte>;
  template struct vector<Lox::Value>;
  template struct variant<std::monostate, bool, double, std::string>;
  template class std::basic_string<char>;
}
