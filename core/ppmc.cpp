
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cassert>
#include <memory>

/*
#ifdef __has_include                           // Check if __has_include is present
#  if __has_include(<filesystem>)                // Check for a standard library
#    include<filesystem>
#  elif __has_include(<-stdlib=libc++ test.cpp -lc++experimentalfilesystem>) // Check for an experimental version
#    include <experimental/filesystem>
#  else                                        // Not found at all
#     error "Missing <filesystem>"
#  endif
#elif
#  error("No has_inculde")
#endif
*/

//#include <filesystem>

#define PP_VARARG "[<...>]"

using VectorStr = std::vector<std::string>;

struct MacroDesc
{
  std::string name;
  VectorStr arguments;
  std::string value;
};

using IndexedMacrocesType = std::map<size_t, unsigned>;

MacroDesc macro_descs[] = {
  {
    "CREATE_SPECIALIZATION",
    {
      "[<Name>]",
      "[<BaseName>]",
      "[<SpecName>]"
    },
  R"raw(
        struct [<Name>] : [<BaseName>] {
            using base_type = [<BaseName>];
            [<SpecName>] _spec;
            TEST_NESTING([<Name>]);
        };
        int GetRegMark[<Name>]();
      )raw"
  },
  {
    "CREATE_GENERALIZATION",
    {
      "[<Name>]"
    },
  R"raw(
        struct [<Name>] { 
            int mark; 
        }; 
        int GetSpecNumAndIncrement[<Name>]();
      )raw"
  } ,
  {
    "TEST_NESTING",
    {
      "[<Param>]"
    },
    R"raw(
          ThereIsATest[<Param>]())raw"
  },
  {
    "DEFINE_GENERALIZATION_METHOD",
    {
      "[<Name>]"
    },
  R"raw(
        namespace { 
            int specNumber = 0; 
        } 
        int GetSpecNumAndIncrement[<Name>]() { 
            return specNumber++; 
        }
      )raw"
  },
  {
    "DECLARE_MM",
    {
      "[<TypeName>]",
      "[<Dimension>]",
      "[<BaseType>]",
      PP_VARARG
    },

    R"raw(
      typedef void (*[<TypeName>])([<BaseType>]&, [<BaseType>]&, )raw" PP_VARARG R"raw( );
      extern [<TypeName>] [<TypeName>]##MMArray[][[<Dimension>]];
      template<typename ...ArgsT>
      void [<TypeName>]##MM([<BaseType>] &p1, [<BaseType>] &p2, ArgsT ...args)
      {
        ([<TypeName>]##MMArray[p1.mark][p2.mark])( p1, p2, args... );
      }
    )raw"
  }
};

constexpr size_t macroces_count = sizeof(macro_descs) / sizeof(macro_descs[0]);


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
  while ((is_vararg || (!is_vararg && str[idx] != ','))
    && str[idx] != ')')
  {
    result += str[idx++];
  }
  return result;
}


VectorStr get_arguments(const std::string& str, size_t& idx, const VectorStr& arguments_names)
{
  assert(str[idx] == '(');
  idx++;
  VectorStr result;
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
    while (nPos != std::string::npos) {
      placeholdersPos[nPos] = i;
      nPos = str.find(cur_arg, nPos + 1);
    }
  }

  std::string result;
  size_t prev_idx = 0;
  for (auto& idxs : placeholdersPos) {
    auto cur_macro_idx = idxs.second;
    auto cur_pos = idxs.first;
    result += str.substr(prev_idx, cur_pos - prev_idx);

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

  for (auto& idxs : macroces) {
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


int main(int argc, char * argv[])
{
  //ifstream ifst(argv[1]);
  //if (!ifst.open) {
  //  std::cerr << "Wrong filename\n";
  //}

	//namespace fs = std::experimental::filesystem::v1;
	//fs::path cur_path = fs::current_path();
	//std::cerr << cur_path << std::endl;

  const char * path_to_test_file = "test/test.txt";

  std::ifstream ifstr(path_to_test_file);

  if (!ifstr.is_open())     {
    std::cerr << "Cannot open the file\n";
    return EXIT_FAILURE;
  }

  std::string str((std::istreambuf_iterator<char>(ifstr)),
                   std::istreambuf_iterator<char>());

  bool was_changed = false;
  std::string result = preprocess(str, was_changed);

  while (was_changed)
  {
    result = preprocess(result, was_changed);
  }

  std::cerr << result << std::endl;

  return EXIT_SUCCESS;
}
