#ifndef READ_FILE
#define READ_FILE

#include "standard_headers.h"

class Read_file {
public:
  Read_file() = delete;
  Read_file(const std::vector<std::string> &paths);
  void read_file(std::string directory_path);
  int NumOfFiles;

  std::string paths;
  std::string content;
};

#endif
