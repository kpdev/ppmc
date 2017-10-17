#pragma once

#include <vector>
#include <string>

#define PP_VARARG "[<...>]"

using VectorStr = std::vector<std::string>;

struct MacroDesc
{
  std::string name;
  VectorStr arguments;
  std::string value;
};


// TODO: Move this definition to cpp file
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