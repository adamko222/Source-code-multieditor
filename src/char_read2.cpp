#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

static uint32_t count = 0;
void *operator new(size_t size) {
  count++;
  std::cout << "Alocating: " << size << '\n';
  return malloc(size);
}

int main() {
  std::string filename = "text.txt";
  std::ifstream file(filename, std::ios::in);

  // size of file to reserve buffer, additional +1024 chars for inserting
  // purposes ...
  int size = fs::file_size(filename);

  // check if file is open.
  if (!file.is_open()) {
    std::cout << "cannot open file !" << std::endl;
    exit(1);
  }

  int num = 0;
  int numspaces = 0;

  // int size = fs::file_size(filename);

  std::string STRING;
  // reserve buffer
  STRING.reserve(size);

  char chars[size];

  // STRING.shrink_to_fit(); // optimize capacity of buffer
  // STRING.clear();        // will wipe out all string.

  // std::string_view str = STRING;

  while (!file.eof()) {
    file.read(chars, size);
  }

  // close file.
  file.close();

  STRING = std::string(chars);

  std::cout << STRING;

  for (int i = 0; i <= size; i++) {
    // std::cout <<STRING[i];
    // check rows
    if (STRING[i] == '\n') {
      num++;
    }
    // check spaces
    if (STRING[i] == ' ') {
      numspaces++;
    }
  }
  std::cout << "string at 7: " << STRING.at(7) << std::endl;
  std::cout << "string [9]: " << STRING[9] << std::endl;
  std::cout << "rows: " << num << std::endl;
  std::cout << "spaces: " << numspaces << std::endl;
}
