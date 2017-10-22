#pragma once

#include <vector>
#include <string>
#include <iostream>

#define PP_VARARG "[<...>]"


using VectorStr = std::vector<std::string>;

struct MacroDesc
{
  std::string name;
  VectorStr arguments;
  std::string value;
};

///------------------------------------------------------

class ClassMarkRegistrar
{
public:
  typedef void(*Initializer)();

  explicit ClassMarkRegistrar(Initializer init, const char* regInfo = nullptr)
  {
    if (regInfo != nullptr) std::cout << regInfo << std::endl;
    init();
  }
};


class MethodRegistrar
{
public:
  template<typename TMethod>
  MethodRegistrar(
    TMethod container[],
    TMethod method,
    int index,
    const char* info = nullptr)
  {
    if (info != nullptr) {
      std::cout << info << "\n\tindex: " << index << '\n';
    }

    container[index] = method;
  }
};



// TODO: Move this definition to cpp file
MacroDesc macro_descs[] = {
  {
    "INIT",
    {
      "[<TypeName>]",
      "[<SpecName>]",
      PP_VARARG
    },
    R"raw(
      void Init([<TypeName>]& generalizationName, ...) 
      {
        generalizationName.mark = GetRegMark[<TypeName>]();
        [<SpecName>]& c = generalizationName._spec;
        Init(c, PP_VARARGS_STR );
      }
    )raw"
  },
  {
    "CREATE",
    {
      "[<TypeName>]"
    },
    R"raw(
      [<TypeName>]* Create[<TypeName>]() {
        [<TypeName>]* object = new [<TypeName>];
        Init(*object, 0);
        return object;
      }
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
  },
  {
    "DEFINE_MM",
    {
      "[<TypeName>]",
      "[<Dimension>]"
    },
    R"raw(
      [<TypeName>] [<TypeName>]MMArray[ [<Dimension>] ][ [<Dimension>] ];
    )raw"
  },
  {
    "CREATE_MM_SPEC",
    {
      "[<MethodName>]",
      "[<Type1>]",
      "[<Type2>]",
      "[<MethodImpl>]"
    },
    R"raw(
      using BaseType = [<Type1>]::base_type;
      static_assert(std::is_same<BaseType, [<Type2>]::base_type>::value, "Basic types must be the same");
      template<typename ... ArgsT>
      void [<MethodName>](BaseType &f1, BaseType &f2, ArgsT ...args)
      {
	      if(f1.mark == GET_REG_MARK_METHOD( [<Type1>] ) && f2.mark == GET_REG_MARK_METHOD( [<Type2>] )) {
		      [<MethodImpl>](static_cast< [<Type1>]& >(f1), static_cast< [<Type2>]&>(f2), args...);
	      }
	      else {
		      cout << " [<MethodName>] : Incorrect convertion one of parameters" << endl;
		      throw;
	      }
      }
    )raw"
  },
  {
    "BEGIN_REG_MM",
    {
      "[<ArrayName>]"
    },
    R"raw(
      namespace {
	      class [<ArrayName>]MMArrayRegister {
	      public:
		      [<ArrayName>]MMArrayRegister(const char * regInfo = nullptr) {
			      if (regInfo != nullptr) cout << regInfo << endl;
			      auto& _array_alias = [<ArrayName>]MMArray;
    )raw"
  },
  {
    "REG_MM_SPEC",
    {
      "[<SpecName>]",
      "[<Type1>]",
      "[<Type2>]"
    },
    R"raw(
			_array_alias[GET_REG_MARK_METHOD(Type1)][GET_REG_MARK_METHOD(Type2)] = [<SpecName>];
			cout << "    multimethodFunc[" << GET_REG_MARK_METHOD( [<Type1>] ) << "][" << GET_REG_MARK_METHOD( [<Type2>] ) << "] = " [<SpecName>] << endl;
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
	      pplib_mm_reg__COUNTER__( [<OptionalMessage>] ); // TODO: Fix counter using
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
      int GetRegMark[<SpecName>]()
      {
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
      struct [<Name>] : [<BaseName>] {
          [<AddFieldType>] [<AddFieldName>];
          [<BaseName>]* [<GeneralizationName>];
      };
	    int GetRegMark[<Name>]();
    )raw"
  },
  {
    "GET_REG_MARK_METHOD",
    {
      "[Type<>]"
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
      "[<DebugInfo>]"
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
      namespace {
	      [<RetType>] * __Inner_Check_[<Method>] ( int file_mark ) {
		      if (file_mark == [<FileMark>]) {
			      auto ptr = [<Method>]();
			      return ptr;
		      }
		      return nullptr;
	      }
	      REGISTER_METHOD([<Container>]FuncArray, __Inner_Check_[<Method>], GET_REG_MARK_METHOD([<DerivedClass>]), [<DebugInfo>]);
      }        
    )raw"
  },
  {
    "REGISTER_METHOD_WITH_CHECK",
    {
      "[<Container>]",
      "[<Method>]",
      "[<DebugInfo>]",
      "[<DerivedClass>]",
      PP_VARARG
    },
    R"raw(
      using BaseClass = [<DerivedClass>]::base_type;
      namespace {
	      template <typename ... ArgsT>
	      void __Inner_Check_[<Method>] (  BaseClass& bc, ArgsT ... args ) {
		      if ( bc.mark == GET_REG_MARK_METHOD([<DerivedClass>]) ) {
			      [<Method>]( static_cast<[<DerivedClass>]&>(bc), args... );
		      }
		      else {
			      cerr << " [<Method>] : incorrect convertion to"
				      << " [<DerivedClass>] \n";
			      throw;
		      }
	      }
	      auto __Inner_Check_[<Method>]FncToPass = __Inner_Check_[<Method>]< )raw" PP_VARARG R"raw( >;
	      REGISTER_METHOD([<Container>]FuncArray, __Inner_Check_[<Method>]FncToPass, GET_REG_MARK_METHOD([<DerivedClass>]), DebugInfo);
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
      namespace
      {
          void InitRegMark[<SpecName>]()
          {
            regMark[<SpecName>] = GetSpecNumAndIncrement[<GenName>]();
			      if ([<DebugInfo>] != nullptr) {
				      cout << "   regMark: " << regMark[<SpecName>] << endl;
			      }
          }
          ClassMarkRegistrar reg[<SpecName>](InitRegMark[<SpecName>], [<DebugInfo>]);
      }
    )raw"
  }
  //,{
  //  "",
  //  {
  //    "[<>]",
  //    "[<>]"
  //  },
  //    R"raw(
  //  )raw"
  //}
};

constexpr size_t macroces_count = sizeof(macro_descs) / sizeof(macro_descs[0]);