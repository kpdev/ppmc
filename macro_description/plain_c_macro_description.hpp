#pragma once

#include <vector>
#include <string>
#include <cstddef>

#define PP_VARARG "[<...>]"

// TODO: Move it to common part
using VectorStr = std::vector<std::string>;

struct MacroDesc
{
  std::string name;
  VectorStr arguments;
  std::string value;
};

using MacroDescVec = std::vector<MacroDesc>;

extern MacroDescVec macro_descs;
