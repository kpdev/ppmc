
#include "plain_c_macro_description.hpp"

std::vector<MacroDesc> macro_descs = {
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
  },
  {
    "PPLIB_DEFINE_INIT",
    {
    },
    R"raw(
      void pplib_init()
      {
        /* Init */ printf("Hello PPLIB\n");
      }
    )raw"
  },
  {
    "PPLIB_INIT",
    {
    },
    R"raw(
      pplib_init();
    )raw"
  }
};