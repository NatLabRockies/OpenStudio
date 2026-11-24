/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/core/ApplicationPathHelpers.hpp>
#include <utilities/core/PathHelpers.hpp>
#include <OpenStudio.hxx>

using namespace openstudio;

// Want to make sure what getOpenStudioModule actually returns
TEST(ApplicationPathHelpers, Simple_test_forThisModule) {
  path openstudioModulePath = getOpenStudioModule();
  EXPECT_TRUE(exists(openstudioModulePath));
  // The expected path is the utilities one, but resolved for symlinks (we don't want to hardcode the version eg openstudio_utilities_tests-2.8.0)
#if defined(_WIN32)
#  if defined(_MSC_VER)
  constexpr auto openstudioLibraryName = "openstudioutilitieslib.dll";
#  else
  constexpr auto openstudioLibraryName = "openstudiolib.dll";
#  endif
#  if defined(NINJA)
  openstudio::path expectedOpenstudioModulePath = getApplicationBuildDirectory() / toPath("Products") / toPath(openstudioLibraryName);
#  elif _DEBUG
  openstudio::path expectedOpenstudioModulePath = getApplicationBuildDirectory() / toPath("Products/Debug") / toPath(openstudioLibraryName);
#  else
  openstudio::path expectedOpenstudioModulePath = getApplicationBuildDirectory() / toPath("Products/Release") / toPath(openstudioLibraryName);
#  endif
#elif __APPLE__
  openstudio::path expectedOpenstudioModulePath = getApplicationBuildDirectory() / toPath("Products/libopenstudiolib.dylib");
#else
  openstudio::path expectedOpenstudioModulePath = getApplicationBuildDirectory() / toPath("Products/libopenstudiolib.so");
#endif
  expectedOpenstudioModulePath = completeAndNormalize(expectedOpenstudioModulePath);
  EXPECT_EQ(toString(expectedOpenstudioModulePath), toString(openstudioModulePath));
}
