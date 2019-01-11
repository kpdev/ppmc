
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
      typedef struct [<Name>] [<Name>]; 
      int GetSpecNumAndIncrement[<Name>]();
    )raw"
  } ,
  {
    "DECLARE_GEN_FUNC",
    {
      "[<TypeName>]",
      "[<RetType>]",
      PP_VARARG
    },
    R"raw(
      typedef [<RetType>] (*[<TypeName>]Func)( )raw" PP_VARARG R"raw( ); \
      extern [<TypeName>]Func [<TypeName>]FuncArray[]; \
      [<RetType>] [<TypeName>]( )raw" PP_VARARG R"raw( );
    )raw"
  },
  {
    "DEFINE_GENERALIZATION_METHOD",
    {
      "[<Name>]"
    },
    R"raw(
      static int specNumber = 0; 
      int GetSpecNumAndIncrement[<Name>]() { 
          return specNumber++; 
      }
    )raw"
  },
  {
    "DEFINE_GEN_FUNC",
    {
      "[<TypeName>]",
      "[<Number>]"
    },
    R"raw(
      [<TypeName>]Func [<TypeName>]FuncArray[ [<Number>] ];
    )raw"
  },
  {
    "CREATE_SPECIALIZATION",
    {
      "[<Name>]",
      "[<BaseName>]",
      "[<SpecName>]"
    },
    R"raw(
        typedef [<BaseName>] [<Name>]_base_type;

        typedef struct
        {
            [<BaseName>] _base;
            [<SpecName>] _spec;
        } [<Name>];

        int GetRegMark[<Name>]();
      )raw"
  },
  {
    "CREATE_REG_MARK_METHOD",
    {
      "[<SpecName>]"
    },
    R"raw(  
      static int regMark[<SpecName>] = -1;
	    
      int GetRegMark[<SpecName>]()
      {
          return regMark[<SpecName>];
      }
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
      static void InitRegMark[<SpecName>](void)
      {
        regMark[<SpecName>] = GetSpecNumAndIncrement[<GenName>]();
			  if ([<DebugInfo>] != NULL) 
        {
          printf([<DebugInfo>]);
          printf("   regMark: %d\n", regMark[<SpecName>]);
			  }
      }
    )raw"
  },
  {
    "START_REGISTER_METHODS",
    {},
    R"raw(
      // is not used in plain c pplib
    )raw"
  },
};