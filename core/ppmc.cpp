
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using std::ifstream;
using VectorStr = std::vector<std::string>;

struct MacroDesc
{
  std::string name;
  VectorStr arguments;
  std::string value;
};

using IndexedMacrocesType = std::map<size_t, unsigned>;

void fillMacroIdxs(const MacroDesc(&container)[2], IndexedMacrocesType& macroces, const std::string& str)
{
  for (auto& m : container) 
  {
    auto cur_id = &m - &container[0];
    auto& cur_name = m.name;
    size_t nPos = str.find(cur_name, 0);
    while (nPos != std::string::npos) 
    {
      macroces[nPos] = cur_id;
      // TODO: fill arguments here
      //find '('&& ')'
      //extract arguments
      // insert arguments to MacroDesc 'value' {1},{2}..{n}

      nPos = str.find(cur_name, nPos + 1);
    }
  }
}

VectorStr get_arguments(const std::string& str, size_t& idx)
{
  // TODO: Implement arguments parsing
  return VectorStr();
}

std::string replace_placeholders_in_macro(const MacroDesc&  macro, const VectorStr& arguments)
{
  // TODO: Implement;
  return macro.value;
}

int main(int argc, char * argv[])
{
  //ifstream ifst(argv[1]);
  //if (!ifst.open) {
  //  std::cerr << "Wrong filename\n";
  //}


  std::string str("TEST_TEXT_1 CREATE_GENERALIZATION(ARG_1) TEST_TEXT_2 TEST_TEXT_3 DEFINE_GENERALIZATION_METHOD(ARG_2) TEST_TEXT_4 CREATE_GENERALIZATION(ARG_3)  \n");
  /*
  OUTPUT:
  TEST_TEXT_1
        struct Name {
            int mark;
        };
        int GetSpecNumAndIncrementName();
       TEST_TEXT_2 TEST_TEXT_3
        namespace {
            int specNumber = 0;
        }
        int GetSpecNumAndIncrementName() {
            return specNumber++;
        }
       TEST_TEXT_4
  
  */
  IndexedMacrocesType macroces;
  MacroDesc macro_descs[] = { 
    { 
      "CREATE_GENERALIZATION", 
      {
        "Name"
      },
      R"raw(
        struct [<Name>] { 
            int mark; 
        }; 
        int GetSpecNumAndIncrement[<Name>]();
      )raw" 
    } ,
    { 
      "DEFINE_GENERALIZATION_METHOD", 
      {
        "Name"
      },
      R"raw(
        namespace { 
            int specNumber = 0; 
        } 
        int GetSpecNumAndIncrement[<Name>]() { 
            return specNumber++; 
        }
      )raw" 
    } 
  };
  fillMacroIdxs(macro_descs, macroces, str);

  std::string result;
  size_t prev_idx = 0;
  for (auto& idxs : macroces) 
  {
    auto cur_macro_idx = idxs.second;
    auto cur_pos = idxs.first;
    result += str.substr(prev_idx, cur_pos - prev_idx);

    auto& replacer = macro_descs[cur_macro_idx];
    prev_idx = cur_pos + replacer.name.size();
    auto arguments = get_arguments(str, prev_idx);
    auto replace_text = replace_placeholders_in_macro(replacer, arguments);

    result += replace_text;
  }
  result += str.substr(prev_idx);

  std::cerr << result << std::endl;

  return EXIT_SUCCESS;
}