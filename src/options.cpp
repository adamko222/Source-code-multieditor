#include "../Headers/options.h"
#include <cstring>
#include <vector>



std::string in_dirname;
std::string out_dirname;

Options::Options(){}

void Options::arguments(int argc, char *argv[])
{
  const std::string OPT_IN = "-i";
  const std::string OPT_OUT = "-o";
  
  
  if(argc <= 2)
  {
    std::cout << "No arguments provided provided. " << std::endl;
    exit(1);
  }
  for(int i=0; i< argc; i++)
  {
 	  // get input dir from user
    if (argv[i] == OPT_IN)
    {
      in_dirname = argv[i + 1];
    }
    // get output dir from user
    if (argv[i] == OPT_OUT)
    {
      out_dirname = argv[i + 1];
    }
  }

  if (in_dirname == "")
  {
    std::cout << "input directory not provided. " << std::endl;
    exit(1);
  }

  if (out_dirname == "")
  {
    std::cout << "output directory not provided. " << std::endl;
    exit(1);
  }
}
