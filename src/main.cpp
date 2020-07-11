#include "../Headers/options.h"
#include "../Headers/read_file.h"
#include "../Headers/recursive_file_search.h"

using namespace std;

int main(int argc, char **argv) {

  Options O;

  O.arguments(argc, argv);

  // R.~Recursive_file_search();
  Recursive_file_search R;
  R.iterate_files(O.in_dirname);

  // for (auto it : R.paths) {
  //   std::cout << "paths: " << it << std::endl;
  // }

  Read_file RF(R.paths);

  // std::cout << "numoffiles from RF:  " << RF.NumOfFiles << std::endl;

  return 0;
}
