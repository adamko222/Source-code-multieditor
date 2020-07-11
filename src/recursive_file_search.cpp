#include "../Headers/recursive_file_search.h"

namespace fs = std::filesystem;

Recursive_file_search::Recursive_file_search() {
  // std::filesystem::path path = ".";
}

void Recursive_file_search::iterate_files(const std::string directory_path) {
  // paths.reserve(1024);

  // init Paths file
  std::ofstream out_file("Paths.txt", std::ios::out);

  // fs::exists(directory_path)   check valid directory, if not -> exit
  if (!fs::is_directory(directory_path)) {
    std::cout << "enterred directory does not exists" << std::endl;
    exit(1);
  }

  if (!out_file.is_open()) {
    std::cout << "error in writing Path file" << std::endl;
    exit(1);
  }

  std::cout << "current dir is: " << fs::current_path() << std::endl;

  // iterate through files in all directories.
  for (const auto &path : fs::recursive_directory_iterator(directory_path)) {
    // fs::recursive_directory_iterator(directory_path)
    // or fs::directory_iterator(directory_path)
    // path.path().string();

    // select source code files only by their extensions .
    if (path.path().extension() == ".cpp" ||
        path.path().extension() == ".hpp" || path.path().extension() == ".h" ||
        path.path().extension() == ".c") {
      // write into file for further processing. Use functions for string
      std::cout << path.path().string() << std::endl;
      out_file << path.path().string() << std::endl;

      paths.push_back(path.path());
    }
  }

  // for (auto it : paths) {
  //   std::cout << "paths: " << it << std::endl;
  // }

  // set position pointer on top of the file
  // out_file.seekp(0);
  // close file.
  out_file.close();
}

// int main(int argc, char **argv) {
//
//   Recursive_file_search R;
//   R.file_search(argv[1]);
//
// }
