#include "ModelicaAntlrCleanup.hpp"

#include <antlr4-runtime.h>
#include <ruby.h>

#include <memory>
#include <mutex>

namespace {

using FactoryPtr = std::unique_ptr<antlr4::TokenFactory<antlr4::CommonToken>>;

extern "C" void modelica_antlr_cleanup(VALUE) {
  // This runs as part of Ruby's end_proc chain before the VM dlcloses openstudio.so. We explicitly
  // release the singleton so ANTLR's own static destructor becomes a no-op; otherwise Ruby would
  // run the destructor after parts of the interpreter are gone and we'd segfault while unloading.
  auto* defaultFactory = const_cast<FactoryPtr*>(&antlr4::CommonTokenFactory::DEFAULT);
  auto* raw = defaultFactory->release();
  if (raw != nullptr) {
    delete raw;
  }
}

}  // namespace

namespace openstudio::ruby {

void registerModelicaAntlrCleanup() {
  // Ruby's Init_* entry points are called once per interpreter, so guard the end_proc registration
  // with std::call_once to avoid stacking duplicate callbacks when Init_openstudiomodelica is
  // invoked multiple times (eg. when tests reload the bindings). This static also satisfies the
  // "just use a registrar" idea without running Ruby APIs during global constructors; rb_set_end_proc
  // must execute while the VM is alive, so the call_once guard lives inside the Init path instead of
  // at the translation-unit scope.
  static std::once_flag registeredFlag;
  std::call_once(registeredFlag, []() { rb_set_end_proc(modelica_antlr_cleanup, Qnil); });
}

}  // namespace openstudio::ruby
