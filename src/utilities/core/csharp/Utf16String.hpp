/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_CORE_CSHARP_UTF16STRING_HPP
#define UTILITIES_CORE_CSHARP_UTF16STRING_HPP

#include "../String.hpp"

#include <cstdlib>
#include <memory>
#include <string>

#if defined(_WIN32)
#  include <objbase.h>
#endif

namespace openstudio {
namespace detail {

inline std::u16string directorStringToUtf16(const std::string& value) {
  // toWString stores UTF-16 code units even where wchar_t is four bytes.
  const std::wstring utf16 = openstudio::toWString(value);
  return {utf16.begin(), utf16.end()};
}

struct DirectorStringDeleter
{
  void operator()(const char* value) const noexcept {
#if defined(_WIN32)
    CoTaskMemFree(const_cast<char*>(value));
#else
    std::free(const_cast<char*>(value));
#endif
  }
};

inline std::string takeDirectorUtf16String(const char* value) {
  // The delegate transfers its LPWStr allocation; release it even if conversion throws.
  const std::unique_ptr<const char, DirectorStringDeleter> owner(value);
  const std::u16string utf16(reinterpret_cast<const char16_t*>(value));
  return openstudio::toString(std::wstring(utf16.begin(), utf16.end()));
}

}  // namespace detail
}  // namespace openstudio

#endif  // UTILITIES_CORE_CSHARP_UTF16STRING_HPP
