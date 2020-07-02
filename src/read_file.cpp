#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int main(int argc, char *argv[])
{

	std::ifstream in_file("Paths.txt", std::ios::in);

	std::string content = "";

	if (! in_file.is_open())
	{
		std::cout << "cannot open file" << std::endl;
		exit(1);
	}


	//while (getline(in_file, content))
	//{
		//std::cout << content << std::endl;
	//}

    getline(in_file, content);
    std::cout << content << std::endl;
    in_file.close();
    
    // erase " quotes, at begining, each file have to starts with ./ 
    content = content.erase(0, 1);
    // erase " quotes, at ending
    content = content.erase(content.length()-1, 1);
    
    std::cout << content << std::endl;
    
    //for(int i = 0; i <= 10; i++){
    
    std::ifstream in_file2(content, std::ios::in);
    if (! in_file2.is_open())
	{
		std::cout << "cannot open file" << std::endl;
		exit(1);
	}
    while (getline(in_file2, content))
	{
		std::cout << content << std::endl;
	}

	in_file2.close();
    //}
}
