#ifndef FILE_SEARCH
#define FILE_SEARCH

#include "standard_headers.h"

class Recursive_file_search {
public:
  Recursive_file_search();
  void iterate_files(const std::string directory_path);
  std::vector<std::string> paths; // array holds file names
};

#endif
