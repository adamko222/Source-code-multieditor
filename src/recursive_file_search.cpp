#include "../Headers/recursive_file_search.h"


namespace fs = std::filesystem;

Recursive_file_search::Recursive_file_search()
{

}

//std::filesystem::path path = ".";


void Recursive_file_search::file_search(std::string directory_path)
{
  // init Paths file
  std::ofstream out_file("Paths.txt", std::ios::out);

  //fs::exists(directory_path)   check valid directory, if not -> exit
  if (!fs::is_directory(directory_path))
	{
    std::cout << "enterred directory does not exists" << std::endl;
    exit(1);
  }

  if (!out_file.is_open())
  {
    std::cout << "error in writing Path file" << std::endl;
    exit(1);
  }

  //std::cout << "current dir is: "<< fs::current_path() << std::endl;

  // iterate files in all directories
	for (const auto &x : fs::recursive_directory_iterator(directory_path))
	{
    //fs::recursive_directory_iterator(directory_path)
		// or fs::directory_iterator(directory_path)
		std::cout << x.path() << std::endl;
    out_file << x.path() << std::endl;
  }
    out_file.close();
}


// int main(int argc, char **argv) {
//
//   Recursive_file_search R;
//   R.file_search(argv[1]);
//
// }
