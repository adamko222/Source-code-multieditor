#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

// std::map<std::string, int> UserContainers;
// // UserContainers.insert("UserContainerName", "Length");

// // maybe other stl function will be in file and loading them here, or
// // i declare them here
// std::map<std::string, int> UserContainers;
// // UserContainers.insert("UserContainerName", "Length");

// std::vector<std::string> DataTypes = {"int",   "void",   "bool", "double",
//                                       "float", "size_t", "char", "string",
//                                       "NULL",  "nullptr"};
//
// std::vector<std::string> Class_Struct_Keywords = {
//     "class",   "struct", "public", "private", "static", "protected",
//     "virtual", "friend", "inline", "union",   "mutable"};
//
// std::vector<std::string> Other_Operators = {
//     ";", "(",  "(",  "{", "}", "<", ">",  "<<", ">>", "=",
//     "!", "\"", "\'", "*", "&", "/", "\\", "-",  "+"};
// std::vector<std::string>::iterator it;

int Count_Newline = 0;
int Count_Spaces = 0;
int Count_Left_Bracket = 0;
int Count_Right_Bracket = 0;
int Count_Left_Curly_Bracket = 0;
int Count_Right_Curly_Bracket = 0;
int Count_Semi_Column = 0;
int Count_Comments = 0;
int Count_Class = 0;
int Count_Int = 0;
int Count_bool = 0;

uint16_t RemainingLength = 0; /* calculate length of substring */
int Position_Space_Count = 0; /* no space chars helpful count variable */
std::string_view STRING_SUB;  /* make substring view separated words */
// bool Parsed = false;          /* decide when to analyzeand store data  */

// string and its length
std::map<std::string, int> DataTypes = {{"bool", 4},
                                        {"int", 3},
                                        /*{"uint32_t", 8},*/
                                        {"double", 6},
                                        {"float", 5},
                                        {"char", 4},
                                        {"string", 6},
                                        /*{"std::string", 11},*/
                                        {"size_t", 6},
                                        {"NULL", 4},
                                        {"nullptr", 7},
                                        {"typedef", 7},
                                        {"template", 8},
                                        {"extern", 6},
                                        {"explicit", 8}
                                        /*,{"noexpr", 8}*/};

std::map<std::string, int, std::string> DataTypess;

std::map<std::string, int> Class_Struct_Keywords = {
    {"class", 5},     {"struct", 6}, {"public", 5},  {"private", 6},
    {"protected", 9}, {"static", 6}, {"virtual", 7}, {"friend", 6},
    {"inline", 6},    {"union", 5},  {"mutable", 7}};

std::map<std::string, int> Other_Operators = {
    {";", 1},  {"(", 1},  {")", 1},  {"{", 1},  {"}", 1},  {">", 1},  {"<", 1},
    {"<<", 2}, {">>", 2}, {"=", 1},  {"==", 2}, {"!=", 2}, {"\'", 1}, {"\"", 1},
    {"*", 1},  {"\\", 1}, {"&", 1},  {"&&", 2}, {"|", 1},  {"||", 2}, {"-", 1},
    {"+", 1},  {":", 1},  {"::", 2}, {"#", 1},  {"?", 1}};

std::map<std::string, int> UserVariables;

inline bool
Is_Numeric(const std::string_view &Substring /*, const int &Substr_Length*/) {
  // // check for numbers / numeric initialized values

  if (std::atoi(Substring.data())) {
    std::cout << "this is a number: " << std::atoi(Substring.data()) << ", "
              << Substring << "\n";
    return true; /* must be, without return it will be determined as variable */
  } else {
    return false;
  }
}

inline void AddVariable(const std::string_view &STRING,
                        const int &SubstrLength) {
  // std::cout << "adding variable:  " << std::string(STRING) << "\n";
  UserVariables.insert({std::string(STRING), STRING.length()});
}

