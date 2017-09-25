
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cassert>
#include <memory>


using std::ifstream;
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
    "CREATE_REG_MARK_METHOD",
    {
      "[<SpecName>]"
    },
  R"raw(
      namespace {
        int regMark[<SpecName>] = -1;
      }
      int GetRegMark[<SpecName>](){
        return regMark[<SpecName>];
      }
    )raw"
  },
  {
    "CREATE_SPECIALIZATION_DECORATOR",
    {
      "[<Name>]",
      "[<BaseName>]",
      "[<GeneralizationName>]",
      "[<AddFieldType>]",
      "[<AddFieldName>]"
    },
  R"raw(
      struct [<Name>] : [<BaseName>]{
        [<AddFieldType>] [<AddFieldName>];
        [<BaseName>]* [<GeneralizationName>];
      }
      int GetRegMark[<Name>];
      )raw"
  },
  {
    "REGISTER_SPECIALIZATION",
    {
      "[<GenName>]",
      "[<SpecName>]",
      "[<DebugInfo>]"
    },
  R"raw(
      namespace {
        void InitRegMark[<SpecName>](){
          regMark[<SpecName>] = GetSpecNumAndIncrement[<GenName>]();
        }
        if ([<DebugInfo>] != nullptr){
          cout <<\"regmark: \" << regmark[<SpecName>] << endl;
        }
        ClassMarkRegistrar reg[<SpecName>](InitRegMark[<SpecName>], [<DebugInfo>])
      }
    )raw"
  },
  {
    "GET_REG_MARK_METHOD",
    {
      "[<Type>]"
    },
  R"raw(
      GetRegMark[<Type>]()
    )raw"
  },
  {
    "REGISTER_METHOD",
    {
      "[<Container>]",
      "[<Method>]",
      "[<Mark>]",
      "[<DebugInfo>]",
    },
    R"raw(
      MethodRegistrar regMethod[<Method>]([<Container>], [<Method>], [<Mark>], [<DebugInfo>]);
    )raw"
  },
  {
    "REGISTER_METHOD_WITH_CHECK_RET_PTR",
    {
      "[<Container>]",
      "[<Method>]",
      "[<DerivedClass>]",
      "[<DebugInfo>]",
      "[<FileMark>]",
      "[<RetType>]"
    },
  R"raw(
      namespace{
        [<RetType>] * __Inner_Check_[<Method>] (int file_mark) {
          if(file_mark==[<FileMark>]){
            auto ptr = [<Method>];
            return ptr;
          }
          return nullptr;
        }
        REGISTER_METHOD(Container[<FuncArray>], __Inner_Check_[<Method>], GET_REG_MARK_METHOD([<DerivedClass]), [<DebugInfo>]);
       }
    )raw"
  },
  /*TODO: ADD REGISTER_METHOD_WITH_CHECK*/
  /*TODO: ADD CREATE_MM_SPEC*/
  {
    "BEGIN_REG_MM",
    {
      "[<ArrayName>]"
    },
  R"raw(
      namespace {
        class [<ArrayName>]MMArrayRegister(const char *regInfo = nullptr){
          if(regInfo != nullptr) cout << \"reginfo\" << endl;
          auto & _array_alias = [<ArrayName>]MMArray;
        }
      
    )raw"

    /*
    #define BEGIN_REG_MM(ArrayName) \
    namespace { \
	    class ArrayName##MMArray##Register { \
	    public: \
		    ArrayName##MMArray##Register(const char * regInfo = nullptr) { \
			    if (regInfo != nullptr) cout << regInfo << endl; \
			    auto& _array_alias = ArrayName##MMArray;
    
    */


  },

  {
    "REG_MM_SPEC",
    {
      "[<SpecName>]",
      "[<Type1>]",
      "[<Type2>]"
    },
  R"raw(
      
      _array_alias[GET_REG_MARK_METHOD([<Type1>])] [GET_REG_MARK_METHOD[<Type2>])] = [<SpecName>];
      cout << \"multimethodFunc[\" << GET_REG_MARK_METHOD([<Type1>]) << \"][\" << GET_REG_MARK_METHOD([<Type2>]) << \" ] = \" << #[<SpecName>] << endl;
      
    )raw"
  },
  {
    "END_REG_MM",
    {
      "[<OptionalMessage>]"
    },
  R"raw(
        }
      }
      
      pplib_mm_reg##__COUNTER__([<OptionalMessage>]); /*CHECK GLOBAL DEFINITION COUNTER!!!*/
      
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


std::string parse_arg(const std::string& str, size_t& idx)
{
  std::string result;
  while (str[idx] != ',' && str[idx] != ')') 
  {
    result += str[idx++];
  }
  return result;
}


VectorStr get_arguments(const std::string& str, size_t& idx)
{
  assert(str[idx] == '(');
  idx++;
  VectorStr result;
  while (str[idx] != ')') 
  {
    auto cur_arg = parse_arg(str, idx);
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


int main(int argc, char * argv[])
{
  //ifstream ifst(argv[1]);
  //if (!ifst.open) {
  //  std::cerr << "Wrong filename\n";
  //}


  std::string str("TEST_TEXT_1 CREATE_GENERALIZATION(ARG_1) CREATE_SPECIALIZATION(NameArg, BNameArg, SNameArg)" 
    "TEST_TEXT_2 TEST_TEXT_3 DEFINE_GENERALIZATION_METHOD(ARG_2)"
    " TEST_TEXT_4 CREATE_GENERALIZATION(ARG_3)  \n");

  //std::string str("Begin test text CREATE_SPECIALIZATION(NameArg, BNameArg, SNameArg) end test text\n");

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
    auto arguments = get_arguments(str, prev_idx);
    auto replace_text = replace_placeholders_in_macro(replacer, arguments);

    result += replace_text;
  }
  result += str.substr(prev_idx);

  std::cerr << result << std::endl;

  return EXIT_SUCCESS;
}