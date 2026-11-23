########################################################################################################################
#  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
#  See also https://openstudio.net/license
########################################################################################################################

import os
import platform
import sys

from setuptools import find_packages, setup
from setuptools.command.install import install
from setuptools.dist import Distribution

# CPython minor versions (3.X) that changed struct layouts used by our extension modules via the full C API.
# A Unix wheel built on 3.Y < 3.X is only valid for 3.Y <= python < 3.X
# * 3.14: PyTupleObject gained ob_hash before ob_item, https://github.com/python/cpython/pull/131529 (#5668)
# Note: fields appended at the END of PyTypeObject (tp_watched 3.12, tp_versions_used 3.13, _tp_iteritem 3.15) are not
# listed: SWIG embeds a static PyTypeObject (swig_varlink_type) sized at build time, so that's technically unsupported,
# but it has never broken in practice. The test_python_bindings CI job must pass on every version we tag for.
_CPYTHON_ABI_BREAKS = [14]

# Newest CPython minor version we tag Unix wheels for. Bump it only once CI tests that version.
_NEWEST_TESTED_MINOR = 15


def _unix_compatible_minors():
    """Python 3 minor versions a Unix wheel built with the current interpreter is valid for."""
    build_minor = sys.version_info.minor
    upper = next((b for b in _CPYTHON_ABI_BREAKS if b > build_minor), _NEWEST_TESTED_MINOR + 1)
    return list(range(build_minor, max(upper, build_minor + 1)))


try:
    from wheel.bdist_wheel import bdist_wheel as _bdist_wheel

    class bdist_wheel(_bdist_wheel):
        def finalize_options(self):
            _bdist_wheel.finalize_options(self)
            # Mark us as not a pure python package, so that the wheel is marked
            # with the platform name
            self.root_is_pure = False

        def get_tag(self):
            # Setting it up to build generic wheels.
            python, abi, plat = _bdist_wheel.get_tag(self)
            print(f"Original: (python, abi, plat) = " "({python}, {abi}, {plat})")
            if platform.system() != "Windows":
                # On Unix we build a single wheel (with the oldest version) and reuse it for several CPython versions.
                # The extension modules don't link to libpython, but they use the full (non-limited) C API,
                # so it is only valid from the build version up to the next CPython ABI break.
                # We spell out every compatible version (eg 'cp311.cp312.cp313-cp311.cp312.cp313') rather than using
                # 'py3-none', so pip won't even consider the wheel on other versions.
                # The ABI tag is spelled out too (not 'none') so free-threaded builds (eg cp313t), which have a
                # different PyObject layout, reject it.
                python = ".".join(f"cp3{m}" for m in _unix_compatible_minors())
                abi = python

            # Our bindings won't be compatible with all distributions,
            # BUT pypi will refuse the upload if we do not replace
            # "Binary wheel 'openstudio-3.1.0rc3-py3-none-linux_x86_64.whl'
            #  has an unsupported platform tag 'linux_x86_64'"
            if "aarch64" in plat:
                plat = plat.lower().replace("linux", "manylinux2014")
            else:
                plat = plat.lower().replace("linux", "manylinux1")
            plat = plat.lower().replace("darwin_x86_64", "macosx_10_6_intel")
            if plat[:3] == "mac":
                # Python itself may be a universal2 build (it is with actions/setup-python), but our extensions are only
                # built for the host architecture by CMake, so use that, not the interpreter's platform
                if platform.machine() == "arm64":
                    plat = "macosx_11_0_arm64"
                else:
                    # We don't use a fat binary ('intel' = both i386 and x86_64)
                    # but we set the platform to old one in the hope that it'll
                    # work for all
                    plat = "macosx_10_9_x86_64"
            print("Final: (python, abi, plat) = ({}, {}, {})".format(python, abi, plat))
            return python, abi, plat

except ImportError:
    bdist_wheel = None


class BinaryDistribution(Distribution):
    def is_pure(self):
        return False

    def has_ext_modules(self):
        return True


class InstallPlatlib(install):
    def finalize_options(self):
        install.finalize_options(self)
        self.install_lib = self.install_platlib


with open(os.path.join("@PROJECT_SOURCE_DIR@", "README.md"), encoding="utf-8") as f:
    long_description = f.read()

dev_release = "a2"

# The wheel tag (see bdist_wheel.get_tag) is what really restricts the Python versions, this is belt and braces.
# Windows builds one wheel per Python version (cpXY tag)
python_requires = ">=3.11"
if platform.system() != "Windows":
    _minors = _unix_compatible_minors()
    python_requires = f">=3.{_minors[0]},<3.{_minors[-1] + 1}"

setup(
    name="openstudio",
    # eg 3.1.0rc3
    # version='@OpenStudio_VERSION@'.replace('-', '') + dev_release,
    version="@PYPI_VERSION@",
    description="OpenStudio python bindings.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/NREL/OpenStudio",
    author="Alliance for Energy Innovation, LLC, and other contributors",
    author_email="openstudio@nlr.gov",
    maintainer="Julien Marrec",
    maintainer_email="contact@effibem.com",
    license="BSD3",
    project_urls={
        "Bug Tracker": "https://github.com/NREL/OpenStudio/issues",
        "Documentation": "https://openstudio.net/",
        "Source Code": "https://github.com/NREL/OpenStudio",
    },
    platforms="any",
    python_requires=python_requires,
    classifiers=[
        "Development Status :: 4 - Beta",
        "Environment :: Console",
        "Intended Audience :: Science/Research",
        "Topic :: Scientific/Engineering",
        "License :: OSI Approved :: BSD License",
        "Programming Language :: Python",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.11",
        "Programming Language :: Python :: 3.12",
        "Programming Language :: Python :: 3.13",
    ],
    keywords="openstudio py3 setuptools development",
    packages=find_packages(include=["openstudio"]),
    package_data={
        "openstudio": [
            "*.so",
            "*.pyd",
            "*.dll",
            "*.dylib",
            "*.bundle",
            # "*.lib", "*.exp",
        ],
    },
    install_requires=[],
    cmdclass={"bdist_wheel": bdist_wheel, "install": InstallPlatlib},
    distclass=BinaryDistribution,
)