// string word, length *2
inline bool
Is_All_Parsed(const std::string &Map_String, /* str. to avoid */
              const int &Map_String_Length,  /* str. length to move */
              std::string_view &Substring,   /* view */
              const int &Substr_Length,      /* full length */
              const int &Start_String_Index, /* start position */
              bool &Parsed) {

  // has SubstrLength still more characters --> parsing continues.
  RemainingLength = Substr_Length - Map_String_Length;
  if (RemainingLength != 0) {
    // std::cout << "writing false, remain length of string to parse: "
    // << RemainingLength << "\n";

    // find std:: namespace and cut it
    if (Substring.find("std::") != std::string::npos) {
      Substring.remove_prefix(5);
      std::cout << "std:: is here !!!!!!!!" << Substring << std::endl;
    }

    // prefix Moves the start of the view forward by n characters.
    // suffix Moves the end of the view back by n characters.
    else if (Start_String_Index == 0) {
      Substring.remove_prefix(Map_String_Length);
    } else {
      Substring.remove_suffix(Map_String_Length);
    }

    // after moving view pointer position check if there is numeric value remain
    // also need to check if(!Parsed) in function in case for ex. 155
    if (Is_Numeric(Substring)) {
      return true;
    }

    // std::cout << "new Substring: " << Substring << "\n";
    return false;

    // RemainingLength == 0
  } else {
    // std::cout << "writing true:  " << RemainingLength << "\n";
    RemainingLength = 0;
    Parsed = true;
    return true;
  }
}

void Further_Search(std::string_view &STRING, const int &SubstrLength,
                    bool Parsed) {
  // some way required this type
  std::string::size_type Index;

  std::map<std::string, int>::iterator iter;

  // DataType search.
  for (iter = DataTypes.begin(); iter != DataTypes.end(); iter++) {

    // find -> first elem, rfind -> last elem in text
    Index = STRING.find(iter->first);
    // std::cout << "comparing " << STRING << " with " << iter->first <<
    // std::endl;

    if (Index != std::string::npos) {

      if (iter->first == "int") { /* in there will check types like uint32_t */
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "int is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "bool") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "bool is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "double") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "int is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "float") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "bool is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "char") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "int is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "string") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "bool is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "size_t") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "int is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "NULL") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "bool is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "nullptr") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "int is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "typedef") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "bool is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "template") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "int is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "extern") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "bool is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }

      } else if (iter->first == "explicit") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "bool is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      }
    }
  }

  for (iter = Class_Struct_Keywords.begin();
       iter != Class_Struct_Keywords.end(); iter++) {

    // std::cout << "processing:  " << STRING << std::endl;

    Index = STRING.find(iter->first);
    // std::cout << "comparing " << STRING << " with " << iter->first <<
    // std::endl;

    if (Index != std::string::npos) {

      if (iter->first == "class") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "struct") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "public") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "private") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      }
      if (iter->first == "protected") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "static") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "virtual") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "friend") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }

      } else if (iter->first == "inline") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "union") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }

      } else if (iter->first == "mutable") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      }
    }
  }

  for (iter = Other_Operators.begin(); iter != Other_Operators.end(); iter++) {

    Index = STRING.find(iter->first);
    // std::cout << "comparing " << STRING << " with " << iter->first <<
    // std::endl;

    if (Index != std::string::npos) {

      if (iter->first == ";") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "semi-colums is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        } // ending with semi-column sooo

      } else if (iter->first == "(") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == ")") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "{") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      }
      if (iter->first == "}") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "<") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == ">") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "<<") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }

      } else if (iter->first == ">>") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "=") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }

      } else if (iter->first == "==") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "!=") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "\'") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "\"") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "\\") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
        // here check if reference or in statement
      } else if (iter->first == "&" || iter->first == "&&") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }

      } else if (iter->first == "|" || iter->first == "||") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
        // here check if pointer or multiplication
      } else if (iter->first == "*") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
        // subtracting
      } else if (iter->first == "-") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
        // counting / addition
      } else if (iter->first == "+") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
        // division
      } else if (iter->first == "/") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == ":") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "::") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      } else if (iter->first == "?") {
        // std::cout << iter->first << " should end up here!!!" << std::endl;
        // std::cout << "class is here:  " << STRING << "\n";
        if (Is_All_Parsed(iter->first, iter->second, STRING, SubstrLength,
                          Index, Parsed)) {
          return;
        }
      }
    }
  }
  //***************************************************************************
  // also need to check if(!Parsed) in function in case for ex. 155, however,
  // this is not exactly any language syntax
  // if (Is_Numeric(STRING)) {
  //   return;
  // }
  //***************************************************************************

  // default case, there must be variable, array etc.
  if (!Parsed) {
    AddVariable(STRING, SubstrLength);
    Parsed = true;
  }
}

