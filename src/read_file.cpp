#include "../Headers/read_file.h"

Read_file::Read_file(const std::vector<std::string> &paths) {
  // std::cout << "from read_file nums of files:   " << NumOfFiles << std::endl;
  // std::ifstream paths_file("Paths.txt", std::ios::in);
  // if (! paths_file.is_open())
  // {
  // 	std::cout << "cannot open file" << std::endl;
  // 	exit(1);
  // }
  std::cout << "" << std::endl;

  int NumOfFiles = paths.size();
  std::cout << NumOfFiles << " Files to process." << std::endl;

  if (NumOfFiles == 0) {
    std::cout << "there are no such files we can deal with, please provide "
                 ".cpp/.c/.h  etc.source code extension files."
              << std::endl;
    exit(1);
  }

  for (int i = 0; i < NumOfFiles; i++) {
    // std::string paths = "";
    // getline(paths_file, paths);
    //
    // if (paths == "") {
    // 	std::cout << "empty variable paths !!!" << paths << std::endl;
    // }
    std::cout << "********************************processing:  " << paths[i]
              << "*********************************\n"
              << std::endl;

    read_file(paths[i]);
  }

  // erase " quotes, at begining, each file have to starts with ./

  // paths = paths.erase(0, 1);
  // erase " quotes, at ending
  // paths = paths.erase(paths.length()-1, 1);

  // paths_file.close();
}

void Read_file::read_file(std::string directory_path) {

  std::ifstream in_file(directory_path, std::ios::in);

  if (!in_file.is_open()) {
    std::cout << "cannot open file" << std::endl;
    exit(1);
  }

  std::string content = "";

  // for(int i = 0; i <= 10; i++){
  while (!in_file.eof()) {
    getline(in_file, content);
    std::cout << content << std::endl;
  }

  in_file.clear();
  in_file.close();
}
