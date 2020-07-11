#include <iostream>
#include <string>
#include <string_view>

using namespace std;
static uint32_t count = 0;
void *operator new(size_t size) {
  count++;
  std::cout << "Alocating: " << size << '\n';
  return malloc(size);
}

void print(const std::string &name) // string_view
{
  std::cout << name << '\n';
}

int main(int argc, char **argv) {

  std::string strr = "ahojky to som ja a nikto iný ";
  std::string strra = "sajkdfhkjlasdhfkjsadl";

  const char *str = "ahojky to som ja a nikto iný ";
  // const std::string substr = str.substr(0, 16);
  // std::string_view strr(str, 20);
  // std::string_view strra = "sajkdfhkjlasdhfkjsadl";

  print(strr);
  print(strra);
  print(str);

  std::cout << "Alocations: " << count << '\n';
  return 0;
}