// static uint32_t count = 0;
// void *operator new(size_t size) {
//   count++;
//   std::cout << "Alocating: " << size << '\n';
//   return malloc(size);
// }

int main() {

  std::string filename = "options.cpp";
  std::ifstream file(filename, std::ios::in);

  // size of file to reserve buffer, additional +1024 chars for inserting
  // purposes ...
  int size = fs::file_size(filename);

  // check if file is open.
  if (!file.is_open()) {
    std::cout << "cannot open file !" << std::endl;
    exit(1);
  }

  // int size = fs::file_size(filename);

  std::string STRING;
  // reserve buffer
  STRING.reserve(size);
  // initialize stringstream buffer to read file.
  std::ostringstream StreamBuffer;
  // read file.
  StreamBuffer << file.rdbuf();
  // clear buffer.
  StreamBuffer.clear();

  // close file.
  file.close();

  // transform to string
  STRING = StreamBuffer.str();
  // STRING.shrink_to_fit(); // optimize capacity of buffer
  // STRING.clear();        // will wipe out all string.

  // std::string_view str = STRING;

  std::cout << STRING;

  for (int i = 0; i <= size; i++) {
    Position_Space_Count++;
    // std::cout <<STRING[i];

    // handle comments, then find end character \n and jump there in string
    // (i tried do this with bool, but something went wrong so i end up there)
    if (STRING[i] == '/' && STRING[i + 1] == '/') {
      // std::cout << "comments of type //---// at positions: " << i << '\n';
      i = STRING.find('\n', i);
    }
    // handle comments, then find end character */ and jump there in string
    // +2 - length of */ exactly to escape comment field
    if (STRING[i] == '/' && STRING[i + 1] == '*') {
      // std::cout << "comments of type /*---*/ at positions: " << i << '\n';
      i = STRING.find("*/", i) + 2;
    }

    // extract all words, and call funtion for deeper search.
    if (STRING[i] == ' ' || STRING[i] == '\n') {

      // i starts from 0 so it is needed to calculate indexes
      STRING_SUB = STRING.substr((i + 1) - Position_Space_Count,
                                 Position_Space_Count - 1);
      // std::cout << Position_Space_Count << " " << i << " " << STRING_SUB
      //           << std::endl;

      // check if there is no multiple '\n' or ' ' following = no characters.
      if (STRING_SUB.length() != 0) {
        // std::cout << STRING_SUB << std::endl;
        Further_Search(STRING_SUB, STRING_SUB.length(), false);
      }

      Position_Space_Count = 0;
    }

    // check rows
    if (STRING[i] == '\n') {
      Count_Newline++;
    }
    // check spaces
    if (STRING[i] == ' ') {
      Count_Spaces++;
    }
  }
  std::cout << Count_Newline << std::endl;
  std::cout << Count_Spaces << std::endl;
  // std::cout << Count_Left_Bracket << std::endl;
  // std::cout << Count_Right_Bracket << std::endl;
  // std::cout << Count_Left_Curly_Bracket << std::endl;
  // std::cout << Count_Right_Curly_Bracket << std::endl;
  // std::cout << Count_Semi_Column << std::endl;
  // std::cout << Count_Class << std::endl;
  // std::cout << Count_Int << std::endl;

  // std::cout << MyMap["int"];

  std::map<std::string, int>::iterator iter;

  for (iter = UserVariables.begin(); iter != UserVariables.end(); iter++) {
    std::cout << iter->first << "  -->  " << iter->second << std::endl;
  }
}
