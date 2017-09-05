
#include <iostream>
#include <fstream>
#include <string>
#include <map>


using std::ifstream;

struct MacroDesc
{
  std::string name;
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

int main(int argc, char * argv[])
{
  //ifstream ifst(argv[1]);
  //if (!ifst.open) {
  //  std::cerr << "Wrong filename\n";
  //}

  std::string str("first MACRO2 line MACRO1 of MACRO2 file\n");
  //               first float() line int() of float() file

  IndexedMacrocesType macroces;
  MacroDesc macro_descs[] = { { "MACRO1", "int()" } ,{ "MACRO2", "float()" } };
  fillMacroIdxs(macro_descs, macroces, str);

  std::string result;
  size_t prev_idx = 0;
  for (auto& idxs : macroces) 
  {
    auto cur_macro_idx = idxs.second;
    auto cur_pos = idxs.first;
    result += str.substr(prev_idx, cur_pos - prev_idx);

    auto& replacer = macro_descs[cur_macro_idx];
    result += replacer.value;
    prev_idx = cur_pos + replacer.name.size();
  }
  result += str.substr(prev_idx);

  std::cerr << result << std::endl;

  return EXIT_SUCCESS;
}