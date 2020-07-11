#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <string_view>
#include <vector>

int main() {

  std::string str = "ahojky to som zasa ja a som tu to sa stále";

  std::string::size_type Search_For_String;

  std::string s = "x";

  Search_For_String = str.find(s);
  if (Search_For_String == std::string::npos) {
    std::cout << "new variable:  " << s << "\n";
  }
  std::cout << Search_For_String << " position\n";
}
