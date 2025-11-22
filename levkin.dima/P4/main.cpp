#include <cstddef>
#include <ios>
#include <iostream>

namespace levkin {

char *extend(char *old_buffer, size_t old_size, size_t new_size) {
  char *new_buffer = reinterpret_cast<char*>(malloc(new_size));
  if (!new_buffer)
    return nullptr;

  for (size_t i = 0; i < old_size; i++) {
    new_buffer[i] = old_buffer[i];
  }
  for (size_t i = old_size; i < new_size; i++) {
    new_buffer[i] = ' ';
  }

  free(old_buffer);
  return new_buffer;
}

char *getLine(std::istream &in, size_t &size) {
  bool is_skip_ws = in.flags() & std::ios_base::skipws;
  if (is_skip_ws) {
    in >> std::noskipws;
  }

  size = 5;
  char *buffer = (char *)malloc(size);
  if (!buffer)
    return nullptr;

  size_t len = 0;

  char c;
  while (in >> c) {
    if (len == size) {
      buffer = extend(buffer, size, size + 5);
      if (!buffer)
        return nullptr;
      size += 5;
    }
    buffer[len++] = c;
  }

  if (len == size) {
    buffer = extend(buffer, size, size + 1);
    if (!buffer)
      return nullptr;
    size += 1;
  }

  buffer[len] = '\0';

  if (is_skip_ws)
    in >> std::skipws;

  return buffer;
}
char *lat_rmv(const char * const original, char *destination, size_t & s) {
    if (!original || !destination) {
        return NULL;
    }

    size_t w = 0;
    
    for (size_t r = 0; original[r] != '\0'; r++) {
        char ch = original[r];

        if ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z')) {
            continue;
        }

        destination[w++] = ch;
    }
    s = w;
    destination[w] = '\0';
    return destination;
}
int has_rep(const char *s) {
    int visited[256] = {0};

    for (int i = 0; s[i] != '\0'; i++) {
        unsigned char c = s[i];
        if (visited[c] == 1) {
            return 1;
        }
        visited[c] = 1; 
    }

    return 0; 
}

} // namespace levkin

int main() {
  size_t s = 0;
  const char * string = levkin::getLine(std::cin, s);
  std::cout << "has rep: " <<levkin::has_rep(string) << "\n";
  
  char * cleaned_string = new char[s];
  std::cout << "removed eng lett: " <<levkin::lat_rmv(string,cleaned_string, s) << "\n";
  return 0;
}
