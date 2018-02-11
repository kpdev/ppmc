#pragma once

#include <vector>
#include <string>
#include <cstddef>

// TODO: Move it to common part
using VectorStr = std::vector<std::string>;

struct MacroDesc
{
  std::string name;
  VectorStr arguments;
  std::string value;
};

#define PP_VARARG "[<...>]"

MacroDesc macro_descs[] = {
  {
    "INIT_v2",
    {
      "[<TypeName>]"
    },
    R"raw(
          template <typename [<TypeName>], typename ... TArgs>
          void Init([<TypeName>]& generalizationName, TArgs ... args)
          {
            generalizationName.mark = GetRegMark[<TypeName>]();
            auto& c = generalizationName._spec;
            Init(c, args...);
          }
        )raw"
  }
};
  
constexpr size_t macroces_count = sizeof(macro_descs) / sizeof(macro_descs[0]);