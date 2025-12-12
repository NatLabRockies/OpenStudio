/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#if defined(__APPLE__)

extern "C" void OPENSSL_cpuid_setup();

namespace {

// On macOS we statically link libcrypto into librubyengine. Recent versions of the
// Xcode linker expect OPENSSL_cpuid_setup to live inside the image when wiring up
// initializer fixups, otherwise the build fails before we even get to runtime. Forcing
// a direct call keeps the object file that defines the symbol from being dropped.
struct ForceOpenSSLCpuidSetup {
  ForceOpenSSLCpuidSetup() {
    OPENSSL_cpuid_setup();
  }
};

[[maybe_unused]] const ForceOpenSSLCpuidSetup forceOpenSSLCpuidSetup;

}  // namespace

#endif  // __APPLE__
