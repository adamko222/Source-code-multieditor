#ifndef OPTIONS_H
#define OPTIONS_H

#include "standard_headers.h"

class Options {
public:
  std::string in_dirname;
  std::string out_dirname;

  Options();
  void arguments(int argc, char *argv[]);

private:
  const std::string option_input_dir;
  const std::string option_output_dir;
};

#endif
