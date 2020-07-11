#include "../Headers/options.h"

Options::Options(){};

void Options::arguments(int argc, char *argv[]) {

  if (argc <= 2) {
    std::cout << "No arguments provided provided. " << std::endl;
    exit(1);
  }
  for (int i = 0; i < argc; i++) {
    // get input dir from user -i <in_file>
    if (std::strncmp(argv[i], "-i", 2) == 0) {
      in_dirname = argv[i + 1];
    }
    // get output dir from user -o <out_file>
    if (std::strncmp(argv[i], "-o", 2) == 0) {
      out_dirname = argv[i + 1];
    }
  }

  // chceck if input, output directories are provided.
  if (in_dirname.empty()) {
    std::cout << "input directory not provided. " << std::endl;
    exit(1);
  }

  if (out_dirname.empty()) {
    std::cout << "output directory not provided. " << std::endl;
    exit(1);
  }
}
