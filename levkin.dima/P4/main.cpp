#include <cstddef>
#include <fstream>
#include <ios>
#include <iostream>

namespace levkin {

char *extend(char *old_buffer, size_t old_size, size_t new_size) {
  char *new_buffer = new char[new_size];
  for (size_t i = 0; i < old_size; i++) {
    new_buffer[i] = old_buffer[i];
  }
  for (size_t i = old_size; i < new_size; i++) {
    new_buffer[i] = ' ';
  }
  delete[] old_buffer;
  return new_buffer;
}

char *getLine(std::istream &in, size_t &size) {
  bool is_skip_ws = in.flags() & std::ios_base::skipws;
  if (is_skip_ws) {
    in >> std::noskipws;
  }

  size = 5;
  char *buffer = new char[size];
  size_t len = 0;

  char c = 0;
  while (in >> c) {
    if (len == size) {
      buffer = extend(buffer, size, size + 5);
      size += 5;
    }
    buffer[len++] = c;
  }

  if (len == size) {
    buffer = extend(buffer, size, size + 1);
    size += 1;
  }
  buffer[len] = '\0';

  if (is_skip_ws)
    in >> std::skipws;

  return buffer;
}

} // namespace levkin

int main() {
  size_t s = 0;
  levkin::getLine(std::cin, s);
  return 0;
}
