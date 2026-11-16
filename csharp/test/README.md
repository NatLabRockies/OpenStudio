# C# UTF-8 regression

Configure a Windows build with `BUILD_CSHARP_BINDINGS=ON` and `BUILD_TESTING=ON`, then run:

```console
cmake --build build --config Release --target csharp_sdk
ctest --test-dir build -C Release -R "^CSharpTest-Utf8Bindings$" --output-on-failure
```

The standalone test uses only .NET Framework 4.5 APIs. It checks Unicode directory
and file names, IDF load/save, header text on disk, returned strings, containers,
exception callbacks, null/empty handling, and repeated callbacks with garbage
collection. It also exercises the model and translator binding modules.

The director tests call the existing native measure-name entry point to reach a
C# `EnergyPlusMeasure.name()` override. They also call `validateUserArguments` to
make native code invoke a C# `OSRunner.registerError()` override with a Unicode
argument name. Callback counts verify that native virtual dispatch reaches both
overrides. Repeated calls and forced garbage collection check delegate lifetimes.
The measure-name test uses reflection because a direct C# call stays in the
override, while `base.name()` bypasses native virtual dispatch.

P/Invoke inputs use zero-terminated UTF-8 `byte[]` values. The CLR manages their
storage for the duration of the native call. Ordinary string results cross the
generated wrapper boundary as UTF-16 `LPWStr`; the CLR copies and releases the
result buffers. The underlying OpenStudio C++ API continues to use UTF-8 strings.

Director callbacks use a UTF-16 boundary in both directions. Native code owns
callback input strings, which remain valid for the callback and must not be
released by managed code. The CLR allocates director string-return buffers;
native RAII ownership releases each buffer with `CoTaskMemFree` on Windows or
`free` on other platforms after converting it to a C++ UTF-8 string, including
when conversion throws. Registered delegates remain rooted by their wrappers.

These mechanisms use APIs available in .NET Framework 4.5. Rebuild and distribute
the managed assembly and native wrappers together: their string boundary must
match.
