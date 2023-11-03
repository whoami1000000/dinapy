import json
import os
import subprocess
import sys
from pathlib import Path

from setuptools import Extension, setup
from setuptools.command.build_ext import build_ext


# A CMakeExtension needs a sourcedir instead of a file list.
# The name must be the _single_ output extension from the CMake build.
# If you need multiple extensions, see scikit-build.
class CMakeExtension(Extension):
    def __init__(self, name: str, source_dir: str = '') -> None:
        super().__init__(name, sources=[])
        self.source_dir = os.fspath(Path(source_dir).resolve())


class CMakeBuild(build_ext):
    def build_extension(self, ext: CMakeExtension) -> None:
        # Must be in this form due to bug in .resolve() only fixed in Python 3.10+
        ext_fullpath = Path.cwd() / self.get_ext_fullpath(ext.name)
        ext_dir = ext_fullpath.parent.resolve()

        cfg = 'Release'

        # CMake lets you override the generator - we need to check this.
        # Can be set with Conda-Build, for example.
        cmake_generator = os.environ.get('CMAKE_GENERATOR', '')

        # Set Python_EXECUTABLE instead if you use PYBIND11_FINDPYTHON
        # EXAMPLE_VERSION_INFO shows you how to pass a value into the C++ code
        # from Python.
        cmake_args = [
            f'-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={ext_dir}{os.sep}',
            f'-DPYTHON_EXECUTABLE={sys.executable}',
            f'-DCMAKE_BUILD_TYPE={cfg}',  # not used on MSVC, but no harm
            f'-DPy=ON'
        ]
        build_args = []

        # if self.compiler.compiler_type != "msvc":
        #     # Using Ninja-build since it a) is available as a wheel and b)
        #     # multithreads automatically. MSVC would require all variables be
        #     # exported for Ninja to pick it up, which is a little tricky to do.
        #     # Users can override the generator with CMAKE_GENERATOR in CMake
        #     # 3.15+.
        #     if not cmake_generator or cmake_generator == "Ninja":
        #         try:
        #             import ninja
        #
        #             ninja_executable_path = Path(ninja.BIN_DIR) / "ninja"
        #             cmake_args += [
        #                 "-GNinja",
        #                 f"-DCMAKE_MAKE_PROGRAM:FILEPATH={ninja_executable_path}",
        #             ]
        #         except ImportError:
        #             pass

        build_temp = Path(self.build_temp) / ext.name
        if not build_temp.exists():
            build_temp.mkdir(parents=True)

        subprocess.run(
            ['cmake', ext.source_dir, *cmake_args], cwd=build_temp, check=True
        )
        subprocess.run(
            ['cmake', '--build', '.', *build_args], cwd=build_temp, check=True
        )


with open('vcpkg.json', 'r') as vcpkg_file:
    vcpkg_json = json.load(vcpkg_file)
    version = vcpkg_json['version-string']

setup(
    name='dinapy',
    version=version,
    author='Igor Kozlov',
    author_email='igorkozlov1992@gmail.com',
    description='A test project using pybind11 and CMake',
    long_description='',
    ext_modules=[CMakeExtension('dinapy')],
    cmdclass={'build_ext': CMakeBuild},
    zip_safe=False,
    python_requires='>=3.7',
)
