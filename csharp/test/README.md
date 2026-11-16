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

The UTF-8 marshaler owns P/Invoke input buffers and string-result buffers allocated
by the SWIG callback. Callback input pointers are borrowed from native strings.
Both the ordinary function declarations and runtime callback declarations must
specify UTF-8 marshaling; fixing only one direction does not preserve text.
