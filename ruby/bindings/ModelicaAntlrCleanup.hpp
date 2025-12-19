#pragma once

namespace openstudio::ruby {

/**
 * Register a Ruby end_proc hook that tears down ANTLR singletons safely when the interpreter exits.
 *
 * Why does this exist? Linking the Modelica parser into openstudio.so drags in ANTLR's global
 * singletons (notably CommonTokenFactory::DEFAULT). Ruby unloads extensions with dlclose() and runs
 * them through its GC at exit, so ANTLR's destructors fire while the interpreter is already winding
 * down, which consistently segfaults. We cannot delete the singleton from a global static
 * destructor either because every executable that links
 * openstudio_modelica (gtests, CLI, etc.) would explode during __cxa_finalize() before Ruby was
 * ever involved, and we cannot register Ruby callbacks from such a static because rb_set_end_proc
 * must run after the VM boots.
 *
 * Instead, we register a Ruby end_proc callback once per interpreter that releases the singleton
 * *only* when the Ruby VM shuts down. That keeps the workaround scoped to Ruby, preserves the
 * default teardown order for other binaries, and mirrors Ruby's own extension lifecycle.
 */
void registerModelicaAntlrCleanup();

}  // namespace openstudio::ruby
