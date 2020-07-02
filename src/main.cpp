#include "../Headers/options.h"
#include "../Headers/recursive_file_search.h"

using namespace std;


int main(int argc, char **argv) {

  Options O;

  O.arguments(argc, argv);
  //std::cout << "in_dirname:  " << O.in_dirname << std::endl;
  //std::cout << "out_dirname:  " << O.out_dirname << std::endl;

  Recursive_file_search R;
  R.file_search(O.in_dirname);



  return 0;
}
