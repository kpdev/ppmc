
#include "../macro_description/macro_description.hpp"

#include <iostream>
#include <fstream>
#include <map>
#include <cassert>
#include <memory>

#ifdef __has_include                             // Check if __has_include is present
#  if __has_include(<filesystem>)                // Check for a standard library
#    include<filesystem>
#  elif __has_include(<experimental/filesystem>) // Check for an experimental version
#    include <experimental/filesystem>
#  else                                          // Not found at all
#     error "Missing <filesystem>"
#  endif
#elif
#  error("No has_inculde")
#endif


namespace fs = std::experimental::filesystem::v1;
using IndexedMacrocesType = std::map<size_t, unsigned>;


void fill_macro_idxs(const MacroDesc(&container)[macroces_count], IndexedMacrocesType& macroces, const std::string& str)
{
  for (auto& m : container) 
  {
    auto cur_id = &m - &container[0];
    auto& cur_name = m.name;
		size_t nPos = str.find(cur_name, 0);
    while (nPos != std::string::npos)
    {
      macroces[nPos] = cur_id;
      nPos = str.find(cur_name, nPos + 1);
    }
  }
}


std::string parse_arg(const std::string& str, size_t& idx, bool is_vararg)
{
  std::string result;
  unsigned parenteses_level = 0;
  while ((is_vararg || (!is_vararg && str[idx] != ','))
    && (str[idx] != ')' || parenteses_level > 0))
  {
    if (str[idx] == '(')
      ++parenteses_level;
    else if (str[idx] == ')' && parenteses_level != 0)
      --parenteses_level;

    const char cur_char = str[idx++];
    if (cur_char != ' ')
      result += cur_char;
  }
  return result;
}


VectorStr get_arguments(const std::string& str, size_t& idx, const VectorStr& arguments_names)
{
  assert(str[idx] == '(');
  idx++;
  VectorStr result;
  unsigned nested_braces_level{ 0 };
  while (str[idx] != ')') 
  {
    const auto& cur_mmacro_arg = arguments_names[result.size()];
    auto cur_arg = parse_arg(str, idx, cur_mmacro_arg == PP_VARARG);
    result.emplace_back(std::move(cur_arg));
    if (str[idx] == ',')
      idx++;
  }
  idx++;
  return result;
}


std::string replace_placeholders_in_macro(const MacroDesc&  macro, const VectorStr& arguments)
{
  std::map<size_t, size_t> placeholdersPos; // TODO: Fill this map only once
  const auto& str = macro.value;
  for (size_t i = 0; i < macro.arguments.size(); ++i) 
  {
    const auto& cur_arg = macro.arguments[i];
    size_t nPos = str.find(cur_arg, 0);
    while (nPos != std::string::npos) 
    {
      placeholdersPos[nPos] = i;
      nPos = str.find(cur_arg, nPos + 1);
    }
  }

  std::string result;
  size_t prev_idx = 0;
  for (auto& idxs : placeholdersPos) 
  {
    auto cur_macro_idx = idxs.second;
    auto cur_pos = idxs.first;
    result += str.substr(prev_idx, cur_pos - prev_idx);

    assert(cur_macro_idx < arguments.size());
    auto& replacer = arguments[cur_macro_idx];
    prev_idx = cur_pos + macro.arguments[cur_macro_idx].size();
    result += replacer;
  }
  result += str.substr(prev_idx);

  return result;
}


std::string preprocess(const std::string& str, bool& was_changed)
{
  IndexedMacrocesType macroces;
  fill_macro_idxs(macro_descs, macroces, str);

  std::string result;
  size_t prev_idx = 0;

  for (auto& idxs : macroces) 
  {
    auto cur_macro_idx = idxs.second;
    auto cur_pos = idxs.first;
    result += str.substr(prev_idx, cur_pos - prev_idx);

    auto& replacer = macro_descs[cur_macro_idx];
    prev_idx = cur_pos + replacer.name.size();
    auto arguments = get_arguments(str, prev_idx, replacer.arguments);
    auto replace_text = replace_placeholders_in_macro(replacer, arguments);

    result += replace_text;
  }
  result += str.substr(prev_idx);
  was_changed = !macroces.empty();
  return result;
}


std::string get_str_from_file(std::ifstream& file)
{
  std::string str((std::istreambuf_iterator<char>(file)),
                   std::istreambuf_iterator<char>());
  return str;
}


bool process_file(const fs::path& path, std::ofstream& output_file)
{
  std::ifstream ifstr(path.c_str());

  if (!ifstr.is_open()) 
  {
    std::cerr << "Cannot open the file\n";
    return false;
  }

  std::string str = get_str_from_file(ifstr);

  bool was_changed = false;
  std::string result = preprocess(str, was_changed);

  while (was_changed)
  {
    result = preprocess(result, was_changed);
    std::cerr << result << "\n\n\n\n";
  }

  output_file << result;

  return true;
}


int main(int argc, char * argv[])
{
  const fs::path cur_dir = fs::current_path();
  const fs::path work_path = cur_dir / "test"; // TODO: Directory name as program argument
  const fs::path output_path = cur_dir / "output";
  fs::create_directories(output_path / "_build" / "obj");

  for (auto & p : fs::recursive_directory_iterator(work_path))
  {
    if (fs::is_regular_file(p))
    {
      std::cerr << "\nStart to process file: " << p << "\n";

      auto& p_path = p.path();
      const fs::path textFilename = p_path.filename();

      // TODO: Make it in generic way
      auto out_file_path = p_path.parent_path().stem() == "_build" ? output_path / "_build" / textFilename : output_path / textFilename;

      std::ofstream cur_output_file(out_file_path.c_str());
      assert(cur_output_file.is_open());

      process_file(p, cur_output_file) ?
        std::cerr << "\n[SUCCESS]\n" :
        std::cerr << "\n[FAIL]\n";
    }
  }

  return EXIT_SUCCESS;
}
