import sys
from pathlib import Path

from conan import ConanFile
from conan.tools.apple import is_apple_os
from conan.tools.cmake import CMakeToolchain

required_conan_version = ">=2.0"


class OpenStudioBuildRecipe(ConanFile):
    name = "openstudio"
    description = "Build recipe for OpenStudio SDK which install necessary conan dependencies"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"  # CMakeToolchain explicitly instantiated

    options = {
        "with_ruby": [True, False],
        "with_python": [True, False],
        "with_csharp": [True, False],
        "with_testing": [True, False],
        "with_benchmark": [True, False],
    }
    default_options = {
        "with_ruby": True,
        "with_python": True,
        "with_csharp": False,
        "with_testing": True,
        "with_benchmark": True,
    }

    def requirements(self):
        if self.options.with_ruby:
            self.requires("ruby/3.2.2")

        if is_apple_os(self):
            self.requires(
                "boost/1.86.0", force=True, options={"visibility": "global"}
            )
        else:
            self.requires("boost/1.86.0", force=True) # cpprestsdk doesn't build with boost 1.87.0
        self.requires("pugixml/1.15")
        self.requires(
            "libxml2/[<2.12.0]"
        )  # deprecated xmlSubstituteEntitiesDefault and co https://github.com/GNOME/libxml2/commit/db8b9722cb2a1f7dca7374ec38ecaa4936ab3869
        self.requires("libxslt/1.1.37")  # TODO use libxslt/1.1.43 after porting the libxml2 code
        self.requires("jsoncpp/1.9.6")
        self.requires("fmt/12.1.0")
        self.requires("sqlite3/3.53.0")
        self.requires("cpprestsdk/2.10.19")  # df2f6ac88e47cadd9c9e8e0971e00d89
        self.requires("websocketpp/0.8.2")  # 3fd704c4c5388d9c08b11af86f79f616
        self.requires("geographiclib/2.6")
        self.requires("swig/4.4.0")
        self.requires("tinygltf/2.9.7")
        self.requires("cli11/2.6.2")
        self.requires("antlr4-cppruntime/4.13.2")

        self.requires(
            "minizip/1.3.1"
        )  # This depends on zlib, and basically patches it
        self.requires(
            "zlib/[>=1.2.11 <2]"
        )  # Also needed, so we can find zlib.h and co (+ pinning exactly is good)
        self.requires("openssl/[>=3 <4]")

        if self.options.with_testing:
            self.requires("gtest/1.17.0")
        if self.options.with_benchmark:
            self.requires("benchmark/1.9.5")

    # Let people provide their own CMake for now
    # def build_requirements(self):
    #     self.tool_requires("cmake/3.29.0")

    def generate(self):
        tc = CMakeToolchain(self)

        tc.cache_variables["BUILD_CLI"] = bool(self.options.with_ruby)
        tc.cache_variables["BUILD_RUBY_BINDINGS"] = bool(self.options.with_ruby)
        tc.cache_variables["BUILD_PYTHON_BINDINGS"] = bool(self.options.with_python)
        tc.cache_variables["BUILD_CSHARP_BINDINGS"] = bool(self.options.with_csharp)
        # tc.cache_variables["BUILD_NUGET_PACKAGE"] = False
        # tc.cache_variables["BUILD_PYTHON_PIP_PACKAGE"] = False

        tc.cache_variables["BUILD_TESTING"] = bool(self.options.with_testing)
        tc.cache_variables["BUILD_BENCHMARK"] = bool(self.options.with_benchmark)

        tc.cache_variables["CPACK_BINARY_TGZ"] = True
        tc.cache_variables["CPACK_BINARY_IFW"] = False
        tc.cache_variables["CPACK_BINARY_DEB"] = False
        if self.settings.build_type == "Release":
            if is_apple_os(self) or self.settings.os == "Windows":
                tc.cache_variables["CPACK_BINARY_IFW"] = True
            else:
                tc.cache_variables["CPACK_BINARY_DEB"] = True
        tc.cache_variables["CPACK_BINARY_NSIS"] = False
        tc.cache_variables["CPACK_BINARY_RPM"] = False
        tc.cache_variables["CPACK_BINARY_STGZ"] = False
        tc.cache_variables["CPACK_BINARY_TBZ2"] = False
        tc.cache_variables["CPACK_BINARY_TXZ"] = False
        tc.cache_variables["CPACK_BINARY_TZ"] = False

        # Ensure cmake finds the conan executable
        exe_ext = ".exe" if self.settings.os == "Windows" else ""
        swig_exe = (Path(self.dependencies['swig'].cpp_info.bindir) / f"swig{exe_ext}").as_posix()
        # CMakePresets.json
        tc.cache_variables["SWIG_EXECUTABLE"] = swig_exe
        # conan_toolchain.cmake
        tc.variables["SWIG_EXECUTABLE"] = swig_exe

        if self.options.with_python:
            v = sys.version_info
            if (v.major, v.minor) == (3, 12):
                python_version = f"{v.major}.{v.minor}.{v.micro}"
                self.output.info(
                    f"Setting PYTHON_VERSION and Python_ROOT_DIR from your current python: {python_version}, '{sys.base_prefix}'"
                )
                tc.cache_variables["PYTHON_VERSION"] = python_version
                tc.cache_variables["Python_ROOT_DIR"] = Path(sys.base_prefix).as_posix()
            else:
                self.output.warning(
                    "Your current python is not in the 3.12.x range, which is what we target.\n"
                    "You'll need to pass it properly when configuring CMake\n"
                    "via -DPYTHON_VERSION:STRING='3.12.xx' and -DPython_ROOT_DIR:PATH='/path/to/python3.12/'"
                )
        tc.generate()
